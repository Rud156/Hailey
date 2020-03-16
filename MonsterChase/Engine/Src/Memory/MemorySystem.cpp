#include "MemorySystem.h"
#include "FixedMemoryManager.h"

#include <Windows.h>

Memory::MemorySystem* memorySystem = nullptr;

namespace Memory
{
#pragma region Construction

	MemorySystem* MemorySystem::_instance = nullptr;

	MemorySystem::MemorySystem(): _instanceHeapMemory(nullptr), _memoryBlocks(nullptr), _fixedMemoryManagers(nullptr)
	{
	}

	MemorySystem::~MemorySystem() = default;

#pragma region Setup And Destory

	void MemorySystem::createMemorySystem()
	{
		if (_instance == nullptr) // This means that MemorySystem has not yet been allocated
		{
			void* instanceHeapMemory = HeapAlloc(GetProcessHeap(), 0, 1024 * 1024);
			setupMemorySystem(instanceHeapMemory);
		}

		createManager();
	}

	void MemorySystem::createManager()
	{
		_instance->_memorySystemMutex.lock();

		_instance->collect();

		if (_instance->_memoryBlocks != nullptr)
		{
			_instance->_currentSize *= 2;
		}

		const size_t totalMemoryInMB = _instance->_currentSize;
		const size_t sizeHeap = 1024 * 1024 * totalMemoryInMB;
		const size_t numDescriptors = 2048 * totalMemoryInMB;

		void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);

		if (_instance->_memoryBlocks == nullptr) // This means that no memory has been created and thus needs to be done
		{
			Memory::MemorySystem::createInitialMemoryManager(pHeapMemory, sizeHeap, numDescriptors);
		}
		else
		{
			Utils::Debug::LogOutputToWindow("Creating New Memory Manager\n");
			Memory::MemorySystem::createOtherMemoryManager(pHeapMemory, sizeHeap, numDescriptors);
		}

		_instance->_memorySystemMutex.unlock();
	}

	void MemorySystem::returnMemoryToWindows()
	{
		while (_instance->_memoryBlocks != nullptr)
		{
			void* heapMemory = _instance->_memoryBlocks->heapMemory;
			_instance->_memoryBlocks = _instance->_memoryBlocks->nextBlock;

			HeapFree(GetProcessHeap(), 0, heapMemory);
		}

		HeapFree(GetProcessHeap(), 0, _instance->_instanceHeapMemory);
		_instance = nullptr;
	}

	MemorySystem::MemoryBlock* MemorySystem::getEmptyMemoryBlock(void* i_memory)
	{
		const auto memoryBlock = new(i_memory)MemoryBlock();

		memoryBlock->heapMemory = nullptr;
		memoryBlock->memoryManager = nullptr;
		memoryBlock->nextBlock = nullptr;

		return memoryBlock;
	}

#pragma endregion

#pragma endregion

#pragma region Creation

	void MemorySystem::setupMemorySystem(void* i_heapMemoryStartAddress)
	{
		_instance = new(i_heapMemoryStartAddress)MemorySystem();
		memorySystem = _instance;
	}

	void MemorySystem::createInitialMemoryManager(void* i_heapMemory, size_t i_heapTotalSize,
	                                              size_t i_maxBlockDescriptors)
	{
		const size_t memoryBlockSize = sizeof(MemoryBlock);
		void* otherHeap = static_cast<char*>(i_heapMemory) + memoryBlockSize;

		MemoryManager* memoryManagerInstance = MemoryManager::create(otherHeap, i_heapTotalSize,
		                                                             i_maxBlockDescriptors);

		MemoryBlock* memoryBlock = MemorySystem::getEmptyMemoryBlock(i_heapMemory);
		memoryBlock->heapMemory = i_heapMemory;
		memoryBlock->nextBlock = nullptr;
		memoryBlock->memoryManager = memoryManagerInstance;
		_instance->_memoryBlocks = memoryBlock;

		const size_t fixedMemoryManagerSize = sizeof(FixedMemoryManager*);
		void* fixedArrayMemory = memoryManagerInstance->allocate(fixedMemoryManagerSize * TotalFixedAllocators);
		_instance->_fixedMemoryManagers = static_cast<FixedMemoryManager**>(fixedArrayMemory);
		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			int totalBlockSize = 0;
			switch (_instance->AllowedFixedAllocators[i])
			{
			case 16:
				totalBlockSize = 500;
				break;

			case 20:
				totalBlockSize = 500;
				break;

			case 44:
				totalBlockSize = 500;
				break;

			case 60:
				totalBlockSize = 100;
				break;

			default:
				totalBlockSize = 500;
				break;
			}

			void* fixedAllocatorMemory = memoryManagerInstance->allocate(sizeof(FixedMemoryManager));
			_instance->_fixedMemoryManagers[i] = new(fixedAllocatorMemory)FixedMemoryManager();
			_instance->_fixedMemoryManagers[i]->create(
				_instance->AllowedFixedAllocators[i], memoryManagerInstance, totalBlockSize
			);
		}
	}

	void MemorySystem::createOtherMemoryManager(void* i_heapMemory, size_t i_heapTotalSize,
	                                            size_t i_maxBlockDescriptors)
	{
		const size_t memoryBlockSize = sizeof(MemoryBlock);
		void* otherHeap = static_cast<char*>(i_heapMemory) + memoryBlockSize;

		MemoryManager* memoryManagerInstance = MemoryManager::create(otherHeap, i_heapTotalSize,
		                                                             i_maxBlockDescriptors);

		MemoryBlock* memoryBlock = MemorySystem::getEmptyMemoryBlock(i_heapMemory);
		memoryBlock->heapMemory = i_heapMemory;
		memoryBlock->memoryManager = memoryManagerInstance;

		// Put it at the head as there will be less thrashing there
		memoryBlock->nextBlock = _instance->_memoryBlocks;

		_instance->_memoryBlocks = memoryBlock;
	}

#pragma endregion

#pragma region Allocations

	void* MemorySystem::allocate(const size_t i_contiguousMemorySizeRequired)
	{
		if (_instance == nullptr)
		{
			createMemorySystem();
		}

		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			if (_instance->_fixedMemoryManagers[i]->canHandleSize(i_contiguousMemorySizeRequired))
			{
				void* memory = _instance->_fixedMemoryManagers[i]->allocate(i_contiguousMemorySizeRequired);
				if (memory != nullptr)
				{
					return memory;
				}
			}
		}

		_instance->_memorySystemMutex.lock();

		MemoryBlock* head = _instance->_memoryBlocks;
		while (head != nullptr)
		{
			void* memory = head->memoryManager->allocate(i_contiguousMemorySizeRequired);
			if (memory != nullptr)
			{
				_instance->_memorySystemMutex.unlock();
				return memory;
			}

			head = head->nextBlock;
		}

		_instance->_memorySystemMutex.unlock();

		createManager();

		return _instance->_memoryBlocks->memoryManager->allocate(i_contiguousMemorySizeRequired);
	}

	void* MemorySystem::allocate(size_t i_contiguousMemorySizeRequired, unsigned i_alignment)
	{
		if (_instance == nullptr)
		{
			createMemorySystem();
		}

		_instance->_memorySystemMutex.lock();

		MemoryBlock* head = _instance->_memoryBlocks;
		while (head != nullptr)
		{
			void* memory = head->memoryManager->allocate(i_contiguousMemorySizeRequired, i_alignment);
			if (memory != nullptr)
			{
				_instance->_memorySystemMutex.unlock();
				return memory;
			}

			head = head->nextBlock;
		}

		_instance->_memorySystemMutex.unlock();

		createManager();

		return _instance->_memoryBlocks->memoryManager->allocate(i_contiguousMemorySizeRequired, i_alignment);
	}

	void* MemorySystem::reallocate(void* i_pointer, size_t i_contiguousMemorySizeRequired)
	{
		if (_instance == nullptr)
		{
			createMemorySystem();
		}

		_instance->_memorySystemMutex.lock();

		MemoryBlock* head = _instance->_memoryBlocks;
		while (head != nullptr)
		{
			void* memory = head->memoryManager->reallocate(i_pointer, i_contiguousMemorySizeRequired);
			if (memory != nullptr)
			{
				_instance->_memorySystemMutex.unlock();
				return memory;
			}

			head = head->nextBlock;
		}

		_instance->_memorySystemMutex.unlock();

		createManager();

		return _instance->_memoryBlocks->memoryManager->reallocate(i_pointer, i_contiguousMemorySizeRequired);
	}

	void* MemorySystem::reallocate(void* i_pointer, size_t i_contiguousMemorySizeRequired, unsigned i_alignment)
	{
		if (_instance == nullptr)
		{
			createMemorySystem();
		}

		_instance->_memorySystemMutex.lock();

		MemoryBlock* head = _instance->_memoryBlocks;
		while (head != nullptr)
		{
			void* memory = head->memoryManager->reallocate(i_pointer, i_contiguousMemorySizeRequired, i_alignment);
			if (memory != nullptr)
			{
				_instance->_memorySystemMutex.unlock();
				return memory;
			}

			head = head->nextBlock;
		}

		_instance->_memorySystemMutex.unlock();

		createManager();

		return _instance->_memoryBlocks->memoryManager->reallocate(i_pointer,
		                                                           i_contiguousMemorySizeRequired,
		                                                           i_alignment);
	}

#pragma endregion

#pragma region Free

	void MemorySystem::freeMem(void* i_pointer)
	{
		if (_instance == nullptr)
		{
			// At this point the Memory has been returned to the system.
			// So don't care about freeing Memory
			return;
		}

		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			if (_instance->_fixedMemoryManagers[i]->contains(i_pointer))
			{
				_instance->_fixedMemoryManagers[i]->freeMem(i_pointer);
				return;
			}
		}

		MemoryBlock* head = _instance->_memoryBlocks;
		while (head != nullptr)
		{
			if (head->memoryManager->contains(i_pointer))
			{
				head->memoryManager->freeMem(i_pointer);
				break;
			}

			head = head->nextBlock;
		}
	}

#pragma endregion

#pragma region Destroy

	void MemorySystem::destroy()
	{
		MemoryBlock* memoryManagerBlock = _instance->_memoryBlocks;
		while (memoryManagerBlock->nextBlock != nullptr)
		{
			memoryManagerBlock = memoryManagerBlock->nextBlock;
		}

		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			_instance->_fixedMemoryManagers[i]->destroy(memoryManagerBlock->memoryManager);
			memoryManagerBlock->memoryManager->freeMem(_instance->_fixedMemoryManagers[i]);
		}

		memoryManagerBlock->memoryManager->freeMem(_instance->_fixedMemoryManagers);

		returnMemoryToWindows();
	}

#pragma endregion

#pragma region Update

	void MemorySystem::Process(float i_deltaTime)
	{
		this->_currentCollectionTime -= i_deltaTime;
		if (this->_currentCollectionTime <= 0)
		{
			MemorySystem::collect();
			this->_currentCollectionTime = MemorySystem::CollectionTime;
		}
	}

#pragma endregion
}

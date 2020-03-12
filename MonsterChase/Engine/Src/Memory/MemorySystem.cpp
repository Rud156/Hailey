#include "MemorySystem.h"
#include "MemoryManager_Extern.h"
#include "FixedMemoryManager.h"

#include <Windows.h>

Memory::MemorySystem* memorySystem = nullptr;

namespace Memory
{
#pragma region Construction

	MemorySystem* MemorySystem::_instance = nullptr;

	MemorySystem::MemorySystem(): _heapMemory(nullptr), _fixedMemoryManagers(nullptr)
	{
	}

	MemorySystem::~MemorySystem()
	= default;

#pragma region Setup And Destory

	void MemorySystem::getMemoryFromWindows()
	{
		const size_t sizeHeap = 30000000; // This is about 30MB of Memory
		const unsigned int numDescriptors = 2048;
		void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);

		create(pHeapMemory, sizeHeap, numDescriptors);

		_instance->_heapMemory = pHeapMemory;
	}

	void MemorySystem::returnMemoryToWindows()
	{
		HeapFree(GetProcessHeap(), 0, _instance->_heapMemory);
		_instance = nullptr;
	}

#pragma endregion

#pragma endregion

#pragma region Creation

	void MemorySystem::create(void* i_heapMemoryStartAddress, size_t i_heapMemoryTotalSize,
	                          size_t i_maxBlockDescriptors)
	{
		const size_t overlordSize = sizeof(MemorySystem);
		_instance = new(i_heapMemoryStartAddress)MemorySystem();

		void* otherUseMemoryStartAddress = static_cast<char*>(i_heapMemoryStartAddress) + overlordSize;
		MemoryManager::create(otherUseMemoryStartAddress, i_heapMemoryTotalSize, i_maxBlockDescriptors);

		const size_t fixedMemoryManagerSize = sizeof(FixedMemoryManager*);
		void* fixedArrayMemory = memoryManager->allocate(fixedMemoryManagerSize * TotalFixedAllocators);
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

			void* fixedAllocatorMemory = memoryManager->allocate(sizeof(FixedMemoryManager));
			_instance->_fixedMemoryManagers[i] = new(fixedAllocatorMemory)FixedMemoryManager();
			_instance->_fixedMemoryManagers[i]->create(
				_instance->AllowedFixedAllocators[i], memoryManager, totalBlockSize
			);
		}

		memorySystem = _instance;
	}

#pragma endregion

#pragma region Allocations

	void* MemorySystem::allocate(const size_t i_contiguousMemorySizeRequired)
	{
		if (_instance == nullptr)
		{
			getMemoryFromWindows();
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

		return memoryManager->allocate(i_contiguousMemorySizeRequired);
	}

	void* MemorySystem::allocate(size_t i_contiguousMemorySizeRequired, unsigned i_alignment)
	{
		if (_instance == nullptr)
		{
			getMemoryFromWindows();
		}

		return memoryManager->allocate(i_contiguousMemorySizeRequired, i_alignment);
	}

	void* MemorySystem::reallocate(void* i_pointer, size_t i_contiguousMemorySizeRequired)
	{
		if (_instance == nullptr)
		{
			getMemoryFromWindows();
		}

		return memoryManager->reallocate(i_pointer, i_contiguousMemorySizeRequired);
	}

	void* MemorySystem::reallocate(void* i_pointer, size_t i_contiguousMemorySizeRequired, unsigned i_alignment)
	{
		if (_instance == nullptr)
		{
			getMemoryFromWindows();
		}

		return memoryManager->reallocate(i_pointer, i_contiguousMemorySizeRequired, i_alignment);
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

		memoryManager->freeMem(i_pointer);
	}

#pragma endregion

#pragma region Destroy

	void MemorySystem::destroy()
	{
		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			_instance->_fixedMemoryManagers[i]->destroy(memoryManager);
			memoryManager->freeMem(_instance->_fixedMemoryManagers[i]);
		}

		memoryManager->freeMem(_instance->_fixedMemoryManagers);
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

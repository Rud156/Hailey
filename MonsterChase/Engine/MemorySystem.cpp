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
		const size_t sizeHeap = 1024 * 1024;
		const unsigned int numDescriptors = 2048;
		void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);

		create(pHeapMemory, sizeHeap, numDescriptors);

		_instance->_heapMemory = pHeapMemory;
	}

	void MemorySystem::returnMemoryToWindows()
	{
		HeapFree(GetProcessHeap(), 0, _instance->_heapMemory);
	}

#pragma endregion

#pragma endregion

#pragma region Creation

	void MemorySystem::create(void* heapMemoryStartAddress, size_t heapMemoryTotalSize,
	                          size_t maxBlockDescriptors)
	{
		const size_t overlordSize = sizeof(MemorySystem);
		_instance = new(heapMemoryStartAddress)MemorySystem();

		void* otherUseMemoryStartAddress = static_cast<char*>(heapMemoryStartAddress) + overlordSize;
		MemoryManager::create(otherUseMemoryStartAddress, heapMemoryTotalSize, maxBlockDescriptors);

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

	void* MemorySystem::allocate(const size_t contiguousMemorySizeRequired)
	{
		if (_instance == nullptr)
		{
			getMemoryFromWindows();
		}

		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			if (_instance->_fixedMemoryManagers[i]->canHandleSize(contiguousMemorySizeRequired))
			{
				void* memory = _instance->_fixedMemoryManagers[i]->allocate(contiguousMemorySizeRequired);
				if (memory != nullptr)
				{
					return memory;
				}
			}
		}

		return memoryManager->allocate(contiguousMemorySizeRequired);
	}

	void* MemorySystem::allocate(size_t contiguousMemorySizeRequired, unsigned alignment)
	{
		if (_instance == nullptr)
		{
			getMemoryFromWindows();
		}

		return memoryManager->allocate(contiguousMemorySizeRequired, alignment);
	}

	void* MemorySystem::reallocate(void* pointer, size_t contiguousMemorySizeRequired)
	{
		if (_instance == nullptr)
		{
			getMemoryFromWindows();
		}

		return memoryManager->reallocate(pointer, contiguousMemorySizeRequired);
	}

	void* MemorySystem::reallocate(void* pointer, size_t contiguousMemorySizeRequired, unsigned alignment)
	{
		if (_instance == nullptr)
		{
			getMemoryFromWindows();
		}

		return memoryManager->reallocate(pointer, contiguousMemorySizeRequired, alignment);
	}

#pragma endregion

#pragma region Free

	void MemorySystem::freeMem(void* pointer)
	{
		if (_instance == nullptr)
		{
			// At this point the Memory has been returned to the system.
			// So don't care about freeing Memory
			return;
		}

		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			if (_instance->_fixedMemoryManagers[i]->contains(pointer))
			{
				_instance->_fixedMemoryManagers[i]->freeMem(pointer);
				return;
			}
		}

		memoryManager->freeMem(pointer);
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

		memoryManager->collect();
		memoryManager->showOutstandingMemory();
		memoryManager->showFreeBlocks();

		returnMemoryToWindows();
	}

#pragma endregion
}

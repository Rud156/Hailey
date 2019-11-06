#include "HeapManagerProxy.h"

#include <cassert>
#include "MemoryManager.h"

#define __TRACK_ALLOCATIONS

namespace HeapManagerProxy
{
	Memory::MemoryManager* CreateMemoryManager(void* i_pMemory, size_t i_sizeMemory,
	                                           unsigned int i_numDescriptors)
	{
		Memory::MemoryManager::Instance()->create(i_pMemory, i_sizeMemory, i_numDescriptors);
		return Memory::MemoryManager::Instance();
	}

	void Destroy(Memory::MemoryManager* i_pManager)
	{
		assert(i_pManager);

		delete i_pManager;
	}

	void* alloc(Memory::MemoryManager* i_pManager, size_t i_size)
	{
		assert(i_pManager);
		return i_pManager->allocate(i_size);
	}

	void* alloc(Memory::MemoryManager* i_pManager, size_t i_size, unsigned int i_alignment)
	{
		assert(i_pManager);

		return i_pManager->allocate(i_size, i_alignment);
	}

	void* realloc(Memory::MemoryManager* i_pManager, void* i_ptr, size_t i_size)
	{
		assert(i_pManager);

		return i_pManager->reallocate(i_ptr, i_size);
	}

	void* realloc(Memory::MemoryManager* i_pManager, void* i_ptr, size_t i_size, unsigned i_alignment)
	{
		assert(i_pManager);

		return i_pManager->reallocate(i_ptr, i_size, i_alignment);
	}

	bool free(Memory::MemoryManager* i_pManager, void* i_ptr)
	{
		assert(i_pManager);

		i_pManager->freeMem(i_ptr);
		return true;
	}

	void collect(Memory::MemoryManager* i_pManager)
	{
		assert(i_pManager);

		i_pManager->collect();
	}

	bool contains(Memory::MemoryManager* i_pManager, void* i_ptr)
	{
		assert(i_pManager);


		return i_pManager->contains(i_ptr);
	}

	bool isAllocated(Memory::MemoryManager* i_pManager, void* i_ptr)
	{
		assert(i_pManager);

		return i_pManager->isAllocated(i_ptr);
	}

	size_t getLargestFreeBlock(Memory::MemoryManager* i_pManager)
	{
		assert(i_pManager);

		return i_pManager->getLargestFreeBlockSize();
	}

	size_t getTotalFreeMemory(Memory::MemoryManager* i_pManager)
	{
		assert(i_pManager);

		return i_pManager->getTotalFreeMemory();
	}

	void showFreeBlocks(Memory::MemoryManager* i_pManager)
	{
		assert(i_pManager);

		i_pManager->showFreeBlocks();
	}

	void showOutstandingAllocations(const Memory::MemoryManager* i_pManager)
	{
		assert(i_pManager);

#ifdef __TRACK_ALLOCATIONS
		i_pManager->showOutstandingMemory();
#else
		printf("Memory::MemoryManager compiled without __TRACK_ALLOCATIONS defined.\n");
#endif
	}
} // namespace Memory::MemoryManagerProxy

#pragma once

#ifndef __HEAP_MANAGER_PROXY_H
#define __HEAP_MANAGER_PROXY_H
#include "MemoryManager.h"

namespace HeapManagerProxy
{
	Memory::MemoryManager* CreateMemoryManager(void* i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);
	void Destroy(Memory::MemoryManager* i_pManager);

	void* alloc(Memory::MemoryManager* i_pManager, size_t i_size);
	void* alloc(Memory::MemoryManager* i_pManager, size_t i_size, unsigned int i_alignment);
	void* realloc(Memory::MemoryManager* i_pManager, void* i_ptr, size_t i_size);
	void* realloc(Memory::MemoryManager* i_pManager, void* i_ptr, size_t i_size, unsigned int i_alignment);
	bool free(Memory::MemoryManager* i_pManager, void* i_ptr);

	void collect(Memory::MemoryManager* i_pManager);

	bool contains(Memory::MemoryManager* i_pManager, void* i_ptr);
	bool isAllocated(Memory::MemoryManager* i_pManager, void* i_ptr);

	size_t getLargestFreeBlock(Memory::MemoryManager* i_pManager);
	size_t getTotalFreeMemory(Memory::MemoryManager* i_pManager);

	void showFreeBlocks(Memory::MemoryManager* i_pManager);
	void showOutstandingAllocations(const Memory::MemoryManager* i_pManager);
} // namespace HeapManagerProxy

#endif // __HEAP_MANAGER_PROXY_H

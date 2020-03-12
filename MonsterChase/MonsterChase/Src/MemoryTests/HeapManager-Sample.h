#pragma once

// this is a sample of what your HeapManager class interface should look like.

class HeapManager
{
public:
	static HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);

	// allocates memory. named with a underscore to resolve name clash 
	void* _alloc(size_t i_bytes);
	// allocation with alignment. returns a block of memory with a given alignment
	void* _alloc(size_t i_bytes, unsigned int i_alignment);

	// frees an allocation
	void _free(void* i_ptr);

	// attempt to merge abutting blocks.
	void collect();

	// destroy the HeapManager
	void destroy();

	// tells us the size of the largest free block
	size_t getLargestFreeBlock();
	// tells us how much total memory is available
	size_t getTotalFreeMemory();

	// tells us if a pointer is within this HeapManagers managed memory
	bool Contains(void* i_ptr);
	// tells us if this pointer is an outstanding allocation from this block
	bool IsAllocated(void* i_ptr);

	// a debugging helper function to show us all the free blocks.
	void ShowFreeBlocks();
	// a debugging helper function to show us all the outstanding blocks.
};

#pragma once

namespace Memory
{
	class MemoryManager
	{
	private:
		// Fixed Constants
		const int EmptyBlockData = 0xCC;
		const int DeadBlockData = 0xFF;

		struct BlockDescriptor
		{
			size_t memorySize;
			void* memoryStartPointer;
			BlockDescriptor* previousBlockDescriptor;
			BlockDescriptor* nextBlockDescriptor;
		};

		// Base Memory Manager Data
		size_t _intSize;
		size_t _maxBlockDescriptors;
		size_t _blockDescriptorSize;
		size_t _blockDescriptorPointerSize;
		void* _memoryStartPointer;
		size_t _maxMemorySize;
		void* _userMemoryStartPointer;

		// BlockDescriptor List
		BlockDescriptor* _availableDescriptors;
		BlockDescriptor* _freeBlocks;
		// Fill this with the given Block Descriptors and Return user with only the data
		BlockDescriptor* _inUseBlockDescriptors;

		// Construction
		static MemoryManager* _instance;
		MemoryManager();

		// Creation
		void createBlockDescriptors();
		void createFreeBlock();
		BlockDescriptor* createAndGetEmptyBlockDescriptor(size_t descriptorOffsetPosition) const;

		// Allocation
		void* getFirstFittingFreeBlock(size_t sizeRequired);
		void* getFirstFittingFreeBlockAligned(size_t sizeRequired, size_t initialSizeToLeave, unsigned int alignment);

		// Quick Sort
		static void swap(BlockDescriptor* first, BlockDescriptor* second);
		static BlockDescriptor* getLastBlockDescriptor(BlockDescriptor* head);
		BlockDescriptor* partition(BlockDescriptor* left, BlockDescriptor* head) const;
		void quickSort(BlockDescriptor* left, BlockDescriptor* head) const;

		// Other Helpers
		inline static void printList(const char* headerString, BlockDescriptor* head);

	public:
		// Singleton
		static MemoryManager* Instance();
		~MemoryManager();

		// Variables
		size_t getMinimumToLeave() const;

		// Creation
		void create(void* heapMemoryStartAddress, size_t heapMemoryTotalSize, size_t maxBlockDescriptors);

		// Allocation
		void* allocate(size_t contiguousMemorySizeRequired);
		void* allocate(size_t contiguousMemorySizeRequired, unsigned int alignment);
		void* reallocate(void* pointer, size_t contiguousMemorySizeRequired);
		void* reallocate(void* pointer, size_t contiguousMemorySizeRequired, unsigned int alignment);

		// Free
		void freeMem(void* pointer);

		// Collection
		void collect();

		// Data Checks
		inline bool contains(void* pointer) const;
		inline bool isAllocated(void* pointer) const;

		// Info
		inline size_t getLargestFreeBlockSize() const;
		inline size_t getTotalFreeMemory() const;
		inline void showFreeBlocks() const;
		inline void showOutstandingMemory() const;
		inline void showAvailableBlocks() const;
	};
}

#include "MemoryManager_Inl.h"

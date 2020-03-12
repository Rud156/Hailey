#pragma once
#include <mutex>

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

		// Mutex
		std::mutex _memoryManagerMutex;

		// BlockDescriptor List
		BlockDescriptor* _availableDescriptors;
		BlockDescriptor* _freeBlocks;
		// Fill this with the given Block Descriptors and Return user with only the data
		BlockDescriptor* _inUseBlockDescriptors;

		// Construction
		static MemoryManager* _instance;
		MemoryManager();
		~MemoryManager();

		// Creation
		void createBlockDescriptors();
		void createFreeBlock();
		[[nodiscard]] BlockDescriptor* createAndGetEmptyBlockDescriptor(size_t i_descriptorOffsetPosition) const;

		// Allocation
		[[nodiscard]] void* getFirstFittingFreeBlock(size_t i_sizeRequired);
		[[nodiscard]] void* getFirstFittingFreeBlockAligned(size_t i_sizeRequired, size_t i_initialSizeToLeave,
		                                                    unsigned int i_alignment);

		// Quick Sort
		static void swap(BlockDescriptor* i_first, BlockDescriptor* i_second);
		static BlockDescriptor* getLastBlockDescriptor(BlockDescriptor* i_head);
		BlockDescriptor* partition(BlockDescriptor* i_left, BlockDescriptor* i_head) const;
		void quickSort(BlockDescriptor* i_left, BlockDescriptor* i_head) const;

		// Other Helpers
		inline static void printList(const char* i_headerString, BlockDescriptor* i_head);

	public:
		// Variables
		[[nodiscard]] size_t getMinimumToLeave() const;

		// Creation
		static void create(void* i_heapMemoryStartAddress, size_t i_heapMemoryTotalSize, size_t i_maxBlockDescriptors);

		// Allocation
		void* allocate(size_t i_contiguousMemorySizeRequired);
		void* allocate(size_t i_contiguousMemorySizeRequired, unsigned int i_alignment);
		void* reallocate(void* i_pointer, size_t i_contiguousMemorySizeRequired);
		void* reallocate(void* i_pointer, size_t i_contiguousMemorySizeRequired, unsigned int i_alignment);

		// Free
		void freeMem(void* i_pointer);

		// Collection
		void collect();

		// Data Checks
		[[nodiscard]] inline bool contains(void* i_pointer) const;
		[[nodiscard]] inline bool isAllocated(void* i_pointer) const;

		// Info
		[[nodiscard]] inline size_t getLargestFreeBlockSize() const;
		[[nodiscard]] inline size_t getTotalFreeMemory() const;
		inline void showFreeBlocks() const;
		inline void showOutstandingMemory() const;
		inline void showAvailableBlocks() const;
	};
}

#include "MemoryManager_Inl.h"

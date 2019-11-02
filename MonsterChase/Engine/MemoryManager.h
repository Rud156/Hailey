#pragma once
#include <cstdio>

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


	// Data Checks

	inline bool MemoryManager::contains(void* pointer) const
	{
		void* startPointer = this->_memoryStartPointer;
		void* endPointer = static_cast<char*>(this->_memoryStartPointer) + this->_maxMemorySize;

		if (pointer >= startPointer && pointer <= endPointer)
		{
			return true;
		}

		return false;
	}

	inline bool MemoryManager::isAllocated(void* pointer) const
	{
		BlockDescriptor* inUseBlock = this->_inUseBlockDescriptors;
		if (inUseBlock == nullptr)
		{
			return false;
		}

		while (inUseBlock != nullptr)
		{
			void* startPointer = inUseBlock->memoryStartPointer;
			void* endPointer = static_cast<char*>(inUseBlock->memoryStartPointer) + inUseBlock->memorySize;

			if (pointer >= startPointer && pointer <= endPointer)
			{
				return true;
			}

			inUseBlock = inUseBlock->nextBlockDescriptor;
		}

		return false;
	}

	// Data Checks

	// Info

	inline size_t MemoryManager::getLargestFreeBlockSize() const
	{
		if (this->_freeBlocks == nullptr)
		{
			return 0;
		}

		BlockDescriptor* freeBlock = this->_freeBlocks;
		size_t freeBlockSize = freeBlock->memorySize;

		while (freeBlock != nullptr)
		{
			if (freeBlock->memorySize > freeBlockSize)
			{
				freeBlockSize = freeBlock->memorySize;
			}

			freeBlock = freeBlock->nextBlockDescriptor;
		}

		return freeBlockSize;
	}

	inline size_t MemoryManager::getTotalFreeMemory() const
	{
		size_t totalFreeMemory = 0;
		BlockDescriptor* freeBlock = this->_freeBlocks;
		while (freeBlock != nullptr)
		{
			totalFreeMemory += freeBlock->memorySize;
			freeBlock = freeBlock->nextBlockDescriptor;
		}

		return totalFreeMemory;
	}

	inline void MemoryManager::showFreeBlocks() const
	{
		printList("Free Blocks", this->_freeBlocks);
	}

	inline void MemoryManager::showOutstandingMemory() const
	{
		printList("OutStanding Blocks", this->_inUseBlockDescriptors);
	}

	inline void MemoryManager::showAvailableBlocks() const
	{
		printList("Available Blocks", this->_availableDescriptors);
	}

	// Info

	// Helper Methods

	inline void MemoryManager::printList(const char* headerString, BlockDescriptor* head)
	{
		printf_s("%s\n", headerString);

		BlockDescriptor* headBlock = head;
		while (headBlock != nullptr)
		{
			printf_s("Size: %zu\n", headBlock->memorySize);
			printf_s("Address: %p\n", &headBlock->memoryStartPointer);
			printf_s("================\n");

			headBlock = headBlock->nextBlockDescriptor;
		}
	}

	// Helper Methods
}

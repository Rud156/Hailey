#pragma once
#include <cstdio>

namespace Memory
{
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
		printf_s("=====================================\n");

		BlockDescriptor* headBlock = head;
		while (headBlock != nullptr)
		{
			printf_s("Address => %p\t||\tSize => %zu\n", &headBlock->memoryStartPointer, headBlock->memorySize);

			headBlock = headBlock->nextBlockDescriptor;
		}
		printf_s("\n");
	}

	// Helper Methods
}

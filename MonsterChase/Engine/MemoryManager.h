#pragma once

namespace Memory
{
	class MemoryManager
	{
	private:
		// Fixed Constants
		const int GuardBlockSize = 4;
		const int EmptyBlockData = 0xCC;
		const int DeadBlockData = 0xFF;

		struct BlockDescriptor
		{
			size_t memorySize;
			size_t memoryStartAddress;
			BlockDescriptor* nextBlockDescriptor;
		};

		// Base Memory Manager Data
		size_t _maxBlockDescriptors;
		size_t _blockDescriptorSize;
		size_t _blockDescriptorPointerSize;
		void* _memoryStartPointer;
		size_t _maxMemorySize;
		size_t _userMemoryStartAddress;

		// BlockDescriptor List
		BlockDescriptor* _availableDescriptors;
		BlockDescriptor* _outstandingAllocations;
		BlockDescriptor* _freeBlocks;

		// Creation
		void createBlockDescriptors();
		void createFreeBlock();
		BlockDescriptor* createAndGetEmptyBlockDescriptor(int descriptorOffsetPosition) const;

		// Allocation
		void* getFirstFreeBlock(size_t sizeRequired);

	public:
		MemoryManager();
		~MemoryManager();

		void create(void* heapMemoryStartAddress, size_t heapMemoryTotalSize, size_t maxBlockDescriptors);
		void* allocate(size_t contiguousMemorySizeRequired);
		void* allocate(size_t contiguousMemorySizeRequired, unsigned int alignment);
	};
}

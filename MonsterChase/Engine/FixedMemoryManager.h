#pragma once


namespace Containers
{
	class BitArray;
}

namespace Memory
{
	class MemoryManager;

	class FixedMemoryManager
	{
	private:
		static const int DeadBlockData = 0xFF;

		// Memory Mapper
		size_t _fixedMemoryBlockSize;
		size_t _totalUserMemorySize;
		long _totalBitsCount;

		// 1 -> Means that the memory is empty, 0 -> Means that memory is being used
		Containers::BitArray* _memoryMapper;
		void* _userMemoryStartPointer;

		// Destruction
		~FixedMemoryManager();

	public:

		// Construction
		FixedMemoryManager();

		// Setup
		void create(size_t memoryBlockSize, MemoryManager* memoryManager, long totalBitsCount = 1000);

		// Allocation
		void* allocate(size_t contiguousMemorySize) const;

		// Free
		void freeMem(void* pointer) const;

		// Destroy
		void destroy(MemoryManager* memoryManager) const;

		// Data Checks
		inline bool canHandleSize(size_t inputSize) const;
		inline bool contains(void* pointer) const;
		inline bool isAllocated(void* pointer) const;
	};
}

#include "FixedMemoryManager_Inl.h"

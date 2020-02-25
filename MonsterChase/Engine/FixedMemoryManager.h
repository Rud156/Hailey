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
		void create(size_t i_memoryBlockSize, MemoryManager* i_memoryManager, long i_totalBitsCount = 1000);

		// Allocation
		[[nodiscard]] void* allocate(size_t i_contiguousMemorySize) const;

		// Free
		void freeMem(void* i_pointer) const;

		// Destroy
		void destroy(MemoryManager* i_memoryManager) const;

		// Data Checks
		[[nodiscard]] inline bool canHandleSize(size_t i_inputSize) const;
		[[nodiscard]] inline bool contains(void* i_pointer) const;
		[[nodiscard]] inline bool isAllocated(void* i_pointer) const;
	};
}

#include "FixedMemoryManager_Inl.h"

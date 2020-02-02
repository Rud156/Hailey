#pragma once

namespace Memory
{
	class FixedMemoryManager;
	class MemoryManager;

	class MemorySystem
	{
	private:
		// Fixed Allocators
		static const size_t TotalFixedAllocators = 4;
		const int AllowedFixedAllocators[TotalFixedAllocators] = {16, 20, 44, 60};

		// Memory
		void* _heapMemory;

		FixedMemoryManager** _fixedMemoryManagers;

		// Construction
		static MemorySystem* _instance;
		MemorySystem();
		~MemorySystem();

		// Setup
		static void getMemoryFromWindows();
		// Destroy
		static void returnMemoryToWindows();

	public:
		// Creation
		static void create(void* heapMemoryStartAddress, size_t heapMemoryTotalSize, size_t maxBlockDescriptors);

		// Allocation
		static void* allocate(size_t contiguousMemorySizeRequired);
		static void* allocate(size_t contiguousMemorySizeRequired, unsigned int alignment);
		static void* reallocate(void* pointer, size_t contiguousMemorySizeRequired);
		static void* reallocate(void* pointer, size_t contiguousMemorySizeRequired, unsigned int alignment);

		// Free
		static void freeMem(void* pointer);

		// Destroy
		static void destroy();

		// Collection
		static inline void collect();

		// Data Checks
		inline bool contains(void* pointer) const;
		inline bool isAllocated(void* pointer) const;
	};
}

#include "MemorySystem_Inl.h"

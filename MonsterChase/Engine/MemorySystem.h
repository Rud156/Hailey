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
		static void create(void* i_heapMemoryStartAddress, size_t i_heapMemoryTotalSize, size_t i_maxBlockDescriptors);

		// Allocation
		[[nodiscard]] static void* allocate(size_t i_contiguousMemorySizeRequired);
		[[nodiscard]] static void* allocate(size_t i_contiguousMemorySizeRequired, unsigned int i_alignment);
		[[nodiscard]] static void* reallocate(void* i_pointer, size_t i_contiguousMemorySizeRequired);
		[[nodiscard]] static void* reallocate(void* i_pointer, size_t i_contiguousMemorySizeRequired,
		                                      unsigned int i_alignment);

		// Free
		static void freeMem(void* i_pointer);

		// Destroy
		static void destroy();

		// Collection
		static inline void collect();

		// Data Checks
		[[nodiscard]] inline bool contains(void* i_pointer) const;
		[[nodiscard]] inline bool isAllocated(void* i_pointer) const;
	};
}

#include "MemorySystem_Inl.h"

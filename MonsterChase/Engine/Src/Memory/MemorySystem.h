#pragma once
#include <mutex>

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

		struct MemoryBlock
		{
			MemoryManager* memoryManager;
			void* heapMemory;
			MemoryBlock* nextBlock;
		};

		void* _instanceHeapMemory;

		std::mutex _memorySystemMutex;
		MemoryBlock* _memoryBlocks; // Linked List of MemoryManagers
		FixedMemoryManager** _fixedMemoryManagers;

		// Process
		const float CollectionTime = 60; // Auto Collection of Memory Every 60s
		float _currentCollectionTime = CollectionTime;

		// Construction
		static MemorySystem* _instance;
		MemorySystem();
		~MemorySystem();

		// Setup
		size_t _currentSize = 30;
		static MemoryBlock* getEmptyMemoryBlock(void* i_memory);

		// Creation
		static void createMemorySystem();
		static void createManager();
		static void createInitialMemoryManager(void* i_heapMemory, size_t i_heapTotalSize,
		                                       size_t i_maxBlockDescriptors);
		static void createOtherMemoryManager(void* i_heapMemory, size_t i_heapTotalSize, size_t i_maxBlockDescriptors);

		// Destroy
		static void returnMemoryToWindows();

	public:
		// Creation
		static void setupMemorySystem(void* i_heapMemoryStartAddress);

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

		// Auto Collect and Arrange Memory after sometime. Something like GoLang
		void Process(float i_deltaTime);

		// Data Checks
		[[nodiscard]] inline bool contains(void* i_pointer) const;
		[[nodiscard]] inline bool isAllocated(void* i_pointer) const;
		[[nodiscard]] static inline size_t getMinimumToLeave();
	};
}

#include "MemorySystem_Inl.h"

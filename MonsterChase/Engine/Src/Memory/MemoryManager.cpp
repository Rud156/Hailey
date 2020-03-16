#include "MemoryManager.h"
#include "MemoryManager_Extern.h"
#include "../Utils/MathUtils.h"
#include "../Utils/Debug.h"
#include "../Externals/StackTrace/call_stack.hpp"

#include <memory>
#include <cassert>
#include <chrono>

Memory::MemoryManager* memoryManager = nullptr;

namespace Memory
{
	// Singleton

	MemoryManager* MemoryManager::_instance = nullptr;

	MemoryManager::MemoryManager(): _intSize(0), _maxBlockDescriptors(0), _blockDescriptorSize(0),
	                                _blockDescriptorPointerSize(0), _memoryStartPointer(nullptr),
	                                _maxMemorySize(0),
	                                _userMemoryStartPointer(nullptr),
	                                _availableDescriptors(nullptr),
	                                _freeBlocks(nullptr),
	                                _inUseBlockDescriptors(nullptr)
	{
		// Constructor must be empty and not call any reference
		// Or a recursive StackOverflow exception will occur
	}

	MemoryManager::~MemoryManager() = default;

	size_t MemoryManager::getMinimumToLeave() const
	{
		return sizeof(MemoryManager) + this->_blockDescriptorSize * this->_maxBlockDescriptors;
	}

	// Singleton

	// Creation
	MemoryManager* MemoryManager::create(void* i_heapMemoryStartAddress, const size_t i_heapMemoryTotalSize,
	                                     const size_t i_maxBlockDescriptors)
	{
		const size_t memoryManagerSize = sizeof(MemoryManager);
		_instance = new(i_heapMemoryStartAddress)MemoryManager();

		_instance->_maxBlockDescriptors = i_maxBlockDescriptors;
		_instance->_blockDescriptorSize = sizeof(BlockDescriptor);
		_instance->_blockDescriptorPointerSize = sizeof(BlockDescriptor*);
		_instance->_intSize = sizeof(int);

		_instance->_maxMemorySize = i_heapMemoryTotalSize - memoryManagerSize;
		_instance->_userMemoryStartPointer = static_cast<char*>(i_heapMemoryStartAddress) +
			i_maxBlockDescriptors * _instance->_blockDescriptorSize + memoryManagerSize;
		_instance->_memoryStartPointer = static_cast<void*>(static_cast<char*>(i_heapMemoryStartAddress) +
			memoryManagerSize);

		_instance->_availableDescriptors = nullptr;
		_instance->_freeBlocks = nullptr;
		_instance->_inUseBlockDescriptors = nullptr;

		_instance->createBlockDescriptors();
		_instance->createFreeBlock();

		memoryManager = _instance;
		return _instance;
	}

	void MemoryManager::createBlockDescriptors()
	{
		// Just added to keep a reference to the previous descriptor
		BlockDescriptor* previousBlockDescriptor = nullptr;

		// This creates a list of BlockDescriptors
		for (size_t i = 0; i < _maxBlockDescriptors; i++)
		{
			const size_t offsetPosition = i * this->_blockDescriptorSize;

			BlockDescriptor* blockDescriptor = this->createAndGetEmptyBlockDescriptor(offsetPosition);
			blockDescriptor->previousBlockDescriptor = previousBlockDescriptor;
			blockDescriptor->nextBlockDescriptor = this->_availableDescriptors;

			previousBlockDescriptor = blockDescriptor;
			this->_availableDescriptors = blockDescriptor;
		}
	}

	// Allocates Memory for BlockDescriptor from the Initial Heap Memory and returns it
	MemoryManager::BlockDescriptor* MemoryManager::createAndGetEmptyBlockDescriptor(
		const size_t i_descriptorOffsetPosition) const
	{
		const auto blockDescriptor = new(static_cast<void*>(
				static_cast<char*>(this->_memoryStartPointer) + i_descriptorOffsetPosition
			))
			BlockDescriptor();

		blockDescriptor->memoryStartPointer = nullptr;
		blockDescriptor->previousBlockDescriptor = nullptr;
		blockDescriptor->nextBlockDescriptor = nullptr;
		blockDescriptor->memorySize = 0;

		return blockDescriptor;
	}

	void MemoryManager::createFreeBlock()
	{
		// Completely exit if no descriptors are available
		// This should never happen
		assert(this->_availableDescriptors != nullptr);

		BlockDescriptor* freeMemoryBlockDescriptor = this->_availableDescriptors;
		this->_availableDescriptors = this->_availableDescriptors->nextBlockDescriptor;
		this->_availableDescriptors->previousBlockDescriptor = nullptr;

		freeMemoryBlockDescriptor->previousBlockDescriptor = nullptr;
		freeMemoryBlockDescriptor->nextBlockDescriptor = nullptr;
		freeMemoryBlockDescriptor->memoryStartPointer = this->_userMemoryStartPointer;
		freeMemoryBlockDescriptor->memorySize = this->_maxMemorySize -
			(this->_maxBlockDescriptors * this->_blockDescriptorSize);

		this->_freeBlocks = freeMemoryBlockDescriptor;
	}

	// Creation

	// Allocation

	void* MemoryManager::allocate(const size_t i_contiguousMemorySizeRequired)
	{
		this->_memoryManagerMutex.lock();

		// Return NullPtr if there are no BlockDescriptors available
		if (_availableDescriptors == nullptr)
		{
			Utils::Debug::LogOutputToWindow("=============Stack Trace==============\n");
			Utils::Debug::LogOutputToWindow("Out of Memory!!!\n");
			// const stacktrace::call_stack st;
			// Utils::Debug::LogOutputToWindow(st.to_string().c_str());

			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		const size_t totalRequiredMemorySize = this->_blockDescriptorPointerSize + this->_intSize * 2 +
			i_contiguousMemorySizeRequired;

		this->_memoryManagerMutex.unlock();
		void* memoryAddress = this->getFirstFittingFreeBlock(totalRequiredMemorySize);
		this->_memoryManagerMutex.lock();

		// Return NullPtr if there is no consecutive memory fit available
		if (memoryAddress == nullptr || this->_availableDescriptors == nullptr)
		{
			Utils::Debug::LogOutputToWindow("=============Stack Trace==============\n");
			Utils::Debug::LogOutputToWindow("Out of Memory!!!\n");
			// const stacktrace::call_stack st;
			// Utils::Debug::LogOutputToWindow(st.to_string().c_str());

			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		// At this point we are definitely sure that memory can be provided

		// Get the head BlockDescriptor address to send to the user
		BlockDescriptor* headBlockDescriptor = this->_availableDescriptors;
		this->_availableDescriptors = headBlockDescriptor->nextBlockDescriptor;
		// This only happens when there are no more BlockDescriptors left
		if (this->_availableDescriptors != nullptr)
		{
			this->_availableDescriptors->previousBlockDescriptor = nullptr;
		}

		headBlockDescriptor->memorySize = totalRequiredMemorySize;
		headBlockDescriptor->memoryStartPointer = memoryAddress;

		// Assign a pointer to the BlockDescriptor that was taken from the AvailableBlockDescriptors
		*static_cast<BlockDescriptor**>(memoryAddress) = headBlockDescriptor;

		// Put the block descriptor from the AvailableBlockDescriptor to the InUseBlockDescriptors
		headBlockDescriptor->nextBlockDescriptor = this->_inUseBlockDescriptors;
		headBlockDescriptor->previousBlockDescriptor = nullptr; // This is always NULL as it is attached to the head
		// Handle the case when there are more than 0 BlockDescriptors in the InUseList already
		if (_inUseBlockDescriptors != nullptr)
		{
			this->_inUseBlockDescriptors->previousBlockDescriptor = headBlockDescriptor;
		}
		this->_inUseBlockDescriptors = headBlockDescriptor;

		void* userMemoryAddress = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize + this->_intSize); // Assign the User Address

		void* firstGuardPosition = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize);
		*static_cast<int*>(firstGuardPosition) = this->DeadBlockData; // Assign the First Guard Block

		void* secondGuardPosition = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize + this->_intSize + i_contiguousMemorySizeRequired);
		*static_cast<int*>(secondGuardPosition) = this->DeadBlockData; // Assign the Second Guard Block

		this->_memoryManagerMutex.unlock();
		return userMemoryAddress;
	}

	void* MemoryManager::allocate(const size_t i_contiguousMemorySizeRequired, const unsigned int i_alignment)
	{
		this->_memoryManagerMutex.lock();

		// Return NullPtr if there are no BlockDescriptors available
		if (_availableDescriptors == nullptr)
		{
			Utils::Debug::LogOutputToWindow("=============Stack Trace==============\n");
			Utils::Debug::LogOutputToWindow("Out of Memory!!!\n");
			// const stacktrace::call_stack st;
			// Utils::Debug::LogOutputToWindow(st.to_string().c_str());

			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		const size_t initialSizeToLeave = this->_blockDescriptorPointerSize + this->_intSize;
		const size_t totalMemorySize = initialSizeToLeave + i_contiguousMemorySizeRequired + this->_intSize;

		this->_memoryManagerMutex.unlock();
		void* memoryAddress = this->getFirstFittingFreeBlockAligned(totalMemorySize, initialSizeToLeave, i_alignment);
		this->_memoryManagerMutex.lock();

		if (memoryAddress == nullptr || this->_availableDescriptors == nullptr)
		{
			Utils::Debug::LogOutputToWindow("=============Stack Trace==============\n");
			Utils::Debug::LogOutputToWindow("Out of Memory!!!\n");
			// const stacktrace::call_stack st;
			// Utils::Debug::LogOutputToWindow(st.to_string().c_str());

			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		const size_t alignmentAmount = *static_cast<size_t*>(memoryAddress);
		const size_t totalAdjustedMemorySize = totalMemorySize + alignmentAmount;

		// At this point we are definitely sure that memory can be provided

		// Get the head BlockDescriptor address to send to the user
		BlockDescriptor* headBlockDescriptor = this->_availableDescriptors;
		this->_availableDescriptors = headBlockDescriptor->nextBlockDescriptor;
		// This only happens when there are no more BlockDescriptors left
		if (this->_availableDescriptors != nullptr)
		{
			this->_availableDescriptors->previousBlockDescriptor = nullptr;
		}

		headBlockDescriptor->memorySize = totalAdjustedMemorySize;
		headBlockDescriptor->memoryStartPointer = memoryAddress;

		// Assign a pointer to the BlockDescriptor that was taken from the AvailableBlockDescriptors
		void* blockDescriptorPosition = static_cast<void*>(static_cast<char*>(memoryAddress) + alignmentAmount);
		*static_cast<BlockDescriptor**>(blockDescriptorPosition) = headBlockDescriptor;

		// Put the block descriptor from the AvailableBlockDescriptor to the InUseBlockDescriptors
		headBlockDescriptor->nextBlockDescriptor = this->_inUseBlockDescriptors;
		headBlockDescriptor->previousBlockDescriptor = nullptr; // This is always NULL as it is attached to the head
		// Handle the case when there are more than 0 BlockDescriptors in the InUseList already
		if (_inUseBlockDescriptors != nullptr)
		{
			this->_inUseBlockDescriptors->previousBlockDescriptor = headBlockDescriptor;
		}
		this->_inUseBlockDescriptors = headBlockDescriptor;

		void* userMemoryAddress = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize + this->_intSize + alignmentAmount); // Assign the User Address

		void* firstGuardPosition = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize + alignmentAmount);
		*static_cast<int*>(firstGuardPosition) = this->DeadBlockData; // Assign the First Guard Block

		void* secondGuardPosition = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize + this->_intSize + i_contiguousMemorySizeRequired + alignmentAmount);
		*static_cast<int*>(secondGuardPosition) = this->DeadBlockData; // Assign the Second Guard Block

		this->_memoryManagerMutex.unlock();
		return userMemoryAddress;
	}

	void* MemoryManager::reallocate(void* i_pointer, const size_t i_contiguousMemorySizeRequired)
	{
		this->_memoryManagerMutex.lock();

		if (i_pointer == nullptr)
		{
			Utils::Debug::LogOutputToWindow("\nTrying to reallocate NULLPTR\n");

			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		void* userMemoryAddress = this->allocate(i_contiguousMemorySizeRequired);

		if (userMemoryAddress == nullptr)
		{
			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		size_t pointerIndex = 0;

		while (true)
		{
			// This is given such that the data does not overflow into the older pointers
			const int deadBlockCheck = *static_cast<int*>(static_cast<void*>(static_cast<char*>(i_pointer) +
				pointerIndex));
			const int newMemoryDeadBlockCheck = *static_cast<int*>(static_cast<void*>(
				static_cast<char*>(userMemoryAddress) + pointerIndex));
			if (deadBlockCheck == this->DeadBlockData || newMemoryDeadBlockCheck == this->DeadBlockData)
			{
				break;
			}

			// Copy data between pointers
			*(static_cast<char*>(userMemoryAddress) + pointerIndex) = *(static_cast<char*>(i_pointer) + pointerIndex);
			pointerIndex += 1;
		}

		this->_memoryManagerMutex.unlock();

		// Free the Old Pointer and Return New Pointer
		this->freeMem(i_pointer);
		return userMemoryAddress;
	}

	void* MemoryManager::reallocate(void* i_pointer, const size_t i_contiguousMemorySizeRequired,
	                                const unsigned int i_alignment)
	{
		this->_memoryManagerMutex.lock();

		if (i_pointer == nullptr)
		{
			Utils::Debug::LogOutputToWindow("\nTrying to reallocate NULLPTR\n");

			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		void* userMemoryAddress = this->allocate(i_contiguousMemorySizeRequired, i_alignment);

		if (userMemoryAddress == nullptr)
		{
			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		size_t pointerIndex = 0;

		while (true)
		{
			// This is given such that the data does not overflow into the older pointers
			const int deadBlockCheck = *static_cast<int*>(static_cast<void*>(static_cast<char*>(i_pointer) +
				pointerIndex));
			const int newMemoryDeadBlockCheck = *static_cast<int*>(static_cast<void*>(
				static_cast<char*>(userMemoryAddress) + pointerIndex));
			if (deadBlockCheck == this->DeadBlockData || newMemoryDeadBlockCheck == this->DeadBlockData)
			{
				break;
			}

			// Copy data between pointers
			*(static_cast<char*>(userMemoryAddress) + pointerIndex) = *(static_cast<char*>(i_pointer) + pointerIndex);
			pointerIndex += 1;
		}

		this->_memoryManagerMutex.unlock();

		// Free the Old Pointer and Return New Pointer
		this->freeMem(i_pointer);
		return userMemoryAddress;
	}

	void* MemoryManager::getFirstFittingFreeBlock(const size_t i_sizeRequired)
	{
		this->_memoryManagerMutex.lock();

		// Return NULL if there are no FreeBlock available
		if (this->_freeBlocks == nullptr || this->_availableDescriptors == nullptr)
		{
			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		BlockDescriptor* freeBlockPointer = this->_freeBlocks;

		// Loop through the Free Block List and find a Block that as the required size
		// Basically (First Fit)
		while (freeBlockPointer != nullptr)
		{
			if (freeBlockPointer->memorySize < i_sizeRequired)
			{
				freeBlockPointer = freeBlockPointer->nextBlockDescriptor;
				continue;
			}

			// Break on finding it
			break;
		}
		// InCase no matching size was found
		if (freeBlockPointer == nullptr)
		{
			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		// freeBlockPointer now points towards the BlockDescriptor that has the required Size
		// freeBlockPointerPrevious points to the previous BlockDescriptor

		// Calculate the amount of memory left in the FreeBlock after user memory is subtracted
		const size_t freeBlockMemorySizeLeft = freeBlockPointer->memorySize - i_sizeRequired;

		// Find the user memory as this is the one that will be returned
		void* userMemory = freeBlockPointer->memoryStartPointer;

		// Just Reduce the BlockDescriptor size in case the whole of it is not used
		if (freeBlockMemorySizeLeft > 0)
		{
			freeBlockPointer->memorySize = freeBlockMemorySizeLeft;
			freeBlockPointer->memoryStartPointer = static_cast<void*>(static_cast<char*>(
				freeBlockPointer->memoryStartPointer) + i_sizeRequired);
		}
			// In Case the whole is Used...
		else
		{
			// If the previous is not null, then make the previous->next the current->next
			// And remove the current from the middle
			// Previous -> Current -> Next
			// Previous -> Next
			if (freeBlockPointer->previousBlockDescriptor != nullptr)
			{
				freeBlockPointer->previousBlockDescriptor->nextBlockDescriptor = freeBlockPointer->nextBlockDescriptor;

				if (freeBlockPointer->nextBlockDescriptor != nullptr)
				{
					freeBlockPointer->nextBlockDescriptor->previousBlockDescriptor =
						freeBlockPointer->previousBlockDescriptor;
				}
			}
				// This means that the current is the head of the Block
				// Just put in the next
			else
			{
				this->_freeBlocks = this->_freeBlocks->nextBlockDescriptor;
				if (this->_freeBlocks != nullptr)
				{
					this->_freeBlocks->previousBlockDescriptor = nullptr;
				}
			}

			// Return the Current to the _availableDescriptors LinkedList
			freeBlockPointer->nextBlockDescriptor = this->_availableDescriptors;
			if (this->_availableDescriptors->nextBlockDescriptor != nullptr)
			{
				this->_availableDescriptors->nextBlockDescriptor->previousBlockDescriptor = freeBlockPointer;
			}
			this->_availableDescriptors = freeBlockPointer;
		}

		this->_memoryManagerMutex.unlock();
		return userMemory;
	}

	void* MemoryManager::getFirstFittingFreeBlockAligned(const size_t i_sizeRequired, const size_t i_initialSizeToLeave,
	                                                     const unsigned int i_alignment)
	{
		this->_memoryManagerMutex.lock();

		// Return NULL if there are no FreeBlock available
		if (this->_freeBlocks == nullptr || this->_availableDescriptors == nullptr)
		{
			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		BlockDescriptor* freeBlockPointer = this->_freeBlocks;
		size_t alignmentAmount = 0;

		// Loop through the Free Block List and find a Block that as the required size
		// Basically (First Fit)
		while (freeBlockPointer != nullptr)
		{
			if (freeBlockPointer->memorySize < i_sizeRequired)
			{
				freeBlockPointer = freeBlockPointer->nextBlockDescriptor;
				continue;
			}

			if (freeBlockPointer == nullptr)
			{
				break;
			}

			void* startPosition = freeBlockPointer->memoryStartPointer;
			void* probableUserMemoryStartPosition = static_cast<void*>(static_cast<char*>(startPosition) +
				i_initialSizeToLeave);

			const auto pointerAddress = reinterpret_cast<size_t>(probableUserMemoryStartPosition);
			const size_t nextClosestMultiple = Utils::MathUtils::GetRoundNextMultiple(pointerAddress, i_alignment);
			alignmentAmount = nextClosestMultiple - pointerAddress;

			const size_t totalAdjustedSize = i_sizeRequired + alignmentAmount;
			if (freeBlockPointer->memorySize >= totalAdjustedSize)
			{
				break;
			}

			freeBlockPointer = freeBlockPointer->nextBlockDescriptor;
		}
		// InCase no matching size was found
		if (freeBlockPointer == nullptr)
		{
			this->_memoryManagerMutex.unlock();
			return nullptr;
		}

		const size_t totalSizeRequired = i_sizeRequired + alignmentAmount;

		// freeBlockPointer now points towards the BlockDescriptor that has the required Size
		// freeBlockPointerPrevious points to the previous BlockDescriptor

		// Calculate the amount of memory left in the FreeBlock after user memory is subtracted
		const size_t freeBlockMemorySizeLeft = freeBlockPointer->memorySize - totalSizeRequired;

		// Find the user memory as this is the one that will be returned
		void* userMemory = freeBlockPointer->memoryStartPointer;

		// Just Reduce the BlockDescriptor size in case the whole of it is not used
		if (freeBlockMemorySizeLeft > 0)
		{
			freeBlockPointer->memorySize = freeBlockMemorySizeLeft;
			freeBlockPointer->memoryStartPointer = static_cast<void*>(static_cast<char*>(
				freeBlockPointer->memoryStartPointer) + totalSizeRequired);
		}
			// In Case the whole is Used...
		else
		{
			// If the previous is not null, then make the previous->next the current->next
			// And remove the current from the middle
			// Previous -> Current -> Next
			// Previous -> Next
			if (freeBlockPointer->previousBlockDescriptor != nullptr)
			{
				freeBlockPointer->previousBlockDescriptor->nextBlockDescriptor = freeBlockPointer->nextBlockDescriptor;

				if (freeBlockPointer->nextBlockDescriptor != nullptr)
				{
					freeBlockPointer->nextBlockDescriptor->previousBlockDescriptor =
						freeBlockPointer->previousBlockDescriptor;
				}
			}
				// This means that the current is the head of the Block
				// Just put in the next
			else
			{
				this->_freeBlocks = this->_freeBlocks->nextBlockDescriptor;
				if (this->_freeBlocks != nullptr)
				{
					this->_freeBlocks->previousBlockDescriptor = nullptr;
				}
			}

			// Return the Current to the _availableDescriptors LinkedList
			freeBlockPointer->nextBlockDescriptor = this->_availableDescriptors;
			if (this->_availableDescriptors->nextBlockDescriptor != nullptr)
			{
				this->_availableDescriptors->nextBlockDescriptor->previousBlockDescriptor = freeBlockPointer;
			}
			this->_availableDescriptors = freeBlockPointer;
		}

		*static_cast<size_t*>(userMemory) = alignmentAmount;

		this->_memoryManagerMutex.unlock();
		return userMemory;
	}

	// Allocation

	// Free Memory

	void MemoryManager::freeMem(void* i_pointer)
	{
		this->_memoryManagerMutex.lock();

		if (i_pointer == nullptr)
		{
			Utils::Debug::LogOutputToWindow("\nTrying to free a NULLPTR\n");

			this->_memoryManagerMutex.unlock();
			return;
		}

		void* blockDescriptorMemory = static_cast<void*>(static_cast<char*>(i_pointer) -
			this->_intSize - this->_blockDescriptorPointerSize
		);
		const auto actualBlockDescriptor = *(static_cast<BlockDescriptor**>(blockDescriptorMemory));

		// Get the BlockDescriptor from the InUseBlockDescriptors and Remove it
		BlockDescriptor* previousBlockDescriptor = actualBlockDescriptor->previousBlockDescriptor;
		BlockDescriptor* nextBlockDescriptor = actualBlockDescriptor->nextBlockDescriptor;

		// This means that the current BlockDescriptor is the head
		if (previousBlockDescriptor == nullptr && nextBlockDescriptor != nullptr)
		{
			// Make the next the head as the current one was the First one in the list
			nextBlockDescriptor->previousBlockDescriptor = nullptr;
			this->_inUseBlockDescriptors = nextBlockDescriptor;
		}
			// This means that the current BlockDescriptor is the tail
		else if (nextBlockDescriptor == nullptr && previousBlockDescriptor != nullptr)
		{
			previousBlockDescriptor->nextBlockDescriptor = nullptr;
			// In this case the head does not change
		}
			// This means that there was only 1 BlockDescriptor in the inUseBlockDescriptors list
		else if (nextBlockDescriptor == nullptr && previousBlockDescriptor == nullptr)
		{
			// Don't care just clear the list
			this->_inUseBlockDescriptors = nullptr;
		}
			// This means that the BlockDescriptor was somewhere in the middle of the list
		else if (nextBlockDescriptor != nullptr && previousBlockDescriptor != nullptr)
		{
			previousBlockDescriptor->nextBlockDescriptor = nextBlockDescriptor;
			nextBlockDescriptor->previousBlockDescriptor = previousBlockDescriptor;
			// No changes to head required
		}

		// Take the rest of the memory and clean it up
		// Also update the FreeBlock Descriptor to know how much memory it references

		// Then return it to the FreeBlockDescriptors
		actualBlockDescriptor->nextBlockDescriptor = this->_freeBlocks;
		if (this->_freeBlocks != nullptr)
		{
			this->_freeBlocks->previousBlockDescriptor = actualBlockDescriptor;
		}
		actualBlockDescriptor->previousBlockDescriptor = nullptr;
		this->_freeBlocks = actualBlockDescriptor;

		this->_memoryManagerMutex.unlock();
	}

	// Free Memory

	// Collection and Combination

	void MemoryManager::collect()
	{
		this->_memoryManagerMutex.lock();

		Utils::Debug::LogOutputToWindow("\nCollecting Freed Memory\n");
		const auto startTime = std::chrono::high_resolution_clock::now();

		BlockDescriptor* head = getLastBlockDescriptor(this->_freeBlocks);
		quickSort(this->_freeBlocks, head);

		const auto quickSortStopTime = std::chrono::high_resolution_clock::now();
		const auto quickSortDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
			quickSortStopTime - startTime
		);
		Utils::Debug::LogOutputToWindow("Quick Sort took %lld ms\n", quickSortDuration.count());

		BlockDescriptor* current = this->_freeBlocks;

		while (true)
		{
			if (current->nextBlockDescriptor == nullptr)
			{
				break;
			}

			BlockDescriptor* nextDescriptor = current->nextBlockDescriptor;

			void* endPosition = static_cast<char*>(current->memoryStartPointer) + current->memorySize;
			void* nextStartPosition = nextDescriptor->memoryStartPointer;

			if (endPosition == nextStartPosition)
			{
				const size_t totalMemorySize = current->memorySize + nextDescriptor->memorySize;
				current->memorySize = totalMemorySize;

				current->nextBlockDescriptor = nextDescriptor->nextBlockDescriptor;
				if (nextDescriptor->nextBlockDescriptor != nullptr)
				{
					nextDescriptor->nextBlockDescriptor->previousBlockDescriptor = current;
				}

				nextDescriptor->previousBlockDescriptor = nullptr;
				nextDescriptor->nextBlockDescriptor = this->_availableDescriptors;
				if (this->_availableDescriptors != nullptr)
				{
					this->_availableDescriptors->previousBlockDescriptor = nextDescriptor;
				}
				this->_availableDescriptors = nextDescriptor;
			}
			else
			{
				current = current->nextBlockDescriptor;
			}
		}

		const auto stopTime = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);
		Utils::Debug::LogOutputToWindow("Collection of Freed Memory took: %lld ms\n", duration.count());

		this->_memoryManagerMutex.unlock();
	}

	// Collection and Combination

	// Quick Sort

	MemoryManager::BlockDescriptor* MemoryManager::getLastBlockDescriptor(BlockDescriptor* i_head)
	{
		while (i_head != nullptr && i_head->nextBlockDescriptor != nullptr)
		{
			i_head = i_head->nextBlockDescriptor;
		}

		return i_head;
	}

	void MemoryManager::swap(BlockDescriptor* i_first, BlockDescriptor* i_second)
	{
		void* firstMemoryAddress = i_first->memoryStartPointer;
		const size_t firstAddressSize = i_first->memorySize;

		i_first->memoryStartPointer = i_second->memoryStartPointer;
		i_first->memorySize = i_second->memorySize;

		i_second->memoryStartPointer = firstMemoryAddress;
		i_second->memorySize = firstAddressSize;
	}

	MemoryManager::BlockDescriptor* MemoryManager::partition(BlockDescriptor* i_left, BlockDescriptor* i_head) const
	{
		void* compareAddress = i_head->memoryStartPointer;
		BlockDescriptor* current = i_left->previousBlockDescriptor;

		for (BlockDescriptor* j = i_left; j != i_head; j = j->nextBlockDescriptor)
		{
			if (j->memoryStartPointer <= compareAddress)
			{
				current = (current == nullptr) ? i_left : current->nextBlockDescriptor;
				this->swap(current, j);
			}
		}

		current = (current == nullptr) ? i_left : current->nextBlockDescriptor;
		this->swap(current, i_head);

		return current;
	}

	void MemoryManager::quickSort(BlockDescriptor* i_left, BlockDescriptor* i_right) const
	{
		// https://stackoverflow.com/a/33884601
		while (i_left != nullptr && i_right != nullptr &&
			i_left->memoryStartPointer < i_right->memoryStartPointer)
		{
			BlockDescriptor* partitionValue = this->partition(i_left, i_right);

			if (partitionValue == nullptr || partitionValue->nextBlockDescriptor == nullptr)
			{
				return;
			}

			void* combinedLeftPointer = reinterpret_cast<void*>(
				static_cast<char*>(partitionValue->memoryStartPointer) -
				static_cast<char*>(i_left->memoryStartPointer)
			);

			void* combinedRightPointer = reinterpret_cast<void*>(
				static_cast<char*>(i_right->memoryStartPointer) -
				static_cast<char*>(partitionValue->nextBlockDescriptor->memoryStartPointer)
			);

			if (combinedLeftPointer <= combinedRightPointer)
			{
				this->quickSort(i_left, partitionValue);
				i_left = partitionValue->nextBlockDescriptor;
			}
			else
			{
				this->quickSort(partitionValue->nextBlockDescriptor, i_right);
				i_right = partitionValue;
			}
		}

		// if (i_right != nullptr && i_left != i_right && i_left != i_right->nextBlockDescriptor)
		//
		// {
		// 	BlockDescriptor* partitionValue = this->partition(i_left, i_right);
		// 	this->quickSort(i_left, partitionValue->previousBlockDescriptor);
		// 	this->quickSort(partitionValue->nextBlockDescriptor, i_right);
		// }
	}

	// Quick Sort
}

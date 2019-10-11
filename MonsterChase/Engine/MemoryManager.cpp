#include "stdafx.h"
#include "MemoryManager.h"
#include <cstdlib>
#include "Utilities.h"

namespace Memory
{
	MemoryManager::MemoryManager()
	{
	}

	MemoryManager::~MemoryManager()
	{
	}

	// Creation

	void MemoryManager::create(void* heapMemoryStartAddress, const size_t heapMemoryTotalSize,
	                           const size_t maxBlockDescriptors)
	{
		this->_maxBlockDescriptors = maxBlockDescriptors;
		this->_blockDescriptorSize = sizeof(BlockDescriptor);
		this->_blockDescriptorPointerSize = sizeof(BlockDescriptor*);

		this->_maxMemorySize = heapMemoryTotalSize;
		this->_userMemoryStartAddress = maxBlockDescriptors * this->_blockDescriptorSize;
		this->_memoryStartPointer = heapMemoryStartAddress;

		this->_availableDescriptors = nullptr;
		this->_outstandingAllocations = nullptr;

		this->createBlockDescriptors();
		this->createFreeBlock();
	}

	void MemoryManager::createBlockDescriptors()
	{
		// This creates a list of BlockDescriptors
		for (size_t i = 0; i < _maxBlockDescriptors; i++)
		{
			const size_t offsetPosition = i * this->_blockDescriptorSize;

			BlockDescriptor* blockDescriptor = this->createAndGetEmptyBlockDescriptor(offsetPosition);
			blockDescriptor->nextBlockDescriptor = this->_availableDescriptors;

			this->_availableDescriptors = blockDescriptor;
		}
	}

	// Allocates Memory for BlockDescriptor from the Initial Heap Memory and returns it
	MemoryManager::BlockDescriptor* MemoryManager::createAndGetEmptyBlockDescriptor(
		const int descriptorOffsetPosition) const
	{
		BlockDescriptor* blockDescriptor = static_cast<BlockDescriptor*>(
			static_cast<void*>(static_cast<char*>(this->_memoryStartPointer) + descriptorOffsetPosition)
		);
		blockDescriptor->memoryStartAddress = 0;
		blockDescriptor->nextBlockDescriptor = nullptr;
		blockDescriptor->memorySize = this->_maxMemorySize - this->_userMemoryStartAddress;

		return blockDescriptor;
	}

	void MemoryManager::createFreeBlock()
	{
		if (this->_availableDescriptors == nullptr)
		{
			exit(1);
		}

		BlockDescriptor* freeMemoryBlockDescriptor = this->_availableDescriptors;
		this->_availableDescriptors = this->_availableDescriptors->nextBlockDescriptor;

		freeMemoryBlockDescriptor->nextBlockDescriptor = nullptr;
		freeMemoryBlockDescriptor->memoryStartAddress = this->_userMemoryStartAddress;
		freeMemoryBlockDescriptor->memorySize = this->_maxMemorySize - this->_userMemoryStartAddress;
	}

	// Creation

	// Allocation

	void* MemoryManager::allocate(const size_t contiguousMemorySizeRequired)
	{
		// Return NullPtr if there are no BlockDescriptors available
		if (_availableDescriptors == nullptr)
		{
			return nullptr;
		}

		const size_t totalRequiredMemorySize = this->_blockDescriptorPointerSize + this->GuardBlockSize * 2 +
			contiguousMemorySizeRequired;
		void* memoryAddress = this->getFirstFreeBlock(totalRequiredMemorySize);

		// Return NullPtr if there is no consecutive memory fit available
		if (memoryAddress == nullptr)
		{
			return nullptr;
		}

		// At this point we are definitely sure that memory can be provided

		// Get the head BlockDescriptor address to send to the user
		BlockDescriptor* head = this->_availableDescriptors;
		this->_availableDescriptors = head->nextBlockDescriptor;

		head->memorySize = contiguousMemorySizeRequired;
		head->memoryStartAddress = this->_blockDescriptorPointerSize + this->GuardBlockSize;

		// Assign Each Part of Memory
		memoryAddress = head; // Assign the Block Descriptor Pointer

		void* userMemoryAddress = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize + this->GuardBlockSize); // Assign the User Address
		// Just assign Empty Block Data to the User Memory
		// Ease of Debugging and to validate data sent back by the Manager
		// TODO: Check if sizeof(int) is correct
		for (size_t i = 0; i < contiguousMemorySizeRequired; i += sizeof(int))
		{
			*(static_cast<int*>(userMemoryAddress) + i) = EmptyBlockData;
		}

		void* firstGuardPosition = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize);
		*static_cast<int*>(firstGuardPosition) = this->DeadBlockData; // Assign the First Guard Block

		void* secondGuardPosition = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize + this->GuardBlockSize + contiguousMemorySizeRequired);
		*static_cast<int*>(secondGuardPosition) = this->DeadBlockData; // Assign the Second Guard Block

		return userMemoryAddress;
	}

	void* MemoryManager::allocate(size_t contiguousMemorySizeRequired, unsigned int alignment)
	{
		// Return NullPtr if there are no BlockDescriptors available
		if (_availableDescriptors == nullptr)
		{
			return nullptr;
		}

		const size_t totalRequiredMemorySize = this->_blockDescriptorPointerSize + this->GuardBlockSize * 2 +
			contiguousMemorySizeRequired;
		const size_t adjustedMemorySize = Utils::Utilities::GetRoundNextMultiple(totalRequiredMemorySize, alignment);

		void* memoryAddress = this->getFirstFreeBlock(adjustedMemorySize);

		// Return NullPtr if there is no consecutive memory fit available
		if (memoryAddress == nullptr)
		{
			return nullptr;
		}

		// At this point we are definitely sure that memory can be provided

		// Get the head BlockDescriptor address to send to the user
		BlockDescriptor* head = this->_availableDescriptors;
		this->_availableDescriptors = head->nextBlockDescriptor;

		head->memorySize = contiguousMemorySizeRequired;
		head->memoryStartAddress = this->_blockDescriptorPointerSize + this->GuardBlockSize;

		// Assign Each Part of Memory
		memoryAddress = head; // Assign the Block Descriptor Pointer

		void* userMemoryAddress = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize + this->GuardBlockSize); // Assign the User Address
		// Just assign Empty Block Data to the User Memory
		// Ease of Debugging and to validate data sent back by the Manager
		// TODO: Check if sizeof(int) is correct
		for (size_t i = 0; i < contiguousMemorySizeRequired; i += sizeof(int))
		{
			*(static_cast<int*>(userMemoryAddress) + i) = EmptyBlockData;
		}

		void* firstGuardPosition = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize);
		*static_cast<int*>(firstGuardPosition) = this->DeadBlockData; // Assign the First Guard Block

		void* secondGuardPosition = static_cast<void*>(static_cast<char*>(memoryAddress) +
			this->_blockDescriptorPointerSize + this->GuardBlockSize + contiguousMemorySizeRequired);
		*static_cast<int*>(secondGuardPosition) = this->DeadBlockData; // Assign the Second Guard Block

		//Assign EmptyBlockData to the Alignment Bytes
		const size_t adjustedMemoryDiff = adjustedMemorySize - totalRequiredMemorySize;
		for (size_t i = 0; i < adjustedMemoryDiff; i += sizeof(int))
		{
			*(static_cast<int*>(secondGuardPosition) + this->GuardBlockSize + i) = this->EmptyBlockData;
		}

		// The rest of the memory that is left is just void memory for the alignment


		return userMemoryAddress;
	}

	void* MemoryManager::getFirstFreeBlock(const size_t sizeRequired)
	{
		// Return NULL if there are no FreeBlock available
		if (_freeBlocks == nullptr)
		{
			return nullptr;
		}

		BlockDescriptor* freeBlockPointer = _freeBlocks;
		BlockDescriptor* freeBlockPointerPrevious = nullptr;

		// Loop through the Free Block List and find a Block that as the required size
		// Basically (First Fit)
		while (freeBlockPointer != nullptr)
		{
			if (freeBlockPointer->memorySize < sizeRequired)
			{
				freeBlockPointerPrevious = freeBlockPointer;
				freeBlockPointer = freeBlockPointer->nextBlockDescriptor;
				continue;
			}

			// Break on finding it
			break;
		}

		// freeBlockPointer now points towards the BlockDescriptor that has the required Size
		// freeBlockPointerPrevious points to the previous BlockDescriptor

		// Calculate the amount of memory left in the FreeBlock after user memory is subtracted
		const size_t freeBlockMemorySizeLeft = freeBlockPointer->memorySize - sizeRequired;

		// Find the user memory as this is the one that will be returned
		void* userMemory = static_cast<void*>(static_cast<char*>(this->_memoryStartPointer)
			+ freeBlockPointer->memoryStartAddress);

		// Just Reduce the BlockDescriptor size in case the whole of it is not used
		if (freeBlockMemorySizeLeft > 0)
		{
			freeBlockPointer->memorySize = freeBlockMemorySizeLeft;
			freeBlockPointer->memoryStartAddress = freeBlockPointer->memoryStartAddress + sizeRequired;
		}
			// In Case the whole is Used...
		else
		{
			// If the previous is not null, then make the previous->next the current->next
			// And remove the current from the middle
			// Previous -> Current -> Next
			// Previous -> Next
			if (freeBlockPointerPrevious != nullptr)
			{
				freeBlockPointerPrevious->nextBlockDescriptor = freeBlockPointer->nextBlockDescriptor;
			}
				// This means that the current is the head of the Block
				// Just put in the next
			else
			{
				_freeBlocks = _freeBlocks->nextBlockDescriptor;
			}

			// Return the Current to the _availableDescriptors LinkedList
			freeBlockPointer->nextBlockDescriptor = _availableDescriptors;
			_availableDescriptors = freeBlockPointer;
		}

		return userMemory;
	}


	// Allocation
}

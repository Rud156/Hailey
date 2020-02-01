#include "FixedMemoryManager.h"
#include "MemoryManager.h"
#include "BitArray.h"
#include <cassert>

namespace Memory
{
#pragma region Construction and Destruction

	FixedMemoryManager::FixedMemoryManager(): _fixedMemoryBlockSize(0), _totalUserMemorySize(0), _totalBitsCount(0),
	                                          _memoryMapper(nullptr),
	                                          _userMemoryStartPointer(nullptr)
	{
	}

	FixedMemoryManager::~FixedMemoryManager()
	= default;


#pragma endregion

#pragma region Setup

	void FixedMemoryManager::create(size_t memoryBlockSize, MemoryManager* memoryManager,
	                                const long totalBitsCount)
	{
		assert(totalBitsCount > 0);
		const size_t totalMemorySizeRequired = totalBitsCount * memoryBlockSize;

		this->_totalBitsCount = totalBitsCount;
		this->_fixedMemoryBlockSize = memoryBlockSize;
		this->_totalUserMemorySize = totalMemorySizeRequired;

		void* memoryMapperMemory = memoryManager->allocate(sizeof(Containers::BitArray));
		this->_memoryMapper = new(memoryMapperMemory)Containers::BitArray(totalBitsCount, memoryManager);

		void* userMemory = memoryManager->allocate(totalMemorySizeRequired);
		this->_userMemoryStartPointer = userMemory;
	}

#pragma endregion

#pragma region Allocation

	void* FixedMemoryManager::allocate(size_t contiguousMemorySize) const
	{
		if (contiguousMemorySize > this->_fixedMemoryBlockSize)
		{
			return nullptr;
		}

		size_t setBitIndex;
		const bool bitFound = this->_memoryMapper->getFirstSetBit(setBitIndex);

		if (!bitFound)
		{
			return nullptr;
		}

		const bool bitValue = this->_memoryMapper->test(setBitIndex);
		assert(bitValue == true);

		this->_memoryMapper->flip(setBitIndex);
		void* pointer = static_cast<void*>(static_cast<char*>(this->_userMemoryStartPointer) + (setBitIndex *
			this->_fixedMemoryBlockSize));

		return pointer;
	}

#pragma endregion

#pragma region Free

	void FixedMemoryManager::freeMem(void* pointer) const
	{
		if (!isAllocated(pointer))
		{
			printf_s("Trying to free invalid pointer\n");
			return;
		}

		const size_t index = (static_cast<char*>(pointer) - static_cast<char*>(this->_userMemoryStartPointer)) /
			this->_fixedMemoryBlockSize;

		const bool bitValue = this->_memoryMapper->test(index);
		assert(bitValue == false);

		this->_memoryMapper->flip(index);
	}

#pragma endregion

#pragma region Destroy

	void FixedMemoryManager::destroy(MemoryManager* memoryManager) const
	{
		memoryManager->freeMem(this->_userMemoryStartPointer);

		this->_memoryMapper->destroy(memoryManager);
		memoryManager->freeMem(this->_memoryMapper);
	}

#pragma endregion
}

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

	FixedMemoryManager::~FixedMemoryManager() = default;

#pragma endregion

#pragma region Setup

	void FixedMemoryManager::create(size_t i_memoryBlockSize, MemoryManager* i_memoryManager,
	                                const long i_totalBitsCount)
	{
		assert(i_totalBitsCount > 0);
		const size_t totalMemorySizeRequired = i_totalBitsCount * i_memoryBlockSize;

		this->_totalBitsCount = i_totalBitsCount;
		this->_fixedMemoryBlockSize = i_memoryBlockSize;
		this->_totalUserMemorySize = totalMemorySizeRequired;

		void* memoryMapperMemory = i_memoryManager->allocate(sizeof(Containers::BitArray));
		this->_memoryMapper = new(memoryMapperMemory)Containers::BitArray(i_totalBitsCount, i_memoryManager);

		void* userMemory = i_memoryManager->allocate(totalMemorySizeRequired);
		this->_userMemoryStartPointer = userMemory;
	}

#pragma endregion

#pragma region Allocation

	void* FixedMemoryManager::allocate(size_t i_contiguousMemorySize) const
	{
		if (i_contiguousMemorySize > this->_fixedMemoryBlockSize)
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

	void FixedMemoryManager::freeMem(void* i_pointer) const
	{
		if (!isAllocated(i_pointer))
		{
			printf_s("Trying to free invalid pointer\n");
			return;
		}

		const size_t index = (static_cast<char*>(i_pointer) - static_cast<char*>(this->_userMemoryStartPointer)) /
			this->_fixedMemoryBlockSize;

		const bool bitValue = this->_memoryMapper->test(index);
		assert(bitValue == false);

		this->_memoryMapper->flip(index);
	}

#pragma endregion

#pragma region Destroy

	void FixedMemoryManager::destroy(MemoryManager* i_memoryManager) const
	{
		i_memoryManager->freeMem(this->_userMemoryStartPointer);

		this->_memoryMapper->destroy(i_memoryManager);
		i_memoryManager->freeMem(this->_memoryMapper);
	}

#pragma endregion
}

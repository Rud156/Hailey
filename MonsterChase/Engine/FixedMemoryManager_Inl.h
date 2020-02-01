#pragma once

#include "BitArray.h"

namespace Memory
{
#pragma region Data Check

	inline bool FixedMemoryManager::canHandleSize(const size_t inputSize) const
	{
		return inputSize <= this->_fixedMemoryBlockSize;
	}

	inline bool FixedMemoryManager::contains(void* pointer) const
	{
		void* startPointer = this->_userMemoryStartPointer;
		void* endPointer = static_cast<char*>(this->_userMemoryStartPointer) + this->_totalUserMemorySize;

		if (pointer >= startPointer && pointer <= endPointer)
		{
			return true;
		}

		return false;
	}

	inline bool FixedMemoryManager::isAllocated(void* pointer) const
	{
		const long index = static_cast<long>((static_cast<char*>(pointer) -
			static_cast<char*>(this->_userMemoryStartPointer)) / this->_fixedMemoryBlockSize);

		if (index < 0 || index >= this->_totalBitsCount)
		{
			return false;
		}

		return !this->_memoryMapper->test(index);
	}

#pragma endregion
}

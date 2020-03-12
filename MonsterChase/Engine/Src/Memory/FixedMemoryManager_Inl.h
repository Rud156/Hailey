#pragma once
#include "../Containers/BitArray.h"

namespace Memory
{
#pragma region Data Check

	inline bool FixedMemoryManager::canHandleSize(const size_t i_inputSize) const
	{
		return i_inputSize <= this->_fixedMemoryBlockSize;
	}

	inline bool FixedMemoryManager::contains(void* i_pointer) const
	{
		void* startPointer = this->_userMemoryStartPointer;
		void* endPointer = static_cast<char*>(this->_userMemoryStartPointer) + this->_totalUserMemorySize;

		if (i_pointer >= startPointer && i_pointer <= endPointer)
		{
			return true;
		}

		return false;
	}

	inline bool FixedMemoryManager::isAllocated(void* i_pointer) const
	{
		const long index = static_cast<long>((static_cast<char*>(i_pointer) -
			static_cast<char*>(this->_userMemoryStartPointer)) / this->_fixedMemoryBlockSize);

		if (index < 0 || index >= this->_totalBitsCount)
		{
			return false;
		}

		return !this->_memoryMapper->test(index);
	}

#pragma endregion
}

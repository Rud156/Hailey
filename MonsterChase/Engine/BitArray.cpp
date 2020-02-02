#include "BitArray.h"
#include "MemoryManager.h"
#include <cassert>
#include <cmath>
#include <intrin0.h>

namespace Containers
{
#pragma region Construction and Destruction

	BitArray::BitArray(const size_t numBits, bool startSet)
	{
		assert(numBits != 0);

#ifdef _WIN64
		this->_uintSize = sizeof(uint64_t);
		this->_bitSize = 64;
#else
		this->_uintSize = sizeof(uint32_t);
		this->_bitSize = 32;
#endif

		this->_bitArraySize = static_cast<size_t>(ceil(numBits / this->_bitSize));

#ifdef _WIN64
		this->_bitArray64 = new uint64_t[this->_bitArraySize];
#else
		this->_bitArray32 = new uint32_t[this->_bitArraySize];
#endif


		if (startSet)
		{
			for (size_t i = 0; i < this->_bitArraySize; i++)
			{
#ifdef _WIN64
				this->_bitArray64[i] = 0xffffffffffffffff;
#else
				this->_bitArray32[i] = 0xffffffff;
#endif
			}
		}
	}

	BitArray::BitArray(size_t numBits, Memory::MemoryManager* memoryManager, bool startSet)
	{
		assert(numBits != 0);

#ifdef _WIN64
		this->_uintSize = sizeof(uint64_t);
		this->_bitSize = 64;
#else
		this->_uintSize = sizeof(uint32_t);
		this->_bitSize = 32;
#endif

		this->_bitArraySize = static_cast<size_t>(ceil(numBits / this->_bitSize));
		void* arrayMemory = memoryManager->allocate(this->_uintSize * this->_bitArraySize);

#ifdef _WIN64
		this->_bitArray64 = static_cast<uint64_t*>(arrayMemory);
#else
		this->_bitArray32 = static_cast<uint32_t*>(arrayMemory);
#endif


		if (startSet)
		{
			for (size_t i = 0; i < this->_bitArraySize; i++)
			{
#ifdef _WIN64
				this->_bitArray64[i] = 0xffffffffffffffff;
#else
				this->_bitArray32[i] = 0xffffffff;
#endif
			}
		}
	}

	BitArray::~BitArray()
	{
#ifdef _WIN64
		delete this->_bitArray64;
#else
		delete this->_bitArray32;
#endif
	}

#pragma endregion

#pragma region Set All Bits

	void BitArray::clear() const
	{
		for (size_t i = 0; i < this->_bitArraySize; i++)
		{
#ifdef _WIN64
			this->_bitArray64[i] = 0;
#else
			this->_bitArray32[i] = 0;
#endif
		}
	}

	void BitArray::set() const
	{
		for (size_t i = 0; i < this->_bitArraySize; i++)
		{
#ifdef _WIN64
			this->_bitArray64[i] = 0xffffffffffffffff;
#else
			this->_bitArray32[i] = 0xffffffff;
#endif
		}
	}

#pragma endregion

#pragma region Data Checks

	bool BitArray::areAllClear() const
	{
		for (size_t i = 0; i < this->_bitArraySize; i++)
		{
#ifdef _WIN64
			if (this->_bitArray64[i] != 0)
			{
				return false;
			}
#else
			if (this->_bitArray32[i] != 0)
			{
				return false;
			}
#endif
		}

		return true;
	}

	bool BitArray::areAllSet() const
	{
		for (size_t i = 0; i < this->_bitArraySize; i++)
		{
#ifdef _WIN64
			if (this->_bitArray64[i] != 0xffffffffffffffff)
			{
				return false;
			}
#else
			if (this->_bitArray32[i] != 0xffffffff)
			{
				return false;
			}
#endif
		}

		return true;
	}

#pragma endregion

#pragma region Get Bit Data

	bool BitArray::getFirstClearBit(size_t& index) const
	{
		int arrayIndex = -1;
		for (size_t i = 0; i < this->_bitArraySize; i++)
		{
#ifdef _WIN64
			if (this->_bitArray64[i] != 0xffffffffffffffff)
			{
				arrayIndex = static_cast<int>(i);
				break;
			}
#else
			if (this->_bitArray32[i] != 0xffffffff)
			{
				arrayIndex = static_cast<int>(i);
				break;
			}
#endif
		}

		if (arrayIndex == -1)
		{
			return false;
		}

		int bitIndex = 0;

#ifdef _WIN64
		uint64_t arrayValue64 = this->_bitArray64[arrayIndex];
		arrayValue64 = ~arrayValue64;

		while (true)
		{
			const bool isZero = arrayValue64 & 1;
			if (isZero)
			{
				break;
			}

			bitIndex += 1;
			arrayValue64 = arrayValue64 >> 1;
		}
#else
		uint32_t arrayValue32 = this->_bitArray32[arrayIndex];
		arrayValue32 = ~arrayValue32;

		while (true)
		{
			const bool isZero = arrayValue32 & 1;
			if (isZero)
			{
				break;
			}

			bitIndex += 1;
			arrayValue32 = arrayValue32 >> 1;
		}
#endif

		index = bitIndex;
		return true;
	}

	bool BitArray::getFirstSetBit(size_t& index) const
	{
		int arrayIndex = -1;
		for (size_t i = 0; i < this->_bitArraySize; i++)
		{
#ifdef _WIN64
			if (this->_bitArray64[i] != 0)
			{
				arrayIndex = static_cast<int>(i);
				break;
			}
#else
			if (this->_bitArray32[i] != 0)
			{
				arrayIndex = static_cast<int>(i);
				break;
			}
#endif
		}

		if (arrayIndex == -1)
		{
			return false;
		}

		bool isValidPlatform = false;
		unsigned long bitIndex = 0;

#ifdef _WIN64
		const uint64_t arrayValue64 = this->_bitArray64[arrayIndex];

		isValidPlatform = true;
		_BitScanForward64(&bitIndex, arrayValue64);
#else
		const uint32_t arrayValue32 = this->_bitArray32[arrayIndex];

		isValidPlatform = true;
		_BitScanForward(&bitIndex, arrayValue32);
#endif

		index = arrayIndex * this->_bitSize + bitIndex;
		return isValidPlatform;
	}

	bool BitArray::test(size_t index) const
	{
		const size_t arrayIndex = index / this->_bitSize;
		const size_t bitIndex = index % this->_bitSize;

		assert(arrayIndex < this->_bitArraySize);

#ifdef _WIN64
		const auto arrayValue64 = this->_bitArray64[arrayIndex];
		uint64_t finalValue = 1;

		finalValue = finalValue << bitIndex;
		return finalValue & arrayValue64;
#else
		const auto arrayValue32 = this->_bitArray32[arrayIndex];
		uint32_t finalValue = 1;

		finalValue = finalValue << bitIndex;
		return finalValue & arrayValue32;
#endif
	}

	bool BitArray::operator[](const size_t index) const
	{
		return test(index);
	}

#pragma endregion

#pragma region Affect Single Bit

	void BitArray::set(size_t index, const bool value) const
	{
		const size_t arrayIndex = index / this->_bitSize;
		const size_t bitIndex = index % this->_bitSize;

		assert(arrayIndex < this->_bitArraySize);
		if (value)
		{
#ifdef _WIN64
			uint64_t arrayValue64 = this->_bitArray64[arrayIndex];

			uint64_t finalValue64 = 1;
			finalValue64 = finalValue64 << bitIndex;
			arrayValue64 |= finalValue64;

			this->_bitArray64[arrayIndex] = arrayValue64;
#else
			uint32_t arrayValue32 = this->_bitArray32[arrayIndex];

			uint32_t finalValue32 = 1;
			finalValue32 = finalValue32 << bitIndex;
			arrayValue32 |= finalValue32;

			this->_bitArray32[arrayIndex] = arrayValue32;
#endif
		}
		else
		{
#ifdef _WIN64
			uint64_t arrayValue64 = this->_bitArray64[arrayIndex];

			uint64_t finalValue64 = 1;
			finalValue64 = finalValue64 << bitIndex;
			arrayValue64 &= ~finalValue64;

			this->_bitArray64[arrayIndex] = arrayValue64;
#else
			uint32_t arrayValue32 = this->_bitArray32[arrayIndex];

			uint32_t finalValue32 = 1;
			finalValue32 = finalValue32 << bitIndex;
			arrayValue32 &= ~finalValue32;

			this->_bitArray32[arrayIndex] = arrayValue32;
#endif
		}
	}

	void BitArray::flip(const size_t index) const
	{
		const bool bitValue = test(index);

		if (bitValue)
		{
			set(index, false);
		}
		else
		{
			set(index, true);
		}
	}

#pragma endregion

#pragma region Destroy

	void BitArray::destroy(Memory::MemoryManager* memoryManager) const
	{
#ifdef _WIN64
		memoryManager->freeMem(this->_bitArray64);
#else
		memoryManager->freeMem(this->_bitArray32);
#endif
	}

#pragma endregion
}

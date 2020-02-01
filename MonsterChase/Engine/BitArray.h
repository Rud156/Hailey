#pragma once
#include <cstdint>

namespace Memory
{
	class MemoryManager;
}

namespace Containers
{
	class BitArray
	{
	private:
#ifdef _WIN64
		uint64_t* _bitArray64;	
#else
		uint32_t* _bitArray32;
#endif

		size_t _uintSize;
		size_t _bitArraySize;

	public:
		BitArray(size_t numBits, bool startClear = true);
		BitArray(size_t numBits, Memory::MemoryManager* memoryManager, bool startClear = true);
		~BitArray();

		// Affect All Bits
		void clear() const;
		void set() const;

		// Data Checks
		bool areAllClear() const;
		bool areAllSet() const;

		// Get Bit Data
		bool getFirstClearBit(size_t& index) const;
		bool getFirstSetBit(size_t& index) const;
		bool test(size_t index) const;

		// Affect Single Bit
		void set(size_t index, bool value = true) const;
		void flip(size_t index) const;

		// Get Bit By Index
		bool operator[](size_t index) const;

		// Destroy
		void destroy(Memory::MemoryManager* memoryManager) const;
	};
}

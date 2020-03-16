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
		size_t _bitSize;
		size_t _bitArraySize;

	public:
		BitArray(size_t i_numBits, bool i_startSet = true);
		BitArray(size_t i_numBits, Memory::MemoryManager* i_memorySystem, bool i_startSet = true);
		~BitArray();

		// Affect All Bits
		void clear() const;
		void set() const;

		// Data Checks
		[[nodiscard]] bool areAllClear() const;
		[[nodiscard]] bool areAllSet() const;

		// Get Bit Data
		bool getFirstClearBit(size_t& o_index) const;
		bool getFirstSetBit(size_t& o_index) const;
		[[nodiscard]] bool test(size_t i_index) const;

		// Affect Single Bit
		void set(size_t i_index, bool i_value = true) const;
		void flip(size_t i_index) const;

		// Get Bit By Index
		bool operator[](size_t i_index) const;

		// Destroy
		void destroy(Memory::MemoryManager* i_memoryManager) const;
	};
}

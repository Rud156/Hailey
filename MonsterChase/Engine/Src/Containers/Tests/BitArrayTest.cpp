#include "BitArrayTest.h"
#include "../../Memory/MemorySystem_Extern.h"
#include "../../Utils/Random.h"

#include <cassert>
#include <vector>
#include <ctime>
#include <conio.h>

namespace Containers
{
	namespace Tests
	{
		void RunBitArrayUnitTest()
		{
			srand(static_cast<unsigned int>(time(nullptr)));

			const size_t maxBitArraySize = 1000;

			void* bitArrayMemory = Memory::MemorySystem::allocate(sizeof(BitArray));
			const auto bitArray = new(bitArrayMemory)BitArray(maxBitArraySize, memoryManager, false);

			assert(bitArray->areAllSet());

			size_t index;
			const bool bitFound = bitArray->getFirstSetBit(index);
			assert(bitFound && index == 0);

			std::vector<bool> fakeBitArray;
			for (size_t i = 0; i < maxBitArraySize; i++)
			{
				fakeBitArray.push_back(true);
			}

			for (size_t i = 0; i < maxBitArraySize; i++)
			{
				const int randomIndex = Utils::Random::RandomInRange(0, maxBitArraySize - 1);

				const bool fakeBitValue = fakeBitArray[randomIndex];
				const bool actualBitValue = bitArray->test(randomIndex);
				assert(fakeBitValue == actualBitValue);

				fakeBitArray[randomIndex] = !fakeBitArray[randomIndex];
				bitArray->flip(randomIndex);

				size_t fakeBitArrayIndexSet;
				size_t bitArrayIndexSet;
				const bool fakeBitArrayValueSet = GetFirstSetBit(fakeBitArrayIndexSet, fakeBitArray);
				const bool actualBitArrayValueSet = bitArray->getFirstSetBit(bitArrayIndexSet);
				assert(fakeBitArrayValueSet == actualBitArrayValueSet);
				assert(fakeBitArrayIndexSet == bitArrayIndexSet);

				size_t fakeBitArrayIndexClear;
				size_t bitArrayIndexClear;
				const bool fakeBitArrayValueClear = GetFirstSetBit(fakeBitArrayIndexClear, fakeBitArray);
				const bool actualBitArrayValueClear = bitArray->getFirstSetBit(bitArrayIndexClear);
				assert(fakeBitArrayValueClear == actualBitArrayValueClear);
				assert(fakeBitArrayIndexClear == bitArrayIndexClear);
			}

			bitArray->destroy(memoryManager);
			memoryManager->freeMem(bitArray);
			fakeBitArray.clear();

			memoryManager->collect();

			printf_s("\n===============================\n");
			printf_s("Bit Array Testing Complete\n");
			printf_s("===============================\n");
		}

		bool GetFirstSetBit(size_t& i_index, std::vector<bool> i_fakeBitArray)
		{
			for (size_t i = 0; i < i_fakeBitArray.size(); i++)
			{
				if (i_fakeBitArray[i])
				{
					i_index = i;
					return true;
				}
			}

			return false;
		}

		bool GetFirstClearBit(size_t& i_index, std::vector<bool> i_fakeBitArray)
		{
			for (size_t i = 0; i < i_fakeBitArray.size(); i++)
			{
				if (!i_fakeBitArray[i])
				{
					i_index = i;
					return true;
				}
			}

			return false;
		}
	}
}

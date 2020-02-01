#pragma once
#include <vector>

namespace Containers
{
	namespace Tests
	{
		void RunBitArrayUnitTest();

		bool GetFirstSetBit(size_t& index, std::vector<bool> fakeBitArray);
		bool GetFirstClearBit(size_t& index, std::vector<bool> fakeBitArray);
	}
}

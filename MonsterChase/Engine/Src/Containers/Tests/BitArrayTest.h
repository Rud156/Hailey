#pragma once
#include <vector>

namespace Containers
{
	namespace Tests
	{
		void RunBitArrayUnitTest();

		bool GetFirstSetBit(size_t& i_index, std::vector<bool> i_fakeBitArray);
		bool GetFirstClearBit(size_t& i_index, std::vector<bool> i_fakeBitArray);
	}
}

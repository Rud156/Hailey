#pragma once
#include <atomic>

namespace Utils
{
	class Uuid
	{
	private:
		static std::atomic<size_t> uuid;

	public:
		static size_t getUuid();
	};
}

#include "Uuid.h"

std::atomic<size_t> Utils::Uuid::uuid = 0;

namespace Utils
{
	size_t Uuid::getUuid()
	{
		Uuid::uuid += 1;
		return uuid;
	}
}

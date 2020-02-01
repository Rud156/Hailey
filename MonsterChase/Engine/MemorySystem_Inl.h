#pragma once
#include "FixedMemoryManager.h"
#include "MemoryManager_Extern.h"

namespace Memory
{
#pragma region Collections

	inline void MemorySystem::collect()
	{
		memoryManager->collect();
	}

#pragma endregion

#pragma region Data Checks

	inline bool MemorySystem::contains(void* pointer) const
	{
		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			if (this->_fixedMemoryManagers[i]->contains(pointer))
			{
				return true;
			}
		}

		return memoryManager->contains(pointer);
	}

	inline bool MemorySystem::isAllocated(void* pointer) const
	{
		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			if (this->_fixedMemoryManagers[i]->isAllocated(pointer))
			{
				return true;
			}
		}

		return memoryManager->isAllocated(pointer);
	}

#pragma endregion
}

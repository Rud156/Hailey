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

	inline bool MemorySystem::contains(void* i_pointer) const
	{
		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			if (this->_fixedMemoryManagers[i]->contains(i_pointer))
			{
				return true;
			}
		}

		return memoryManager->contains(i_pointer);
	}

	inline bool MemorySystem::isAllocated(void* i_pointer) const
	{
		for (size_t i = 0; i < TotalFixedAllocators; i++)
		{
			if (this->_fixedMemoryManagers[i]->isAllocated(i_pointer))
			{
				return true;
			}
		}

		return memoryManager->isAllocated(i_pointer);
	}

#pragma endregion
}

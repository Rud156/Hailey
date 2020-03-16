#pragma once
#include "FixedMemoryManager.h"
#include "MemoryManager_Extern.h"

namespace Memory
{
#pragma region Collections

	inline void MemorySystem::collect()
	{
		MemoryBlock* head = _instance->_memoryBlocks;
		while (head != nullptr)
		{
			head->memoryManager->collect();
			head = head->nextBlock;
		}
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

		MemoryBlock* head = _instance->_memoryBlocks;
		while (head != nullptr)
		{
			if (head->memoryManager->contains(i_pointer))
			{
				return true;
			}

			head = head->nextBlock;
		}

		return false;
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


		MemoryBlock* head = _instance->_memoryBlocks;
		while (head != nullptr)
		{
			if (head->memoryManager->isAllocated(i_pointer))
			{
				return true;
			}

			head = head->nextBlock;
		}

		return false;
	}

#pragma endregion
}

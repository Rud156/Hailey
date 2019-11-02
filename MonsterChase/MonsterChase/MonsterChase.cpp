// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include <conio.h>
#include "HeapManagerUnitTest.h"
#include "MemoryManager.h"
#include <Windows.h>
#include <cassert>
#include <cstdio>

int main()
{
	{
		Engine::Init();

		// const size_t sizeHeap = 1024 * 1024;
		// const unsigned int numDescriptors = 6;
		//
		// SYSTEM_INFO SysInfo;
		// GetSystemInfo(&SysInfo);
		// // round our size to a multiple of memory page size
		// assert(SysInfo.dwPageSize > 0);
		// const size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeap + SysInfo.dwPageSize) /
		// 	SysInfo.dwPageSize);
		// void* pHeapMemory = VirtualAlloc(nullptr, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		//
		// Memory::MemoryManager* heapManager = Memory::MemoryManager::Instance();
		// heapManager->create(pHeapMemory, sizeHeap, numDescriptors);
		//
		// heapManager->showAvailableBlocks();
		// heapManager->showFreeBlocks();
		// heapManager->showOutstandingMemory();
		//
		// const size_t largestBeforeAlloc = heapManager->getLargestFreeBlockSize();
		// void* pPtr_1 = heapManager->allocate(10);
		// pPtr_1 = heapManager->reallocate(pPtr_1, 1022);
		// void* pPtr_2 = heapManager->allocate(1022);
		// pPtr_2 = heapManager->reallocate(pPtr_2, 1022);
		// void* pPtr_3 = heapManager->allocate(10);
		//
		// heapManager->showAvailableBlocks();
		// heapManager->showFreeBlocks();
		// heapManager->showOutstandingMemory();
		//
		// heapManager->freeMem(pPtr_3);
		// heapManager->freeMem(pPtr_1);
		// heapManager->freeMem(pPtr_2);
		//
		// heapManager->showAvailableBlocks();
		// heapManager->showFreeBlocks();
		// heapManager->showOutstandingMemory();
		//
		// heapManager->collect();
		//
		// heapManager->showAvailableBlocks();
		// heapManager->showFreeBlocks();
		// heapManager->showOutstandingMemory();

		const auto heapManagerUnitTest = new HeapManagerUnitTest();
		const bool success = heapManagerUnitTest->HeapManager_UnitTest();

		if (success)
		{
			printf_s("Testing Complete\n");
		}
		else
		{
			printf_s("Testing Failed\n");
		}

		delete heapManagerUnitTest;

		Engine::ShutDown();
	}

	_getch();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

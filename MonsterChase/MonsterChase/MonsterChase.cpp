// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include <conio.h>
#include "Point2D.h"
#include <iostream>
#include "HeapManagerUnitTest.h"
#include <ctime>
#include <vector>
#include <Windows.h>
#include <cassert>
#include "MemoryManager.h"

int main()
{
	{
		Engine::Init();


		// srand(static_cast<unsigned int>(time(nullptr)));
		//
		// std::vector<int> comparisonVector;
		//
		// const size_t maxRandomValue = 50000;
		// const size_t sizeHeap = 1024 * 1024;
		// const unsigned int numDescriptors = 2048;
		//
		// SYSTEM_INFO SysInfo;
		// GetSystemInfo(&SysInfo);
		// // round our size to a multiple of memory page size
		// assert(SysInfo.dwPageSize > 0);
		// const size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeap + SysInfo.dwPageSize) /
		// 	SysInfo.dwPageSize);
		// void* pHeapMemory = VirtualAlloc(nullptr, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		//
		// Memory::MemoryManager* memoryManager = Memory::MemoryManager::Instance();
		// memoryManager->create(pHeapMemory, sizeHeap, numDescriptors);
		//
		// memoryManager->showOutstandingMemory();
		// memoryManager->showFreeBlocks();
		//
		// const size_t totalIntSize = 512;
		// size_t currentArraySize = 0;
		// int* testArray = static_cast<int*>(memoryManager->allocate(sizeof(int)));
		// while (currentArraySize != totalIntSize)
		// {
		// 	testArray = static_cast<int*>(memoryManager->reallocate(testArray, sizeof(int) * (currentArraySize + 1)));
		// 	int randomNumber = (rand() & maxRandomValue - 1) + 1;
		//
		// 	comparisonVector.push_back(randomNumber);
		// 	testArray[currentArraySize] = randomNumber;
		//
		// 	currentArraySize += 1;
		// }
		//
		// for (size_t i = 0; i < currentArraySize; i++)
		// {
		// 	printf_s("Array Value: %d, Vector Value: %d\n", testArray[i], comparisonVector[i]);
		// 	assert(testArray[i] == comparisonVector[i]);
		// }
		// printf_s("Wowser. Testing Complete\n");
		//
		// memoryManager->freeMem(testArray);
		// memoryManager->collect();
		//
		// memoryManager->showOutstandingMemory();
		// memoryManager->showFreeBlocks();
		//
		// delete memoryManager;

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

	_CrtDumpMemoryLeaks();

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

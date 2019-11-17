// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include <conio.h>
#include <iostream>
#include "GameMain.h"
#include "Node2D.h"
#include "MemoryManager.h"
#include  <Windows.h>
#include <cassert>

Memory::MemoryManager* memoryManager = nullptr;

void* operator new(size_t size)
{
	if (memoryManager == nullptr)
	{
		return malloc(size);
	}

	return memoryManager->allocate(size);
}

void* operator new[](size_t size)
{
	if (memoryManager == nullptr)
	{
		return malloc(size);
	}

	return memoryManager->allocate(size);
}

void operator delete(void* pointer)
{
	memoryManager->freeMem(pointer);
}

void operator delete[](void* pointer)
{
	memoryManager->freeMem(pointer);
}

int main()
{
	{
		Engine::Init();

		const size_t maxRandomValue = 50000;
		const size_t sizeHeap = 1024 * 1024;
		const unsigned int numDescriptors = 2048;

		SYSTEM_INFO SysInfo;
		GetSystemInfo(&SysInfo);
		// round our size to a multiple of memory page size
		assert(SysInfo.dwPageSize > 0);
		const size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeap + SysInfo.dwPageSize) /
			SysInfo.dwPageSize);
		void* pHeapMemory = VirtualAlloc(nullptr, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		memoryManager = Memory::MemoryManager::Instance();
		memoryManager->create(pHeapMemory, sizeHeap, numDescriptors);

		memoryManager->showOutstandingMemory();
		memoryManager->showFreeBlocks();

		auto gameMain = new Game::GameMain();
		gameMain->InitializeAndRun();
		delete gameMain;

		memoryManager->showOutstandingMemory();
		memoryManager->showFreeBlocks();

		memoryManager->collect();
		memoryManager->showFreeBlocks();

		free(memoryManager);

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

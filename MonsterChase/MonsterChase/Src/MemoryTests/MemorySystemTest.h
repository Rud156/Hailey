#pragma once

bool MemorySystem_UnitTest();
void RunMemorySystemTest();

bool InitializeMemorySystem(void* i_pHeapMemory);
void Collect();
void DestroyMemorySystem();

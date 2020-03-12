#pragma once

bool MemorySystem_UnitTest();
void RunMemorySystemTest();

bool InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);
void Collect();
void DestroyMemorySystem();

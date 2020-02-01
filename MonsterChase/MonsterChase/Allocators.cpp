#include "Allocators.h"
#include "MemorySystem_Extern.h"

#define malloc(x) customMalloc(x)
#define realloc(x, y) customRealloc(x, y)
#define free(x) customFree(x)

void* customMalloc(size_t size)
{
	printf("malloc %zu\n", size);
	return Memory::MemorySystem::allocate(size);
}

void* customRealloc(void* pointer, size_t contiguousMemorySizeRequired)
{
	return Memory::MemorySystem::reallocate(pointer, contiguousMemorySizeRequired);
}

void customFree(void* pointer)
{
	Memory::MemorySystem::freeMem(pointer);
}

_VCRT_ALLOCATOR
void* __CRTDECL operator new(
	size_t _Size
)
{
	return Memory::MemorySystem::allocate(_Size);
}

void __CRTDECL operator delete(
	void* _Block
) noexcept
{
	return Memory::MemorySystem::freeMem(_Block);
}

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(_Size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](
	size_t _Size
)
{
	return Memory::MemorySystem::allocate(_Size);
}

void __CRTDECL operator delete[](
	void* _Block
) noexcept
{
	return Memory::MemorySystem::freeMem(_Block);
}

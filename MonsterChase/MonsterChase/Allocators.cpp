#include "Allocators.h"
#include "MemorySystem_Extern.h"

void* cMalloc(size_t _Size)
{
	return Memory::MemorySystem::allocate(_Size);
}

void cFree(void* _Block)
{
	Memory::MemorySystem::freeMem(_Block);
}

void* cRealloc(void* _Block, size_t _Size)
{
	return Memory::MemorySystem::reallocate(_Block, _Size);
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

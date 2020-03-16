#include "Allocators.h"
#include "MemorySystem_Extern.h"

#define USE_CUSTOM

void* cMalloc(size_t _Size)
{
#ifdef USE_CUSTOM
	return Memory::MemorySystem::allocate(_Size);
#else
	return malloc(_Size);
#endif
}

void cFree(void* _Block)
{
#ifdef USE_CUSTOM
	Memory::MemorySystem::freeMem(_Block);
#else
	free(_Block);
#endif
}

void* cRealloc(void* _Block, size_t _Size)
{
#ifdef USE_CUSTOM
	return Memory::MemorySystem::reallocate(_Block, _Size);
#else
	return realloc(_Block, _Size);
#endif
}

_VCRT_ALLOCATOR
void* __CRTDECL operator new(
	size_t _Size
)
{
#ifdef USE_CUSTOM
	return Memory::MemorySystem::allocate(_Size);
#else
	return malloc(_Size);
#endif
}

void __CRTDECL operator delete(
	void* _Block
) noexcept
{
#ifdef USE_CUSTOM
	Memory::MemorySystem::freeMem(_Block);
#else
	free(_Block);
#endif
}

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(_Size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](
	size_t _Size
)
{
#ifdef USE_CUSTOM
	return Memory::MemorySystem::allocate(_Size);
#else
	return malloc(_Size);
#endif
}

void __CRTDECL operator delete[](
	void* _Block
) noexcept
{
#ifdef USE_CUSTOM
	Memory::MemorySystem::freeMem(_Block);
#else
	free(_Block);
#endif
}

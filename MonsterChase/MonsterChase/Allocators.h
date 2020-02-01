#pragma once
#include <cinttypes>
#include "MemorySystem.h"

#define malloc(x) customMalloc(x)
#define realloc(x, y) customRealloc(x, y)
#define free(x) customFree(x)

void* customMalloc(size_t size);
void* customRealloc(void* pointer, size_t contiguousMemorySizeRequired);
void customFree(void* pointer);

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(_Size) _VCRT_ALLOCATOR
void* __CRTDECL operator new(
	size_t _Size
);

void __CRTDECL operator delete(
	void* _Block
) noexcept;

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(_Size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](
	size_t _Size
);

void __CRTDECL operator delete[](
	void* _Block
) noexcept;

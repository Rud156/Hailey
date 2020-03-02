#pragma once

#include <cinttypes>

void* cMalloc(size_t _Size);
void cFree(void* _Block);
void* cRealloc(void* _Block, size_t _Size);

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

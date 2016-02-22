#ifndef _STRING_
#define _STRING_
#include <stdint.h>
#include <stddef.h>

#include <lib/error.h>

typedef uint8_t byte;

typedef uint32_t dword;

typedef uint16_t word;

size_t strlen(const char* str);

void* memcpy(void* src, void* dst, size_t size);

void* memset(void* dst, byte z, size_t size);

#endif

#ifndef __NOSTDIO__
#define __NOSTDIO__
#include <stdint.h>
#include <stdarg.h>

void kprint(const char *fmt, ...);

void sprintf(char *buffer, const char *fmt, ...);

int kvprintf(char const *fmt, void (*func)(uint8_t, void*), void *arg, int radix, va_list ap);

#define TEDIOS_MAL_DEBUG

#endif

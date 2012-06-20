#ifndef FMT_H
#define FMT_H
#include <stdarg.h>
#include <stdio.h>
#include "exception.h"

typedef void (*fmt_t)(int code, va_list *ap,
		int put(int c, void *cl), void *cl,
		unsigned char flags[256], int width, int precision);
extern char *fmt_flags;
extern const exception_t fmt_overflow;
extern void fmt_fmt(int put(int c, void *cl), void *cl,
		const char *fmt, ...);
extern void fmt_vfmt(int put(int c, void *cl), void *cl,
		const char *fmt, va_list ap);
extern void fmt_print(const char *fmt, ...);
extern void fmt_fprint(FILE *stream, const char *fmt, ...);
extern int fmt_snprint(char *buf, int size, const char *fmt, ...);
extern int fmt_vnprint(char *buf, int size, const char *fmt, va_list ap);
extern char *fmt_string(const char *fmt, ...);
extern char *fmt_vstring(const char *fmt, va_list ap);
extern fmt_t fmt_register(int code, fmt_t cvt);
extern void fmt_putd(const char *str, int len, int put(int c, void *cl),
		void *cl, unsigned char flags[256], int width, int precision);
extern void fmt_puts(const char *str, int len, int put(int c, void *cl),
		void *cl, unsigned char flags[256], int width, int precision);


#endif

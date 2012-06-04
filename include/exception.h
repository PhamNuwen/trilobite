#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <setjmp.h>
typedef struct T{
    const char *reason;
}Exception_t;
#define RAISE(e) Exception_raise(&(e), __FILE__, __LINE__)

void Exception_raise(const Exception_t *e, const char *file, int line);

#endif

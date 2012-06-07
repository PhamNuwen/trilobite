#undef assert
#ifdef NDEBBUG
#define assert(e) ((void)0)
#else
#include "exception.h"
extern void assert(int e);
extern exception Assertion_Fail;
#define assert(e) ((void)((e)||(RAISE(Assertion_Fail), 0)))
#endif

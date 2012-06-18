#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "exception.h"
#include "mem.h"

static struct discriptor{
	struct descriptor *free;
	struct descroptor *link;
	const void* ptr;
	long size;
	const char *file;
	int line;
}*htab[2048];

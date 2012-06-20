#ifndef ARRAYREP_H
#define ARRAYREP_H
struct array{
	int length;
	int size;
	char *array;
};

extern void arrayrep_init(array_t array, int length, int size, void *ary);
#endif

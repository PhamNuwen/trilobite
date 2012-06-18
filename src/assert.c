#include "assert.h"
const exception_t Assertion_Fail = {"Assertion failed!"};
void (assert)(int e){
	assert(e);
}

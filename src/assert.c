#include "assert.h"
const exception Assertion_Fail = {"Assertion failed!"};
void (assert)(int e){
	assert(e);
}

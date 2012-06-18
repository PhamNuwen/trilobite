#include "exception.h"
#include "assert.h"
#include <stdio.h>

exception_t aaa={"No Money"};
exception_t bbb={"Still No Money"};

int f(){
	RAISE(aaa);
	return 1;
}

int tst_exception(){
	int exceptions = 0;
	TRY
		f();
		RAISE(bbb);
	EXCEPT(aaa)
		exceptions++;
	EXCEPT(bbb)
		exceptions++;
	END_TRY;
	return exceptions;
}

int tst_assertion(){
	int i=0;
	TRY
		assert(i);
	EXCEPT(Assertion_Fail)
		i++;
	END_TRY;
	return i;
}


int main(){

	if(tst_exception()==1)printf("Pass\n");
	if(tst_assertion())printf("Pass\n");
	return 0;
}

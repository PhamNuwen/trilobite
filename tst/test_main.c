#include "exception.h"
#include <stdio.h>

int main(){
	exception aaa={"No Money"};
	TRY
		printf("A New exception %s\n", aaa.reason);
		RAISE(aaa);
	EXCEPT(aaa)
		printf("Ha\n");
	END_TRY;
	return 0;
}

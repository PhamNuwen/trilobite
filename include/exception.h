#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <setjmp.h>
typedef struct exception exception;
struct exception{
    const char *reason;
};
typedef struct exception_frame exception_frame;
struct exception_frame{
	exception_frame *prev;
	jmp_buf env;
	const char *file;
	int line;
	const exception_t *exception;
};
enum { exception_entered=0, exception_raised,
       exception_handled,   exception_finalized };
extern exception_frame *_Ex_stack_top;
#define	RAISE(e)	exception_raise(&(e), __FILE__, __LINE__)
#define RERAISE		exception_raise(exception_frame.exception, exception_frame.file, exception_frame.line)
#define RETURN		switch (_Ex_stack = _Ex_stack->prev,0) default:return
#define TRY \
	do{\
		volatile int _Ex_flag;\
		exception_Frame _Ex_frame;\
		_Ex_frame.prev = _Ex_stack_top;\
		_Ex_stack_top = &_Ex_frame;\
		_Ex_flag = setjmp(_Ex_frame.env);\
		if (_Ex_flag == exception_entered){
#define EXCEPT(e) \
			if(_Ex_flag == exception_entered)\
				_Ex_stack = _Exstack->prev;\
		}\
		else if(_Ex_frame.exception == &(e)){\
			_Ex_flag = exception_handled;
#define ELSE \
			if(_Ex_flag == exception_entered)\
					_Ex_stack = _Exstack->prev;\
		}\
		else{\
			_Ex_flag = exception_handled;
#define FINALLY \
			if(_Ex_flag == exception_entered)\
				_Ex_flag = exception_handled;\
		}\
		{\
			if(_Ex_flag == exception_entered)\
				_Ex_flag = exception_finalized;\
#define END_TRY \
			if(_Ex_flag == exception_entered)\
				_Ex_flag = exception_handled;\
		}\
		if (_Ex_flag == exception_raised)\
			RERAISE;\
	}while(0)
void exception_raise(const Exception_t *e, const char *file, int line);

#endif

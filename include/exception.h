#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <setjmp.h>
typedef struct exception exception_t;
struct exception{
    const char *reason;
};
typedef struct exception_frame exception_frame_t;
struct exception_frame{
	exception_frame_t *prev;
	jmp_buf env;
	const char *file;
	int line;
	const exception_t *exception;
};
enum { exception_entered=0, exception_raised,
       exception_handled,   exception_finalized };
extern exception_frame_t *_Ex_stack_top;
void exception_raise(const exception_t *e, const char *file, int line);
#define	RAISE(e)	exception_raise(&(e), __FILE__, __LINE__)
#define RERAISE		exception_raise(_Ex_frame.exception, _Ex_frame.file, _Ex_frame.line)
#define RETURN		switch (_Ex_stack_top = _Ex_stack_top->prev,0) default:return
#define TRY \
	do{\
		volatile int _Ex_flag;\
		exception_frame_t _Ex_frame;\
		_Ex_frame.prev = _Ex_stack_top;\
		_Ex_stack_top = &_Ex_frame;\
		_Ex_flag = setjmp(_Ex_frame.env);\
		if (_Ex_flag == exception_entered){
#define EXCEPT(e) \
			if(_Ex_flag == exception_entered)\
				_Ex_stack_top = _Ex_stack_top->prev;\
		}\
		else if(_Ex_frame.exception == &(e)){\
			_Ex_flag = exception_handled;
#define ELSE \
			if(_Ex_flag == exception_entered)\
					_Ex_stack_top = _Exstack_top->prev;\
		}\
		else{\
			_Ex_flag = exception_handled;
#define FINALLY \
			if(_Ex_flag == exception_entered)\
				_Ex_flag = exception_handled;\
		}\
		{\
			if(_Ex_flag == exception_entered)\
				_Ex_flag = exception_finalized;
#define END_TRY \
			if(_Ex_flag == exception_entered)\
				_Ex_flag = exception_handled;\
		}\
		if (_Ex_flag == exception_raised)\
			RERAISE;\
	}while(0)


#endif

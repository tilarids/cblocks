#include <stdlib.h>
#include <ucontext.h>

#define DECLARE_GENERATOR(type, name, params) extern ucontext_t name ## _context__; \
extern ucontext_t name ## _out_context__; \
extern int name ## _finished__; \
extern type name ## _out_var__; \
extern void name ## _fun__ params

#define START_GENERATOR(type, name, params) ucontext_t name ## _context__; \
ucontext_t name ## _out_context__; \
int name ## _finished__ = 0; \
type name ## _out_var__; \
void name ## _fun__ params \
{ \
name ## _finished__ = 0; \
int* current_finished = & name ## _finished__; \
ucontext_t* current_context = & name ## _context__; \
ucontext_t* current_out_context = & name ## _out_context__; \
type* current_var = & name ## _out_var__;

#define END_GENERATOR *current_finished = 1; \
}

#define YIELD(x) *current_var = x; swapcontext(current_context, current_out_context);
#define EXECUTE_BLOCK(gen, params, type, varname) do{ type* varname = & gen ## _out_var__; \
ucontext_t* current_context = & gen ## _context__; \
ucontext_t* current_out_context = & gen ## _out_context__; \
volatile int gen ## _temp_var__ = 0; \
getcontext(& gen ## _out_context__); \
if (gen ## _temp_var__ == 0) \
{ \
    gen ## _temp_var__ = 1; \
    gen ## _fun__ params; \
}\
else \
{ \
    while (! gen ## _finished__) { 
         
#define END_BLOCK swapcontext(current_out_context, current_context); } \
} \
} while(0);


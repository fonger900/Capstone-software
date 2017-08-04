#ifndef __capstone_h
#define __capstone_h

extern void cp_process_expression(const char* ,const char *, const char* );

extern void cp_print_usage(FILE* ,int , const char* );

extern void cp_execute_argList(int , char**);
#endif

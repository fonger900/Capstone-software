#include <python2.7/Python.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/capstone.h"
//#include <stdarg.h>

PyObject* cp_process_expression(const char* filename,const char *func_name, const char* arg)
{
    FILE*        exp_file;
    PyObject*    main_module, * global_dict, * expression,*anObj;    
    //va_list args;
    
    //initialize args to store all variable after 'arg'
    //va_start (args, arg);
    
     
    // Open and execute the Python file
    exp_file = fopen(filename, "r");
    PyRun_SimpleFile(exp_file, filename);

    // Get a reference to the main module
    // and global dictionary
    main_module = PyImport_AddModule("__main__");
    global_dict = PyModule_GetDict(main_module);

    // Extract a reference to the function "func_name"
    // from the global dictionary
    expression =
        PyDict_GetItemString(global_dict, func_name);

    //char* arg2 = va_arg(args,char*);
    //if(arg2==NULL)
    //anObj = PyObject_CallObject(expression,arg);
    anObj = PyObject_CallFunction(expression,"s",arg);        
    //va_end(args);//clean up the list
    
    return anObj;
    //PyRun_SimpleString("print x");
}

PyObject* cp_process_expression(const char* filename,const char *func_name, const char* arg1,const char* arg2)
{
    FILE*        exp_file;
    PyObject*    main_module, * global_dict, * expression,*anObj;    
     
    // Open and execute the Python file
    exp_file = fopen(filename, "r");
    PyRun_SimpleFile(exp_file, filename);

    // Get a reference to the main module
    // and global dictionary
    main_module = PyImport_AddModule("__main__");
    global_dict = PyModule_GetDict(main_module);

    // Extract a reference to the function "func_name"
    // from the global dictionary
    expression =
        PyDict_GetItemString(global_dict, func_name);
    //PyImport_ImportModule("parse_log");
    anObj = PyObject_CallFunction(expression,"ss",arg1,arg2);
    
    return anObj;
}

PyObject* cp_process_expression(const char* filename,const char *func_name, const char* arg1,const char* arg2,const char* arg3)
{
    FILE*        exp_file;
    PyObject*    main_module, * global_dict, * expression,*anObj;    
     
    // Open and execute the Python file
    exp_file = fopen(filename, "r");
    PyRun_SimpleFile(exp_file, filename);

    // Get a reference to the main module
    // and global dictionary
    main_module = PyImport_AddModule("__main__");
    global_dict = PyModule_GetDict(main_module);

    // Extract a reference to the function "func_name"
    // from the global dictionary
    expression =
        PyDict_GetItemString(global_dict, func_name);
    //PyImport_ImportModule("parse_log");
    anObj = PyObject_CallFunction(expression,"sss",arg1,arg2,arg3);
    
    return anObj;
}

//print usage information
void cp_print_usage(FILE* stream,int exit_code,const char* program_name)
{
  
  fprintf(stream,"Usage: %s options [inputfile ...]\n",program_name);
  fprintf(stream,
	  " -h --help        Display this usage information.\n"
	  " -o --output --filename Wite output to file.\n"
	  " -v --verbose Print verbose messages.\n");
  exit (exit_code);
}


void cp_execute_argList(int argc, char **argv)
{
  int next_option;
  //strcpy(program_name,"capstone");
  //a string list short option letter
  const char* program_name;
  const char* const short_options="ho:v";
  //an array describing valid long option
  const struct option long_options[]={
    {"help", 0, NULL, 'h'},
    {"output", 1, NULL, 'o'},
    {"verbose", 0, NULL, 'v'},
    {NULL, 0, NULL, 0} //require at end of array
  };

  //name of the file to receive program output, or NULL for standard output
  const char* output_filename=NULL;
  //whether to display verbose message
  int verbose=0;
  //remember the name of the program to incoporate in message. The name is stored in argv[0]
  program_name=argv[0];

  do{
    next_option=getopt_long(argc,argv,short_options,long_options,NULL);
    switch(next_option)
      {
      case 'h': //--help
	cp_print_usage(stdout,0,program_name);
      case 'o': //--output
	output_filename=optarg;
	break;
      case 'v': //--verbose
	verbose=1;
	break;
      case '?': //user specified an invalid option
	cp_print_usage(stderr,1,program_name);
      case -1: //done with option
	break;
      default:
	abort();
      }
  }while(next_option !=-1);

  if(verbose)
    {
      for (int i = optind; i < argc; ++i)
	{
	  printf("Argument: %s\n",argv[i]);
	}
    }
  /*
  printf("Name of program: %s\n",argv[0]);
  printf("Nmber of argument of program: %d\n",argc-1);
  if(argc>1)
    {
      int i;
      printf("the argument are: \n");
      for(i=1;i<argc;i++)
	{
	  printf(" %s\n",argv[i]);
	}
    }
  */
}
/*
void insert_substring(char *a, char *b, int position)
{
   char *f, *e;
   int length;
 
   length = strlen(a);
 
   f = substring(a, 1, position - 1 );      
   e = substring(a, position, length-position+1);
 
   strcpy(a, "");
   strcat(a, f);
   free(f);
   strcat(a, b);
   strcat(a, e);
   free(e);
}
 
char *substring(char *string, int position, int length) 
{
   char *pointer;
   int c;
 
   pointer = malloc(length+1);
 
   if( pointer == NULL )
       exit(EXIT_FAILURE);
 
   for( c = 0 ; c < length ; c++ ) 
      *(pointer+c) = *((string+position-1)+c);       
 
   *(pointer+c) = '\0';
 
   return pointer;
}
*/

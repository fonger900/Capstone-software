#include <libconfig.h>
#include <python2.7/Python.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/capstone.h"

/*Main program entry point. Argc contains number pf argument list element,
  argv is an array of ponter to them*/
int main(int argc, char *argv[])
{
  //execute cmd agument and dispplay usage
  cp_execute_argList(argc,argv);

  //main program goes there
  config_t cfg;
  config_init(&cfg);
  const char* filename;
  const char* func_name;
  const char* arg;
  
  //read file, if error then exit
  if(!config_read_file(&cfg,"/home/phong/project/git_prj/Capstone-software/src/m.cfg"))
    {
      fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
            config_error_line(&cfg), config_error_text(&cfg));
      config_destroy(&cfg);
      return(EXIT_FAILURE);
    }

  //get store name
  if(!config_lookup_string(&cfg, "core_engine", &filename))
    fprintf(stderr, "No 'core_engine' setting in configuration file.\n");

  if(!config_lookup_string(&cfg, "log_data", &arg))
    fprintf(stderr, "No 'log_data' setting in configuration file.\n");

  if(!config_lookup_string(&cfg,"func_name",&func_name))
    fprintf(stderr, "No 'func_name' setting in configuration file.\n");

  //pyhton interpreter  
  Py_Initialize();
  cp_process_expression(filename,func_name,arg);
  //exit config parser
  config_destroy(&cfg);
  return(EXIT_SUCCESS);
  Py_Finalize();

}

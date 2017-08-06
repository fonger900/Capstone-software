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
  
  const char* predict_engine;
  const char* parser_output_dir;
  const char* rule_dir;
  const char* log_dir;
  
  //read file, if error then exit
  if(!config_read_file(&cfg,"/home/phong/project/git_prj/Capstone-software/src/m.cfg"))
    {
      fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
            config_error_line(&cfg), config_error_text(&cfg));
      config_destroy(&cfg);
      return(EXIT_FAILURE);
    }

  //get store name
  if(!config_lookup_string(&cfg, "predict_engine", &predict_engine))
    fprintf(stderr, "No 'predict_engine' setting in configuration file.\n");

  if(!config_lookup_string(&cfg,"log_dir",&log_dir))
    fprintf(stderr, "No 'parser' setting in configuration file.\n");
   
  if(!config_lookup_string(&cfg, "rule_dir", &rule_dir))
    fprintf(stderr, "No 'rule_dir' setting in configuration file.\n");

  if(!config_lookup_string(&cfg, "parser_output_dir", &parser_output_dir))
    fprintf(stderr, "No 'parser_output_dir' setting in configuration file.\n");
  
  //pyhton interpreter  
  Py_Initialize();

  //get current working directory path
  PyObject* mymod,*strret,*strfunc;
  char* cwd;
  mymod= PyImport_ImportModule("os");
  strfunc = PyObject_GetAttrString(mymod,"getcwd");
  strret = PyObject_CallFunction(strfunc,NULL);
  PyArg_Parse(strret,"s",&cwd);
  
  char * engine_name ;
  if((engine_name = (char*)malloc(strlen(predict_engine)+strlen(cwd)+1)) != NULL){
    engine_name[0] = '\0';   // ensures the memory is an empty string
    strcat(engine_name,cwd);
    strcat(engine_name,predict_engine);
  } else {
    fprintf(stderr,"malloc failed!\n");

   printf("engine main: %s\n",engine_name);
    // exit?
  }
  /*
  char *path, *newpath;
  path=Py_GetPath();
  printf("path = %s\n",path);
  newpath=strcat(path, ":/home/phong/project/git_prj/Capstone-software/src"); // or ":.", possibly
  printf("newpath = %s\n",newpath);
  PySys_SetPath(newpath);
  PyImport_ImportModule("pandas");
  free(newpath);*/
  
  /*
  Py_Object* py_string;
  py_string = cp_process_expression(parser,"parse_log",log_dir,parser_output_dir);
  py_string = PyObject_Repr( py_string);//get string representation of PyObject
  parser_output_filename = PyString_AsString(py_string);
  //parser_output_filename = "/home/phong/project/git_prj/Capstone-software/output_data/conn.2017-07-28-16-00-00.csv";
  cp_process_expression(predict_engine,"run_predict",parser_output_filename);
 
  cp_process_expression(parser,"extract_average_log",parser_output_dir,rule_dir);
  */
  
  cp_process_expression(engine_name,"main",log_dir,parser_output_dir,rule_dir);
  
  Py_Finalize();

  //exit config parser
  config_destroy(&cfg);
  return(EXIT_SUCCESS);
}

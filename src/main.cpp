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

  //pyhton interpreter
  Py_Initialize();

  //get current working directory path
  PyObject* mymod,*strret,*strfunc;
  char* cwd;
  mymod= PyImport_ImportModule("os");
  strfunc = PyObject_GetAttrString(mymod,"getcwd");
  strret = PyObject_CallFunction(strfunc,NULL);
  PyArg_Parse(strret,"s",&cwd);
  
  config_t cfg;
  config_init(&cfg);
  
  const char* predict_engine;
  const char* parser_output_dir;
  const char* rule_dir;
  const char* log_dir;
  const char* cfg_file="/src/getdosrule.cfg";
  
  //read file, if error then exit
  cfg_file = cp_strcat(cwd,cfg_file);
  if(!config_read_file(&cfg,cfg_file))
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
  
  /*
  char *path, *newpath;
  path=Py_GetPath();
  printf("path = %s\n",path);
  newpath=strcat(path, ":/home/phong/project/git_prj/Capstone-software/src"); // or ":.", possibly
  printf("newpath = %s\n",newpath);
  PySys_SetPath(newpath);
  PyImport_ImportModule("pandas");
  free(newpath);*/
  predict_engine = cp_strcat(cwd,predict_engine);
  parser_output_dir = cp_strcat(cwd,parser_output_dir);
  //printf("main: %s",parser_output_dir);
  /*
  Py_Object* py_string;
  py_string = cp_process_expression(parser,"parse_log",log_dir,parser_output_dir);
  py_string = PyObject_Repr( py_string);//get string representation of PyObject
  parser_output_filename = PyString_AsString(py_string);
  //parser_output_filename = "/home/phong/project/git_prj/Capstone-software/output_data/conn.2017-07-28-16-00-00.csv";
  cp_process_expression(predict_engine,"run_predict",parser_output_filename);
 
  cp_process_expression(parser,"extract_average_log",parser_output_dir,rule_dir);
  */
  
  cp_process_expression(predict_engine,"main",log_dir,parser_output_dir,rule_dir);
  
  Py_Finalize();

  //exit config parser
  config_destroy(&cfg);
  return(EXIT_SUCCESS);
}

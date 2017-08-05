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
  const char* parser;
  const char* parser_output_dir;
  const char* rule_dir;
  const char* log_dir;
  const char* parser_output_filename;

  PyObject* py_string;
  
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

  if(!config_lookup_string(&cfg, "parser", &parser))
    fprintf(stderr, "No 'core_engine' setting in configuration file.\n");
   
  if(!config_lookup_string(&cfg,"log_dir",&log_dir))
    fprintf(stderr, "No 'parser' setting in configuration file.\n");
   
  if(!config_lookup_string(&cfg, "rule_dir", &rule_dir))
    fprintf(stderr, "No 'rule_dir' setting in configuration file.\n");

  if(!config_lookup_string(&cfg, "parser_output_dir", &parser_output_dir))
    fprintf(stderr, "No 'parser_output_dir' setting in configuration file.\n");
  
  //pyhton interpreter  
  Py_Initialize();

  char *path, *newpath;

  path=Py_GetPath();
  newpath=strcat(path, ":."); // or ":.", possibly
  //printf("newpath = %s",newpath);
  //PySys_SetPath(newpath);
  free(newpath);
  /*parser_output_dir = "/home/phong/project/git_prj/Capstone-software/output_data/";

  rule_dir = "/home/phong/project/git_prj/Capstone-software/test/rules/";

  log_dir = "/home/phong/project/git_prj/Capstone-software/test/log/";*/
  //PyImport_ImportModule("parse_log");
  
  py_string = cp_process_expression(parser,"parse_log",log_dir,parser_output_dir);
  py_string = PyObject_Repr( py_string);//get string representation of PyObject
  parser_output_filename = PyString_AsString(py_string);
  parser_output_filename = "/home/phong/project/git_prj/Capstone-software/output_data/conn.2017-07-28-16-00-00.csv";
  cp_process_expression(predict_engine,"run_predict",parser_output_filename);
 
  cp_process_expression(parser,"extract_average_log",parser_output_dir,rule_dir);
  //printf("%s,%s,%s\n",  parser_output_dir,log_dir,rule_dir);
  //cp_process_expression2(predict_engine,"main",log_dir,parser_output_dir,rule_dir);
  
  Py_Finalize();

  //exit config parser
  config_destroy(&cfg);
  return(EXIT_SUCCESS);
}

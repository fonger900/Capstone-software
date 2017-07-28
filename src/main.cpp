#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

//the name of this program
const char* program_name;

//print usage information
void print_usage(FILE* stream,int exit_code)
{
  fprintf(stream,"Usage: %s options [inputfile ...]\n",program_name);
  fprintf(stream,
	  " -h --help        Display this usage information.\n"
	  " -o --output --filename Wite output to file.\n"
	  " -v --verbose Print verbose messages.\n");
  exit (exit_code);
}

/*Main program entry point. Argc contains number pf argument list element,
  argv is an array of ponter to them*/

int main(int argc, char *argv[])
{
  int next_option;

  //a string list short option letter
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
	print_usage(stdout,0);
      case 'o': //--output
	output_filename=optarg;
	break;
      case 'v': //--verbose
	verbose=1;
	break;
      case '?': //user specified an invalid option
	print_usage(stderr,1);
      case -1: //done with option
	break;
      default:
	abort();
      }
  }while(next_option !=-1);

  if(verbose)
    {
      int i;
      for (int i = optind; i < argc; ++i)
	{
	  printf("Argument: %s\n",argv[i]);
	}
    }

  //main program goes there
  
  printf("Name of program: %s",argv[0]);
  printf("Nmber of argument of program: %d",argc-1);
  if(argc>1)
    {
      int i;
      printf("the argument are: \n");
      for(i=1;i<argc;i++)
	{

	  printf(" %s\n",argv[i]);
	}
    }
	return 0;
}

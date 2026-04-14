#include <stdio.h>  //printf, fprintf
#include <stdlib.h> //EXIT_SUCCESS
#include <string.h> //strlen, strcmp
#define TOO_MANY_ARGS 2
#define TOO_FEW_ARGS 1

int main(int argc, char* argv[]) {
    //Default values:
    int exit_code = EXIT_SUCCESS;
    char * greeting = "Hello";
    char * person = "UNKNOWN";
    //If only one argument to command, returns exit code zero 
    if (argc==1){
        //person becomes "UNKOWN"
        exit_code = TOO_FEW_ARGS;
     //If two arguments to command, second word in array is returned for 'person'
    } else if (argc == 2) {
        exit_code = EXIT_SUCCESS;
        person = argv[1];
     //If three or more arguments, only returns the argument in the same way as case 2
    } else {
        exit_code = TOO_MANY_ARGS;
        person = argv[1];
    }
    
    //Add code to change 'person' if one is given on command line
    
    int len = strlen(argv[0]);
    char * last3 = argv[0] + len - 3; //last3 points to last 3 chars
    //made the lines below into comments so the output is exactly as desired from the lab manual
    //fprintf(stderr, "%s\n", argv[0]);
   // fprintf(stderr, "%s\n", last3);
    
    //Add code to change 'greeting' if last 3 chars of command are 'bye'
    if (len >= 3 && strcmp(last3, "bye") == 0){
        greeting = "Bye";
    }
    printf("%s %s\n", greeting, person);
    
    fprintf(stderr, "exit_code: %d\n", exit_code);
    
    return exit_code; //Could also say exit(exit_code)
}
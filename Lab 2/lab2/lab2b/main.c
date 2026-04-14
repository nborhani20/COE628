#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//repetition
#define N_REPS 50
#define DEFAULT_SLOWDOWN 10000

int main(int argc, char * argv[]) {
    int i;
    //add delay between each character printed
    int slow_down = DEFAULT_SLOWDOWN;

    //case 1: no string message provided 
    if (argc == 1) {
        fprintf(stderr, "Usage: %s string [delay]\n", argv[0]);
        return 1;
    }
    //if delay value provided, override it with provided value
    if (argc >= 3) {
        slow_down = atoi(argv[2]);
    }
    //print the string N_REPS number of times
    for (i = 0; i < N_REPS; i++) {
        //points to first character of given string 
        char * cp = argv[1];
        //critical section starts
        //creates the directory 'junk' only if it does not already exist
        while (system("mkdir junk 2>/dev/null") != 0);
        while (*cp) {
            printf("%c", *cp++);
            fflush(stdout);
            usleep(random() % slow_down);
        }
        //critical section ends 
        //removes the directory so that the next process can proceed
        system("rmdir junk");
        //pause before the next repetition
        usleep(5000);
    }
    return EXIT_SUCCESS;
}
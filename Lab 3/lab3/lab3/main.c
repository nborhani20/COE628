/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: nborhani
 *
 * Created on February 3, 2026, 7:06 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*the maximum length assigned based on lab manual*/
#define MAXLINE 100
#define MAXARGS 20

int main(void) {
    /*Store command line provided by user*/
    char line[MAXLINE + 1];
    char *argv[MAXARGS];
    int ch;

    /*The shell will run until the user inputs the exit command or EOF*/
    while (1) {
        /* Prints command prompt immediately*/
        printf("Your command> ");
        fflush(stdout);
        /* Read one line one character at  time until newline or EOF */
        int i = 0;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /*Store the character if the maximum (100) is not yet exceeded*/
            if (i < MAXLINE) line[i++] = (char)ch;
        }
        /* If EOF is entered exit the shell */
        if (ch == EOF && i == 0) {
            putchar('\n');
            break;
        }
        /* null terminator*/
        line[i] = '\0';

        /* Ignore empty input */
        if (i == 0) continue;
        
        /* Check for '&' */
        int background = 0;
        if (i > 0 && line[i - 1] == '&') {
            background = 1;
            /* remove '&' and proceed as normal */
            line[i - 1] = '\0';  
        }

        /*parse for lines with multiple word commands*/
        int argc = 0;
        char *p = line;

        /* Skip spaces */
        while (*p == ' ') p++;

        while (*p != '\0' && argc < MAXARGS - 1) {
            argv[argc++] = p;        
            /* advance to the space while the character is not null or spcae*/
            while (*p != '\0' && *p != ' ') p++; 
            /* if the character is a space, replace will null */
            if (*p == ' ') {
                *p = '\0';             
                p++;
                while (*p == ' ') p++; 
            }
        }
        /* for execvp(), set last character to null*/
        argv[argc] = NULL;

        if (argc == 0) continue;

          if (argc == 1 && argv[0][0]=='e' && argv[0][1]=='x' && argv[0][2]=='i' && argv[0][3]=='t' && argv[0][4]=='\0') {
            break;
        }
        
        pid_t pid = fork();
        /* case that process failed */
        if (pid < 0) {
            perror("fork");
            continue;
        }
        if (pid == 0) {
            /* replace the child process with the requested program*/
            execvp(argv[0], argv);
            /* failed if execvp returns */
            perror("execvp");
            _exit(127);
        } else {
            /* parent process waits for child process if the command is not background */
            if (!background) {
                int status;
                if (waitpid(pid, &status, 0) < 0) {
                    perror("waitpid");
                }
            }
        }
    }
    return (EXIT_SUCCESS);
}

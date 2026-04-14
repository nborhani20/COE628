/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: nborhani
 *
 * Created on February 25, 2026, 11:47 PM
 */

#include  <stdio.h> /* printf */
#include  <sys/types.h> /* pid_t */
#include <unistd.h> /* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h>  /* wait */
#include <pthread.h>
#include <sys/stat.h>

void * count(void *);
int globalNumber = 0;
//Create a mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
    int i;
    pthread_t counterThread[5];


    //Create the 5 threads
    for (i=0; i<5; i++){
        pthread_create(&counterThread[i], NULL, count, NULL);
    }
    //Wait for all treads to finish
    for (i=0; i<5; i++){
        //blocks until thread is finished
        pthread_join(counterThread[i], NULL);
    }
    //print the final value after all the threads are completed
    printf("Final globalNumber: %d\n", globalNumber);
    return (0);
}

//function executed by each individual thread
void * count(void * junk) {
    int loopCount = 0;
    //lock mutex so only one thread can enter at a time
    pthread_mutex_lock(&mutex1);
    while (loopCount < 10) {
        int tmpNumber = globalNumber;
        //print current counter, thread ID, process ID
        printf("counter: %d, Thread: %ld, PID: %d\n",
                tmpNumber, pthread_self(), getpid());
        //increment 
        tmpNumber = globalNumber;
        tmpNumber++;
        usleep(random() % 2);
        globalNumber = tmpNumber;
        //increase loop counter
        loopCount++;
    }
    //unlock mutex for next thread to enter 
    pthread_mutex_unlock(&mutex1);
    return (0);
}

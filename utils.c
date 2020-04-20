#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"
#include "priority.h"

void unit_time(){
    volatile unsigned long i;
    for(i = 0; i < TIME_UNIT; i ++);
}

long get_time(){
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_sec * 1000000000L + t.tv_nsec;
}

int create_process(char *name, int T){
    pid_t pid = fork();
    if(pid < 0){
        fprintf(stderr, "error: fork\n");
        exit(0);
    }
    if(pid == 0){
        char execution_time[20];
        sprintf(execution_time, "%d", T);
        execl("./process", "./process", name, execution_time, NULL);
    }
    else{
        set_priority(pid, SCHED_FIFO, PRIORITY_INIT);
        use_cpu(pid, 1);
    }
    return pid;
}
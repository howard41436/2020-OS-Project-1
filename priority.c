#define _GNU_SOURCE

#include <sys/types.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>

void use_cpu(pid_t pid, int x){
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET((x), &mask);
    if(!sched_setaffinity((pid), sizeof(mask), &mask)){
        fprintf(stderr, "error: sched_setaffinity\n");
        exit(0);
    }
}

void set_priority(pid_t pid, int policy, int priority){
    struct sched_param param;
    param.sched_priority = priority;
    if(!sched_setscheduler(pid, policy, &param)){
        fprintf(stderr, "error: sched_setscheduler\n");
        exit(0);
    }
}
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"

void unit_time(){
    volatile unsigned long i;
    for(i = 0; i < TIME_UNIT; i ++);
}

long get_time(){
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_sec * 1000000000L + t.tv_nsec;
}
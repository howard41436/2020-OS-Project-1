#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include "utils.h"

int main(int argc, char **argv){
    long start_time = get_time();
    pid_t pid = getpid();
    char *name = argv[1];
    int execution_time = strtol(argv[2]);
    for(int i = 0; i < execution_time; i ++)
        unit_time();
    long finish_time = get_time();
    FILE* demsg = fopen("/dev/kmsg", "a");
    fprintf(dmesg,"[Project1] %d %ld.%09ld %ld.%09ld\n", pid,
            start_time / BASE, start_time % BASE,
            finish_time / BASE, finish_time % BASE);
    fclose(dmesg);
}
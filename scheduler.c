#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "utils.h"
#include "policy.h"
#include "priority.h"

int main(){
    use_cpu(getpid(), 0);
    set_priority(getpid(), SCHED_FIFO, PRIORITY_INIT);

    char policy[MAX_NAME_LEN];
    scanf("%s", policy);
    int n, ready_time[MAX_N], execution_time[MAX_N];
    char name[MAX_N][MAX_NAME_LEN];

    for(int i = 0; i < n; i ++)
        scanf("%s %d %d", &name[i], &ready_time[i], &execution_time[i]);
    
    int waiting_queue[MAX_N][MAX_FEATURES];
    for(int i = 0; i < n; i ++){
        waiting_queue[i][0] = i;
        waiting_queue[i][1] = ready_time[i];
        waiting_queue[i][2] = execution_time[i];
    }

    if(policy[0] == 'F')
        FIFO(n, name, waiting_queue, execution_time);
    else if(policy[0] == 'R')
        RR(n, name, waiting_queue, execution_time);
    else if(policy[0] == 'S')
        SJF(n, name, waiting_queue, execution_time);
    else if(policy[0] == 'P')
        PSJF(n, name, waiting_queue, execution_time);
}
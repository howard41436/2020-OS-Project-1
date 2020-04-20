#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include "utils.h"
#include "policy.h"
#include "priority.h"

int wq_size, rq_size;
void FIFO(int n, char **name, int **waiting_queue, int *execution_time{
    int idx[MAX_N], waiting_key[MAX_FEATURES] = {1, 0, -1};
    sort(idx, waiting_queue, waiting_key);
    int ready_queue[MAX_N][MAX_FEATURES];
    wq_size = n, rq_size = 0;
    pid_t pids[MAX_N] = {};
    int cur_i = -1, cur_finish_time = -1;
    for(int t = 0;;t ++){
        while(wq_size && waiting_queue[0][1] == t){
            // push
            ready_queue[rq_size][0] = waiting_queue[0][0];
            ready_queue[rq_size][1] = waiting_queue[0][1];
            ready_queue[rq_size][2] = waiting_queue[0][2];
            rq_size ++;
            pop(waiting_queue);
        }
        if(t == cur_finish_time){
            if(execution_time[cur_i] == 0){
                wait(pids[cur_i]);
                if(!wq_size && !rq_size)
                    break;
                cur_i = cur_finish_time = -1;
            }
        }
    }
}
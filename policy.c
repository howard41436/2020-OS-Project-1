#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>
#include <string.h>
#include "utils.h"
#include "policy.h"
#include "priority.h"
void pop(int queue[MAX_N][MAX_FEATURES], int *size){
    for(int i = 0; i < *size - 1; i ++)
        for(int j = 0; j < MAX_FEATURES; j ++)
            queue[i][j] = queue[i + 1][j];
    *size --;
}

int compare(int *a, int *b, int *key){
    for(int i = 0;;i ++){
        if(key[i] == -1)
            return 1;
        if(a[key[i]] < b[key[i]])
            return 1;
        else if(a[key[i]] > b[key[i]])
            return 0;
    }
}

void sort(int n, int ary[MAX_N][MAX_FEATURES], int *key){
    for(int i = 0; i < n - 1; i ++){
        for(int j = 0; j < n - i - 1; j ++)
            if(!compare(ary[j], ary[j + 1], key))
                for(int k = 0; k < MAX_FEATURES; k ++){
                    int t = ary[j][k];
                    ary[j][k] = ary[j + 1][k];
                    ary[j + 1][k] = t;
                }
    }
}

void FIFO(int n, char name[MAX_N][MAX_NAME_LEN],
          int waiting_queue[MAX_N][MAX_FEATURES], int *execution_time){
    int waiting_key[MAX_FEATURES] = {1, 0, -1};
    int ready_key[MAX_FEATURES] = {1, 0, -1};
    int wq_size = n, rq_size = 0;
    sort(wq_size, waiting_queue, waiting_key);
    int ready_queue[MAX_N][MAX_FEATURES];
    pid_t pids[MAX_N] = {};
    int cur_i = -1, cur_finish_time = -1;
    for(int t = 0;;t ++){
        while(wq_size && waiting_queue[0][1] == t){
            // push
            ready_queue[rq_size][0] = waiting_queue[0][0];
            ready_queue[rq_size][1] = waiting_queue[0][1];
            ready_queue[rq_size][2] = waiting_queue[0][2];
            rq_size ++;
            pop(waiting_queue, &wq_size);
        }
        if(t == cur_finish_time){
            if(execution_time[cur_i] == 0){
                int stat;
                waitpid(pids[cur_i], &stat, 0);
                if(!wq_size && !rq_size)
                    break;
                cur_i = cur_finish_time = -1;
            }
        }
        if(~cur_i && rq_size){
            sort(rq_size, ready_queue, ready_key);
            int i = ready_queue[0][0];
            int R = ready_queue[0][1], T = ready_queue[0][2];
            pop(ready_queue, &rq_size);
            cur_i = i, cur_finish_time = t + T;
            if(!pids[cur_i]){
                pid_t pid = create_process(name[cur_i], T);
                pids[cur_i] = pid;
            }
        }
        if(~cur_i){
            execution_time[cur_i] --;
            set_priority(pids[cur_i], SCHED_FIFO, PRIORITY_HIGH);
        }
        unit_time();
    }
    for(int i = 0; i < n; i ++)
        printf("%s %d\n", name[i], pids[i]);
}
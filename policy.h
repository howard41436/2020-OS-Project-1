#include "utils.h"

void pop(int queue[MAX_N][MAX_FEATURES], int *size);
int compare(int *a, int *b, int *key);
void sort(int n, int ary[MAX_N][MAX_FEATURES], int *key);

void FIFO(int n, char name[MAX_N][MAX_NAME_LEN],
          int waiting_queue[MAX_N][MAX_FEATURES], int *execution_time);

void RR(int n, char name[MAX_N][MAX_NAME_LEN],
          int waiting_queue[MAX_N][MAX_FEATURES], int *execution_time);

void SJF(int n, char name[MAX_N][MAX_NAME_LEN],
          int waiting_queue[MAX_N][MAX_FEATURES], int *execution_time);

void PSJF(int n, char name[MAX_N][MAX_NAME_LEN],
          int waiting_queue[MAX_N][MAX_FEATURES], int *execution_time);
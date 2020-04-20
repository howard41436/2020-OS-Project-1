#define _GNU_SOURCE
#include <unistd.h>
#define TIME_UNIT 1000000UL
#define BASE 1000000000L
#define MAX_N 10
#define MAX_NAME_LEN 10
#define MAX_FEATURES 6

void unit_time();
long get_time();
int create_process(char *name, int T);
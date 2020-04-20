#define PRIORITY_INIT (int)50
#define PRIORITY_LOW (int)10
#define PRIORITY_HIGH (int)80

void use_cpu(pid_t pid, int x);

void set_priority(pid_t pid, int policy, int priority);
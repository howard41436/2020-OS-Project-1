import sys, os
def FIFO(name, ready_time, execution_time):
    n = len(name)
    waiting_queue = list(zip(range(n), name, ready_time, execution_time))
    waiting_queue.sort(key = lambda p: (p[2], p[0]))
    ready_queue = []
    start_time, finish_time = {}, {}
    t = 0
    cur_name, cur_finish_time = None, None
    while True:
        while waiting_queue and waiting_queue[0][2] == t:
            ready_queue.append(waiting_queue[0])
            waiting_queue = waiting_queue[1:]
        if t == cur_finish_time:
            finish_time[cur_name] = t
            if not ready_queue and not waiting_queue:
                break
            cur_name, cur_finish_time = None, None
        if cur_name is None and ready_queue:
            ready_queue.sort(key = lambda p: (p[2], p[0]))
            _, N, R, T = ready_queue[0]
            ready_queue = ready_queue[1:]
            cur_name = N
            start_time[cur_name] = t
            cur_finish_time = t + T
        t += 1
    return {'start_time': start_time, 'finish_time': finish_time}

def RR(name, ready_time, execution_time):
    n = len(name)
    waiting_queue = list(zip(range(n), name, ready_time, execution_time))
    waiting_queue.sort(key = lambda p: (p[2], p[0]))
    ready_queue = []
    start_time, finish_time = {}, {}
    t = 0
    time_quantum = 500
    cur_name, cur_finish_time = None, None
    while True:
        while waiting_queue and waiting_queue[0][2] == t:
            ready_queue.append(waiting_queue[0] + (-1,))
            waiting_queue = waiting_queue[1:]
        if t == cur_finish_time:
            finish_time[cur_name] = t
            if not ready_queue and not waiting_queue:
                break
            cur_name, cur_finish_time = None, None
        if cur_name is None and ready_queue:
            ready_queue.sort(key = lambda p: (p[-1], p[2], p[0]))
            i, N, R, T, last_enter = ready_queue[0]
            ready_queue = ready_queue[1:]
            cur_name = N
            if cur_name not in start_time:
                start_time[cur_name] = t
            if T <= time_quantum:
                cur_finish_time = t + T
            else:
                cur_finish_time = t + time_quantum
                ready_queue.append((i, N, R, T - time_quantum, t))
        t += 1
    return {'start_time': start_time, 'finish_time': finish_time}
def SJF(name, ready_time, execution_time):
    n = len(name)
    waiting_queue = list(zip(range(n), name, ready_time, execution_time))
    waiting_queue.sort(key = lambda p: (p[2], p[3], p[0]))
    ready_queue = []
    start_time, finish_time = {}, {}
    t = 0
    cur_name, cur_finish_time = None, None
    while True:
        while waiting_queue and waiting_queue[0][2] == t:
            ready_queue.append(waiting_queue[0] + (-1,))
            waiting_queue = waiting_queue[1:]
        if t == cur_finish_time:
            finish_time[cur_name] = t
            if not ready_queue and not waiting_queue:
                break
            cur_name, cur_finish_time = None, None
        if cur_name is None and ready_queue:
            ready_queue.sort(key = lambda p: (p[3], p[-1], p[2], p[0]))
            i, N, R, T, last_enter = ready_queue[0]
            ready_queue = ready_queue[1:]
            cur_name = N
            if cur_name not in start_time:
                start_time[cur_name] = t
            cur_finish_time = t + T
        t += 1
    return {'start_time': start_time, 'finish_time': finish_time}

def PSJF(name, ready_time, execution_time):
    n = len(name)
    waiting_queue = list(zip(range(n), name, ready_time, execution_time))
    waiting_queue.sort(key = lambda p: (p[2], p[3], p[0]))
    ready_queue = []
    start_time, finish_time = {}, {}
    t = 0
    cur_name, cur_finish_time = None, None
    while True:
        while waiting_queue and waiting_queue[0][2] == t:
            # preempt
            if cur_name is not None and\
               waiting_queue[0][3] < cur_finish_time - t:
                ready_queue.append((-1, cur_name, -1, cur_finish_time - t, t))
                cur_name, cur_finish_time = None, None
            ready_queue.append(waiting_queue[0] + (-1,))
            waiting_queue = waiting_queue[1:]
        if t == cur_finish_time:
            finish_time[cur_name] = t
            if not ready_queue and not waiting_queue:
                break
            cur_name, cur_finish_time = None, None
        if cur_name is None and ready_queue:
            ready_queue.sort(key = lambda p: (p[3], p[-1], p[2], p[0]))
            i, N, R, T, last_enter = ready_queue[0]
            ready_queue = ready_queue[1:]
            cur_name = N
            if cur_name not in start_time:
                start_time[cur_name] = t
            cur_finish_time = t + T
        t += 1
    return {'start_time': start_time, 'finish_time': finish_time}

def main():
    if len(sys.argv) == 1:
        f = sys.stdin
    else:
        f = open(sys.argv[1], 'r')
    policy = f.readline().strip()
    n = int(f.readline())
    name, ready_time, execution_time = [], [], []
    for i in range(n):
        N, R, T = f.readline().split(' ')
        R, T = int(R), int(T)
        name.append(N)
        ready_time.append(R)
        execution_time.append(T)
    result = eval(f"{policy}({list(name)}, {ready_time}, {execution_time})")
    start_time, finish_time = result['start_time'], result['finish_time']
    for N in name:
        print(f"{N} {start_time[N]} {finish_time[N]}")

main()
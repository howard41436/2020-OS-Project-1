all: process scheduler

process: process.c
	gcc process.c utils.c priority.c -o process -O2

scheduler: scheduler.c
	gcc scheduler.c utils.c priority.c policy.c -o scheduler -O2

clean:
	rm process scheduler
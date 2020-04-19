all: process

process: process.c
	gcc process.c utils.c -o process -O2

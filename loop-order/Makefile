SHELL := /bin/bash
CC=gcc
CFLAGS=-g

all: row-major column-major

row-major: row-major.c
	$(CC) $(CFLAGS) -o$@ $<

column-major: column-major.c
	$(CC) $(CFLAGS) -o$@ $<

run: row-major column-major
	time ./row-major > /dev/null
	time ./column-major > /dev/null
	sudo perf record -e cache-misses ./row-major; sudo perf report --stdio > row-major-perf
	sudo perf record -e cache-misses ./column-major; sudo perf report --stdio > column-major-perf

clean: 
	sudo rm row-major column-major row-major-perf column-major-perf perf.data*



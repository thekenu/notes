SHELL := /bin/bash
CC=gcc
CFLAGS=-DCACHELINE_SIZE=$$(getconf LEVEL1_DCACHE_LINESIZE) -pthread -Wall -g

all: has-bounce no-bounce

has-bounce: cache-parallel.c
	$(CC) $(CFLAGS) -o$@ $<

no-bounce: cache-parallel.c
	$(CC) -DDISTINCT_CACHE_LINES $(CFLAGS) -o$@ $<

run: has-bounce no-bounce
	time ./has-bounce > /dev/null
	time ./no-bounce > /dev/null

clean:
	rm has-bounce no-bounce

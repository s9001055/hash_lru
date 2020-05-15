$(CC):=gcc

all:
	$(CC) -Wall -g -o hash_lru.out hash_lru.c

.PHONY:clean
clean:
	rm hash_lru.out

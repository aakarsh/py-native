all: shared heap

shared: unix.c
	gcc -g -fPIC -Wall -Werror -Wextra -pedantic unix.c -shared -o lib/libunix.so

heap: heap.c
	gcc heap.c -o bin/heap

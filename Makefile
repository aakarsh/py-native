all: shared heap

shared: unix.c
	g++ -g -fPIC -Wall -Werror -Wextra -pedantic unix.c -shared -o libunix.so

heap: heap.c
	g++  heap.c -o heap

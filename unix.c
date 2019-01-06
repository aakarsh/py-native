#include <stdio.h>

int multiply(int a , int b)
{
	return a*b;
}

int count_chars(char* s) 
{
	int count = 0;
	while(*s++) count++;
	return count;
}

int main()
{
	printf("hello world\n");
	return 0;
}

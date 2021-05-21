#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS	2

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static const int N	= 10;

struct shared_block {
	int upper;
	int lower;
	int *arr;
};

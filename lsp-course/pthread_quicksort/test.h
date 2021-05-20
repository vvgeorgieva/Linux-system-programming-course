#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static const int N	= 10;
#define NUM_THREADS	2

struct shared_block {
	int upper;
	int lower;
	int *arr;
};

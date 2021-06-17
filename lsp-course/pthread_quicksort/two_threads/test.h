#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS	2
static const int N	= 10;

/* Initial set */
int arr[] = {1, 2, 5, 6, 8, 9, 10, 8, 5, 11};

struct shared_block {
	int upper;
	int lower;
};

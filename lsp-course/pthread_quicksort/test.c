#include "test.h"

void print_arr(int *arr, const int N) {
	int i;
	
	if (arr == NULL) {
		fprintf(stderr, "%s: null int ptr arg found!\n", __func__);
	}

	if (N == 0) {
		fprintf(stderr, "%s: null arg found!\n", __func__);
	}

	for (i = 0; i < N; i++) {
		printf("arr[%d] = %d\n", i, arr[i]);
	}
}

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int *arr, int lower, int upper) {
	int i, j;
	if (arr == NULL) {
		fprintf(stderr, "%s: null int ptr arg found!\n", __func__);
	}

	int pivot = arr[upper];
	i = lower - 1;

	for (j = lower; j <= upper - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[i + 1], &arr[upper]);
	return (i + 1);
}

void *q_sort(void *data_ptr) {
	int pivot;
	pthread_t threads[2];
	struct shared_block *sb = (struct shared_block *) data_ptr;
	struct shared_block l_sb;
	struct shared_block r_sb;	

	if (data_ptr == NULL) {
		fprintf(stderr, "%s: null int ptr arg found!\n", __func__);
	}

	pivot = partition(sb->arr, sb->lower, sb->upper);

	l_sb.lower = sb->lower;
	l_sb.upper = pivot - 1;
	l_sb.arr = sb->arr;

	r_sb.lower = pivot + 1;
	r_sb.upper = sb->upper;
	r_sb.arr = sb->arr;

	/* Create two competing threads */
	threads[0] = pthread_create(&threads[0], NULL, q_sort, &l_sb);
	threads[1] = pthread_create(&threads[1], NULL, q_sort, &r_sb);

	/* Join threads */
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
}

int main() {
	/* Initial set */
	int arr[] =
		{1, 2, 5, 6, 8, 9, 10, 8, 5, 11};

	/* Declare shared_block and allocate memory for the struct */
	struct shared_block *sb = (struct shared_block *)malloc(sizeof(struct shared_block));

	/* Set the initial data set to the newly allocated struct array */
	sb->arr = arr;
	
	/* Set initial values to struct memebers */
	sb->upper = N - 1;
	sb->lower = 0;

	/* Use helper function to print the initial array */
	printf("Unsorted array: \n");
	print_arr(arr, N);

	/* Calling the traditional qsort function */
	q_sort(sb);

	/* Last but not least, use helper function to print the sorted array */
	printf("Sorted array: \n");
	print_arr(sb->arr, N);

	return 0;
}

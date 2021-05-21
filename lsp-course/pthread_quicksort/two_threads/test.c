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
		printf("%d\t", arr[i]);
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

pthread_t thread[NUM_THREADS];

void *q_sort(void *data_ptr) {
	int ret = EXIT_FAILURE;
	int pivot;
	struct shared_block *sb = (struct shared_block *) data_ptr;
	struct shared_block *lb = (struct shared_block *) data_ptr;

	/* Set upper and lower values from the given data_ptr */
	int upper = sb->upper;
	int lower = sb->lower;

	if (lower < upper) {
		/* Find the pivot element */
		pivot = partition(sb->arr, sb->lower, sb->upper);

		/* Use second struct in order to pass it as an arg to the 
		 * thread creation function. Set its values according to the
		 * quick sort algorithm.
		 */

		lb->lower = pivot + 1;
		lb->upper = upper;
		/* Create thread and pass new struct to it along with the qsort function */
		ret = pthread_create(&thread[0], NULL, q_sort, lb);
		if (ret != 0) {
			fprintf(stderr, "%s: Thread creation failed!\n", __func__);
		}

		/* Set new values to the struct */
		lb->lower = lower;
		lb->upper = pivot - 1;

		/* Create thread and pass new struct to it along with the qsort function */
		ret = pthread_create(&thread[1], NULL, q_sort, lb);
		if (ret != 0) {
			fprintf(stderr, "%s: Thread creation failed!\n", __func__);
		}

		/* Join both threads */
		pthread_join(thread[0], NULL);
		pthread_join(thread[1], NULL);
	}

	return 0;
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

	/* Calling the q_sort function */
	q_sort(sb);

	/* Last but not least, use helper function to print the sorted array */
	print_arr(sb->arr, N);

	return 0;
}

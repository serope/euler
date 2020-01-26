/*
 * Project Euler
 * 44.c
 * TODO: Simplify this whole thing
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "euler.h"


typedef struct p44_data_s {
	int64_t* arr;
	int len;
	int index;
	int64_t answer;
} p44_data;

void*	problem44_solve(void* ptr);
#define	IS_NEGATIVE(x) x<0

int total_threads = 8;


int main() {
	/* 
	 * create an array of pentagonal numbers
	 * (10k is sufficient for this problem)
	 */
	int len = 10000;
	int64_t* arr = (int64_t*) calloc(len, sizeof(int64_t));
	for (int n=0; n<len; n++)
		arr[n] = nth_pentagonal_number(n+1);
	
	// set initial answer
	int64_t answer = arr[len-1];
	
	// declare threads
	pthread_t threads[total_threads];
	printf("total_threads \t %d \n", total_threads);
	
	// prepare structs to be passed to multithread function
	p44_data data[total_threads];
	for (int i=0; i<total_threads; i++) {
		data[i].arr	= arr;
		data[i].len		= len;
		data[i].answer	= answer;
		data[i].index 	= i;
	}
	
	// solve
	for (int i=0; i<total_threads; i++) {
		int status = pthread_create(&threads[i], NULL, &problem44_solve, (void*) &data[i]);
		if (status!=0) {
			puts("pthread_create() failed");
			free(arr);
			return 1;
		}
	}
	
	// wait
	for (int i=0; i<total_threads; i++)
		pthread_join(threads[i], NULL);
	
	// find min
	for (int i=0; i<total_threads; i++)
		if (data[i].answer < answer)
			answer = data[i].answer;
	
	// end
	free(arr);
	printf("min: "); print64(answer); printf("\n");
	return 0;
}


/**
 * Solves problem 44, ptr being a pointer to a struct containing:
 *  - an array of pentagonal numbers
 *  - the array's length
 *  - an index from which to start traversing
 *  - an int64 for holding the final answer
 * 
 * @param	ptr		a pointer to p44_data
 * @return			null
 */
void* problem44_solve(void* ptr) {
	/*
	 * unpack data for readability
	 */
	p44_data* data = (p44_data*) ptr;
	int64_t* arr	= data->arr;
	int len			= data->len;
	int index		= data->index;
	
	/*
	 * Add and subtract different pairs on the list.
	 * If both the sum and difference are on the list, and the
	 * difference is the smallest so far, save it.
	 */
	int64_t smallest	= arr[len-1];
	int64_t largest		= arr[len-1];
	
	for (int a=index; a<len-1; a+=total_threads) {
		for (int b=a+1; b<len; b+=1) {
			// sum
			int64_t sum = arr[a]+arr[b];
			if (sum>largest || IS_NEGATIVE(sum))
				break;
				
			// difference
			int64_t dif = arr[b]-arr[a];
			if (IS_NEGATIVE(dif) || dif>largest)
				break;
				
			// compare with smallest and check list
			if (dif < smallest)
				if (arr_bsearch64(arr, len, sum))
					if (arr_bsearch64(arr, len, dif))
						smallest = dif;
		}
	}
	
	// save answer
	data->answer = smallest;
	return NULL;
}

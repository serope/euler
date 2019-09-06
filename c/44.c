/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 44
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "euler.h"


//This function is called in each thread
void* problem44_solve(void* ptr);


//Total threads; adjust as desired (note: the RPi 3B has 4 cores)
int total_threads = 3;


//Data to be passed in each thread
typedef struct problem44_data_s {
	int64_t* list;
	int len;
	int index;
	int64_t answer;
} problem44_data;




int main() {
	/* 
	 * Create a list of pentagonal numbers
	 * (10k is sufficient for this problem)
	 */
	int len = 10000;
	int64_t* list = (int64_t*) calloc(len, sizeof(int64_t));
	for (int n=0; n<len; n++)
		list[n] = nth_pentagonal_number_int64(n+1);
	
	//Set initial answer
	int64_t answer = list[len-1];
	
	//Declare threads
	pthread_t threads[total_threads];
	printf("total_threads \t %d \n", total_threads);
	
	//Prepare structs to be passed to multithread function
	problem44_data data[total_threads];
	for (int i=0; i<total_threads; i++) {
		data[i].list	= list;
		data[i].len		= len;
		data[i].answer	= answer;
		data[i].index 	= i;
	}
	
	//Solve the problem
	for (int i=0; i<total_threads; i++) {
		int status = pthread_create(&threads[i], NULL, &problem44_solve, (void*) &data[i]);
		if (status!=0) {
			puts("pthread_create() failed");
			free(list);
			return 1;
		}
	}
	
	//Wait until each thread terminates
	for (int i=0; i<total_threads; i++)
		pthread_join(threads[i], NULL);
	
	//Find the smallest answer among each thread's results
	for (int i=0; i<total_threads; i++)
		if (data[i].answer < answer)
			answer = data[i].answer;
	
	//End
	free(list);
	printf("smallest: %lld \n", answer);
	return 0;
}






/*
 * Solve problem 44.
 * 
 * The passed value should be a pointer to a struct containing:
 *  - a list of pentagonal numbers
 *  - the list's length
 *  - an index from which to start traversing
 *  - an int64 for holding the final answer
 */
void* problem44_solve(void* ptr) {
	/*
	 * Unpack data
	 */
	problem44_data* data = (problem44_data*) ptr;
	int64_t* list	= data->list;
	int len			= data->len;
	int index		= data->index;
	
	/*
	 * Add and subtract different pairs on the list.
	 * If both the sum and difference are on the list, and the
	 * difference is the smallest so far, save it.
	 */
	int64_t smallest	= list[len-1];
	int64_t largest		= list[len-1];
	
	for (int a=index; a<len-1; a+=total_threads) {
		for (int b=a+1; b<len; b+=1) {
			//Sum
			int64_t sum = list[a]+list[b];
			if (sum>largest || IS_NEGATIVE(sum))
				break;
				
			//Difference
			int64_t dif = list[b]-list[a];
			if (IS_NEGATIVE(dif) || dif>largest)
				break;
				
			//Compare with smallest and check list
			if (dif < smallest)
				if (contains_int64(list, sum, len))
					if (contains_int64(list, dif, len))
						smallest = dif;
		}
	}
	
	//Save answer
	data->answer = smallest;
	return NULL;
}

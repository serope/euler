/*
 * Project Euler
 * 12.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "euler.h"
#include "factor.h"


typedef struct p12_data_s {
	int* list;
	int len;
	int index;
	int returned_n;
	int returned_triangle;
	int total_threads;
} p12_data;


p12_data 	p12_data_new(int* list, int n, int i, int total_threads);
void*		p12_solve(void* ptr);
int			min_result(p12_data* arr, int len);
bool		verify_total_threads(int total_threads, int n);
bool		has_over_500_factors(int x);



int main() {
	// generate triangles (15000 is sufficient)
	int n = 15000;
	int* list = triangle_numbers(n);
	int max = list[n-1];
	
	// total threads OK ?
	int total_threads = 10;
	if (!verify_total_threads(total_threads, n)) {
		free(list);
		return -1;
	}
	
	// prepare multithread data
	p12_data data[total_threads];
	for (int i=0; i<total_threads; i++)
		data[i] = p12_data_new(list, n, i, total_threads);
	
	// declare threads
	pthread_t threads[total_threads];
	printf("total_threads \t %d \n", total_threads);
	
	// solve
	for (int i=0; i<total_threads; i++) {
		bool failed = pthread_create(&threads[i], NULL, &p12_solve, 
															&data[i]);
		if (failed) {
			puts("pthread_create() failed");
			free(list);
			return -1;
		}
	}
	
	// wait
	for (int i=0; i<total_threads; i++)
		pthread_join(threads[i], NULL);
	
	// end
	int answer = min_result(data, total_threads);
	printf("answer           %d \n", answer);
	free(list);
	return 0;
}


/**
 * Returns true if the amount of triangle numbers is evenly divisible
 * by the amount of threads to be used.
 * 
 * @param	total_threads	the amount of threads to be used
 * @param	n				the amount of triangle numbers that were
 * 							generated
 * @return					true or false
 */
bool verify_total_threads(int total_threads, int n) {
	if (n%total_threads != 0) {
		puts("n must be divisible by total_threads");
		printf("n               %d \n", n);
		printf("total_threads   %d \n", total_threads);
		return false;
	}
	return true;
}


/**
 * Creates a new instance of p12_data.
 * 
 * @param	list			an array of triangle numbers
 * @param	n				the array's length
 * @param	i				the index that this data's thread will start
 * 							searching the array from
 * @param	total_threads	the total threads to be used
 * @return					a new instance of p12_data to be passed to
 * 							p12_solve
 */
p12_data p12_data_new(int* list, int n, int i, int total_threads) {
	int max = list[n-1];
	p12_data d;
	d.list				= list;
	d.len				= n;
	d.index				= i;
	d.returned_n		= n;
	d.returned_triangle	= max;
	d.total_threads		= total_threads;
	return d;
}


/**
 * Finds a triangle with over 500 divisors and saves it in the given
 * pointer.
 * 
 * @param	ptr		a pointer to p12_data
 * @return			null
 */
void* p12_solve(void* ptr) {
	// unpack for readability
	p12_data* data 		= (p12_data*) ptr;
	int* list			= data->list;
	int len				= data->len;
	int index			= data->index;
	int total_threads	= data->total_threads;
	
	/*
	 * Go through the list and count the factors of some triangles
	 * (each thread works on its own subset of the list)
	 */
	for (int i=index; i<len; i+=total_threads) {
		// skip if the element isn't at least 500
		int x = list[i];
		if (x < 500)
			continue;
		
		// if this element has over 500 factors, save it and return
		if (has_over_500_factors(x)) {
			data->returned_triangle = x;
			data->returned_n = i+1;
			break;
		}
	}
	
	return NULL;
}


/**
 * Returns the smallest result from the given p12_data array.
 * 
 * @param	arr		an array of type p12_data
 * @param	len		the array's length (equal to total_threads)
 * @return			the smallest result
 */
int min_result(p12_data* arr, int len) {
	int min = arr[0].returned_triangle;
	for (int i=0; i<len; i++) {
		if (arr[i].returned_triangle < min) {
			min = arr[i].returned_triangle;
		}
	}
	return min;
}


/**
 * A faster version of factor.c's factor_count() for problem 12.
 * 
 * @param	x	the number to be factorized
 * @return		true or false
 */
bool has_over_500_factors(int x) {
	// edge case
	if (x==1)
		return 1;
	
	// upper = {x}
	int* upper = malloc(sizeof(int));
	upper[0] = x;
	int upper_len = 1;
	
	// if odd, only check odd factors
	int factor, increment;
	if (x%2==0) {
		factor = 2;
		increment = 1;
	}
	else {
		factor = 3;
		increment = 2;
	}
	
	// factorize
	int total = 0;
	while (factor < arr_min(upper, upper_len)) {
		if (x%factor == 0) {
			total++;
			if (factor*factor != x)
				upper = arr_append(upper, x/factor, &upper_len);
				total++;
			if (total > 500)	// break if 500+
				break;
		}
		factor += increment;
		if (x-factor+total < 501)	// break if no chance of reaching 501
			break;
	}
	
	// end
	free(upper);
	if (total > 500)
		return true;
	return false;
}

/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 12
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "euler.h"

//This function is called in each thread
void* problem12_solve(void* ptr);

//Total threads; adjust as desired (note: the RPi 3B has 4 cores)
int total_threads = 5;

//Data to be passed in each thread
typedef struct problem12_data_s {
	int* list;
	int len;
	int index;
	int returned_n;
	int returned_triangle;
	int returned_factors;
} problem12_data;


int main() {
	//Create a list of triangular numbers (15k is sufficient)
	int* list = NULL;
	int len = 0;
	int n = 1;
	int triangle = 0;
	while (len < 15000) {
		triangle += n;
		n++;
		list = append(list, triangle, &len);
	}
	
	//Get largest triangular number
	int largest_triangle = list[len-1];
	
	//Prepare structs for multithread function
	problem12_data data[total_threads];
	for (int i=0; i<total_threads; i++) {
		problem12_data d;
		d.list				= list;
		d.len				= len;
		d.index				= i;
		d.returned_n		= len;
		d.returned_triangle	= largest_triangle;
		d.returned_factors	= 0;
		
		data[i] = d;
	}
	
	//Declare threads
	pthread_t threads[total_threads];
	printf("total_threads \t %d \n", total_threads);
	
	//Solve problem
	for (int i=0; i<total_threads; i++) {
		int status = pthread_create(&threads[i], NULL, &problem12_solve, (void*) &data[i]);
		if (status!=0) {
			puts("pthread_create() failed");
			free(list);
			return 1;
		}
	}
	
	//Wait for each thread to terminate
	for (int i=0; i<total_threads; i++)
		pthread_join(threads[i], NULL);
	
	//Find the smallest answer among each thread's results
	int answer_triangle = largest_triangle;
	int answer_n;
	int answer_factors;
	for (int i=0; i<total_threads; i++) {
		if (data[i].returned_triangle < answer_triangle) {
			answer_triangle		= data[i].returned_triangle;
			answer_n			= data[i].returned_n;
			answer_factors		= data[i].returned_factors;
		}
	}
	
	//End
	printf("n=%d \t %d has %d factors \n", answer_n, answer_triangle, answer_factors);
	free(list);
	return 0;
}



void* problem12_solve(void* ptr) {
	//Unpack data
	problem12_data* data = (problem12_data*) ptr;
	int* list	= data->list;
	int len		= data->len;
	int index	= data->index;
	
	/*
	 * Go through the list and count the factors of some triangles
	 * (each thread works on its own subset of the list)
	 */
	for (int i=index; i<len; i+=total_threads) {
		//Skip if the element isn't at least 500
		if (list[i] < 500)
			continue;
		
		//Count factors
		int factors = factor_count(list[i]);
		
		//Print if over 300 factors
		if (factors > 300)
			printf("n=%d \t %d has %d factors \n", i+1, list[i], factors);
		
		//If this element has over 500 factors, save it and return
		if (factors > 500) {
			data->returned_triangle	= list[i];
			data->returned_n		= i+1;
			data->returned_factors	= factors;
			break;
		}
	}
	
	return NULL;
}

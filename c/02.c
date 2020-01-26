/*
 * Project Euler
 * 02.c
 */
#include <stdio.h>
#include "vector.h"

vec_t* fibonacci(int n);


int main() {
	// generate Fibonacci sequence (40 is sufficient)
	int n = 40;
	vec_t* seq = fibonacci(n);
	
	// sum until limit
	int sum = 0;
	int limit = 4000000;
	for (int i=0; i < seq->len; i++) {
		int x = vec_get_int(seq, i);
		if (x%2 == 0)
			sum += x;
		if (sum >= limit)
			break;
	}
	
	// end
	vec_print_ints(seq);
	vec_destroy(seq, free);
	printf("%d \n", sum);
	return 0;
}


/**
 * Generates the first n elements of the Fibonacci sequence.
 * 
 * @param 	n 	the amount of Fibonacci terms to generate
 * @return 		the resulting sequence
 */
vec_t* fibonacci(int n) {
	vec_t* seq = vec_new();				// initialize sequence {1 2}
	seq = vec_append_int(seq, 1);
	seq = vec_append_int(seq, 2);
	for (int i=2; i<n; i++) {			// generate
		int a = vec_get_int(seq, i-2);
		int b = vec_get_int(seq, i-1);
		seq = vec_append_int(seq, a+b);
	}
	return seq;
}

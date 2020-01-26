/*
 * Project Euler
 * 39.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"

int* make_problem39_dict(int limit);

int main() {
	// generate
	int limit = 1000;
	int* dict = make_problem39_dict(limit);
	
	// find max pair
	int key = 0;
	int val = 0;
	for (int i=0; i<limit; i++) {
		if (dict[i] > val) {
			key = i;
			val = dict[i];
		}
	}
	
	// end
	printf("p=%d has %d Pythagorean solutions \n", key, val);
	free(dict);
	return 0;
}


/**
 * Creates an array in which each index is a perimeter and each value is
 * the total Pythagorean triplet solutions for that perimeter.
 * e.g. from problem text, dict[120] = 3
 * Note: In a Pythagorean triplet, at least one term is divisibley by 5.
 * 
 * @param	limit	the limit go check up to
 * @return			a heap-allocated array
 */
int* make_problem39_dict(int limit) {
	int* dict = calloc(limit, sizeof(int));
	for (int a=1; a<limit; a++) {
		for (int b=a+1; b<limit; b++) {
			for (int c=b+1; c<limit; c++) {
				int perim = a+b+c;
				if (perim<limit && is_pythagorean_triplet(a, b, c))
					dict[perim]++;
			}
		}
	}
	return dict;
}

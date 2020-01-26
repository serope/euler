/*
 * Project Euler
 * 49.c
 */
#include <stdlib.h>
#include <stdio.h>
#include "prime.h"
#include "euler.h"

bool has_problem49_property(int x, int y);

int main() {
	// sieve up to 4 digits (1-9999)
	int list_len;
	int* list = eratosthenes(9999, &list_len);
	
	// remove non-4-digit terms, along with examples from problem text
	for (int i=0; i<list_len; i++) {
		int p = list[i];
		if (p==1487 || p==4817 || p==8147 || p<1000)
			list[i] = 0;
	}
			
	// solve
	int answer1;
	int answer2;
	int answer3;
	for (int i=0; i<list_len; i++) {
		int x = list[i];
		if (x == 0)
			continue;
		for (int j=i+1; j<list_len; j++) {
			int y = list[j];
			if (y == 0 || !has_problem49_property(x, y))
				continue;
			for (int k=j+1; k<list_len; k++) {
				int z = list[k];
				if (z == 0 || !has_problem49_property(y, z))
					continue;
				else {
					answer1 = x;
					answer2 = y;
					answer3 = z;
					goto nested_break;
				}
			}
		}
	}
	
	// end
	nested_break:
	printf("%d %d %d \n", answer1, answer2, answer3);
	free(list);
	return 0;
}


/**
 * Returns true if two given terms satisfy the requirements in the
 * problem text.
 * 
 * @param	x	a 4-digit prime
 * @param	y	a 4-digit prime
 * @return		true or false
 */
bool has_problem49_property(int x, int y) {
	// can't be equal
	if (x == y)
		return false;
		
	// must have 4 digits
	if (digit_count(x) != 4 || digit_count(y) != 4)
		return false;
	
	// must be permutations of one another
	if (!is_permutation(x, y))
		return false;
		
	// must have a distance which is divisible by 3330
	int d = x-y;
	if (d < 0)
		d *= -1;
	if (d%3330 != 0)
		return false;
	return true;
}


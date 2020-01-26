/*
 * Project Euler
 * binary.c
 */
#include "binary.h"


bin_t* bin_new(int x, int* len_ptr) {
	// determine array len
	int len = 0;
	int y = x;
	while (y > 0) {
		y = y >> 1;
		len++;
	}
	
	// convert
	bin_t* b = calloc(len, sizeof(int));
	int i = len-1;
	y = x;
	while (y > 0) {
		if (y%2 != 0)
			b[i] = 1;
		y = y >> 1;
		i--;
	}
	*len_ptr = len;
	return b;
}


int bin_to_dec(bin_t* b, int len) {
	int x = 0;
	int m = 1;
	for (int i=len-1; i>=0; i--) {
		x += b[i]*m;
		m *= 2;
	}
	return x;
}


void bin_print(bin_t* b, int len) {
	printf("0b");
	for (int i=0; i<len; i++)
		printf("%d", b[i]);
	printf("\n");
}


void bin_free(bin_t* b) {
	free(b);
}

/*
 * Project Euler
 * euler.c
 */
#include "euler.h"


int* triangle_numbers(int n) {
	int* arr = calloc(n, sizeof(int));
	int tri = 0;
	for (int i=0; i<n; i++) {
		tri += i+1;
		arr[i] = tri;
	}
	return arr;
}


int* digits_of(int x) {
	// 1 digit
	if (x <= 9) {
		int* arr = malloc(sizeof(int));
		arr[0] = x;
		return arr;
	}
	
	// count and get divider
	int count = digit_count(x);
	int div = int_pow(10, count-1);
	
	// divide
	int* arr = calloc(count, sizeof(int));
	int i = 0;
	while (div > 0) {
		int digit = x/div - 10*(x/(div*10));
		arr[i] = digit;
		i++;
		div = div/10;
	}
	return arr;
}


int digit_count(int x) {
	if (x<=9)
		return 1;
	else if (x<=99)
		return 2;
	else if (x<=999)
		return 3;
	else if (x<=9999)
		return 4;
	else if (x<=99999)
		return 5;
	else if (x<=999999)
		return 6;
	else if (x<=9999999)
		return 7;
	else if (x<=99999999)
		return 8;
	else if (x<=999999999)
		return 9;
	else if (x<=9999999999)
		return 10;
	else if (x<=99999999999)
		return 11;
	return -1;
}


int int_pow(int x, int y) {
	if (x==1 || y==0)
		return 1;
	int z = x;
	for (int e=1; e<y; e++)
		z *= x;
	return z;
}


int digits_to_int(int* arr, int len) {
	int x = 0;	// returning int
	int m = 1;	// multiplier
	for (int i=len-1; i>=0; i--) {
		x += arr[i]*m;
		m *= 10;
	}
	return x;
}


bool is_palindromic_int(int x) {
	int* arr = digits_of(x);
	int len = digit_count(x);
	bool result = arr_is_palindrome(arr, len);
	free(arr);
	return result;
}


bool is_permutation(int x, int y) {
	int len_x = digit_count(x);
	int len_y = digit_count(y);
	if (len_x != len_y)
		return false;
		
	int* digs_x = digits_of(x);
	int* digs_y = digits_of(y);
	qsort(digs_x, len_x, sizeof(int), __int_cmp);
	qsort(digs_y, len_x, sizeof(int), __int_cmp);
	
	bool result = true;
	for (int i=0; i<len_x; i++) {
		if (digs_x[i] != digs_y[i]) {
			result = false;
			break;
		}
	}
	
	free(digs_x);
	free(digs_y);
	return result;
}


bool is_pythagorean_triplet(int a, int b, int c) {
	if (a<b && b<c && a*a+b*b==c*c)
		return true;
	return false;
}


int64_t nth_pentagonal_number(int n) {
	int64_t p = 3*n;
	p -= 1;
	p *= n;
	return p/2;
}


int factorial(int x) {
	if (x==0 || x==1)
		return 1;
	int a=1;
	for (int b=0; b<x; b++)
		a *= (b+1);
	return a;
}


void print64(int64_t x) {
	printf("%" PRId64 "\n", x);
}


int* natural_numbers(int n) {
	int* arr = calloc(n, sizeof(int));
	for (int i=0; i<n; i++)
		arr[i] = i+1;
	return arr;
}


static int __int_cmp(const void* a_ptr, const void* b_ptr) {
	int a = *((int*) a_ptr);
	int b = *((int*) b_ptr);
	return a-b;
}

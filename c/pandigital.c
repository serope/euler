/*
 * Project Euler
 * pandigital.c
 */
#include "pandigital.h"

static int _ = -1;		// represents an empty element

pand_t* pand_permute_ith(int i, int n) {
	// init
	int* pool = __pand_new_pool(n);
	int* seq = __pand_new_empty(n);
	int seq_len = 0;
	int total_perms = factorial(n);
	int range_size = total_perms/n;
	int range_marker = 0;
	
	/*
	 * perform pandigital generation method described in notes
	 * (https://serope.com/github/euler.html)
	 */
	while (true) {
		// find next row
		int row = 0;
		while (range_marker+range_size < i) {
			row += 1;
			range_marker += range_size;
		}
		
		// determine remaining items
		int remaining_pool_len = 0;
		for (int p=0; p<n; p++)
			if (__pand_exists(pool[p]))
				remaining_pool_len += 1;
		int* remaining_pool = calloc(remaining_pool_len, sizeof(int));
		int r = 0;
		for (int p=0; p<n; p++) {
			if (__pand_exists(pool[p])) {
				remaining_pool[r] = pool[p];
				r += 1;
			}
		}
		
		// transfer appropriate item from remaining pool to seq
		int remaining_pool_index = row;
		seq[seq_len] = remaining_pool[remaining_pool_index];
		seq_len += 1;
		int remove_index = 0;
		while (pool[remove_index] != seq[seq_len-1])
			remove_index += 1;
		pool[remove_index] = _;
		free(remaining_pool);
		
		// break if the seq has 10 items
		if (seq_len == n)
			break;
		
		// otherwise, prepare next pass
		int range_start = range_marker;				//725760 in 1st pass
		int range_end = range_marker + range_size;	//1088640
		range_marker = range_start;
		range_size = (range_end-range_start)/(n-seq_len);
	}
	free(pool);
	return seq;
}


int64_t pand_to_int(pand_t* p, int n) {
	if (n == 1)
		return p[0];
	int64_t x = p[n-1];
	int64_t m = 10;
	for (int i=n-2; i>=0; i--) {
		x += p[i] * m;
		m *= 10;
	}
	return x;
}


bool is_pand(int x) {
	// digits
	int* arr = digits_of(x);
	int arr_len = digit_count(x);
	
	// digit appearances
	int dict_len = arr_len+1;
	bool* dict = calloc(dict_len, sizeof(int));		// digit appearances
	
	// count appearances
	bool result = true;
	for (int i=0; i<arr_len; i++) {
		int dig = arr[i];
		if (dig >= dict_len || dict[dig]) {
			result = false;
			break;
		}
		else
			dict[dig] = true;
	}
	
	// did every digit appear?
	if (result) {
		int start = 0;			// if x is 10 digits, 0-9 must appear
		if (arr_len < 10)
			start = 1;			// if x is <=9 digits, 1-9 must appear
		for (int i=start; i<dict_len; i++) {
			if (!dict[i]) {
				result = false;
				break;
			}
		}
	}
	
	// end
	free(arr);
	free(dict);
	return result;
}


void pand_print(pand_t* p, int n) {
	for (int i=0; i<n; i++)
		printf("%d", p[i]);
	printf("\n");
}


void pand_free(pand_t* p) {
	free(p);
}


static int* __pand_new_pool(int n) {
	int* pool = calloc(n, sizeof(int));
	for (int i=0; i<n; i++) {
		if (n == 10)
			pool[i] = i;
		else
			pool[i] = i+1;
	}
	return pool;
}


static int* __pand_new_empty(int n) {
	int* p = calloc(n, sizeof(int));
	for (int i=0; i<n; i++)
		p[i] = _;
	return p;
}


static bool __pand_exists(int x) {
	return (x != _);
}

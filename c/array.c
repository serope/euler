/*
 * Project Euler
 * array.c
 */
#include "array.h"

int* arr_append(int* arr, int x, int* len_ptr) {
	arr = realloc(arr, sizeof(int) * ( *len_ptr + 1 ) );
	arr[*len_ptr] = x;
	*len_ptr += 1;
	return arr;
}


int arr_min(int* arr, int len) {
	int m = arr[0];
	for (int i=1; i<len; i++)
		if (arr[i] < m)
			m = arr[i];
	return m;
}


int arr_max(int* arr, int len) {
	int m = arr[0];
	for (int i=1; i<len; i++)
		if (arr[i] > m)
			m = arr[i];
	return m;
}


int arr_sum(int* arr, int len) {
	int sum = 0;
	for (int i=0; i<len; i++)
		sum += arr[i];
	return sum;
}


int* arr_shift_left(int* arr, int len) {
	int first = arr[0];
	arr = memcpy(&arr[0], &arr[1], sizeof(int) * len-1);
	arr[len-1] = first;
	return arr;
}


int* arr_shift_right(int* arr, int len) {
	int last = arr[len-1];
	arr = memcpy(&arr[1], &arr[0], sizeof(int) * len-1);
	arr[0] = last;
	return arr;
}


int* arr_merge(int* arr1, int len1, int* arr2, int len2) {
	int* arr3 = calloc(len1 + len2, sizeof(int));
	size_t size1 = sizeof(int) * len1;
	size_t size2 = sizeof(int) * len2;
	memcpy(arr3, arr1, size1);
	memcpy(&arr3[len1], arr2, size2);
	return arr3;
}


int arr_cat_elems(int* arr, int len) {
	int cat = arr[0];
	for (int i=1; i<len; i++) {
		int elem = arr[i];
		for (int j=0; j<digit_count(elem); j++)
			cat *= 10;
		cat += elem;
	}
	return cat;
}


void** arr_filter_repeats(	void**	arr,
							int		len,
							int		(*cmp_fun)(void* x, void* y),
							void*	(*cpy_fun)(void* x),
							int*	len_ptr)
{
	void** unique = calloc(len, sizeof(void*));
	int unique_len = 0;
	for (int i=0; i<len-1; i++) {
		if (cmp_fun(arr[i], arr[i+1]) != 0) {
			unique[unique_len] = cpy_fun(arr[i]);
			unique_len++;
		}
	}
	unique[unique_len] = cpy_fun(arr[len-1]);
	unique_len++;
	*len_ptr = unique_len;
	return unique;
}


void arr_free_full(int** arr, int len) {
	for (int i=0; i<len; i++)
		free(arr[i]);
	free(arr);
}


void arr_print(int* arr, int len) {
	printf("{");
	for (int i=0; i<len; i++) {
		printf("%d", arr[i]);
		if (i < len-1)
			printf(" ");
	}
	printf("}\n");
}


void arr_print_matrix(int** m, int n) {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			int x = m[i][j];
			printf("%d  ", x);
			if (x<10)
				printf(" ");
		}
		printf("\n");
	}
	printf("matrix: %dx%d \n", n, n);
}


bool arr_bsearch(int* arr, int len, int x) {
	return bsearch(&x, arr, len, sizeof(int), __int_cmp);
}


bool arr_bsearch64(int64_t* arr, int len, int64_t x) {
	return bsearch(&x, arr, len, sizeof(int64_t), __int64_cmp);
}


bool arr_is_palindrome(int* arr, int len) {
	int i = 0;
	int j = len-1;
	while (i <= j) {
		if (arr[i] != arr[j])
			return false;
		i++;
		j--;
	}
	return true;
}


static int __int_cmp(const void* a_ptr, const void* b_ptr) {
	int a = *((int*) a_ptr);
	int b = *((int*) b_ptr);
	return a-b;
}


static int __int64_cmp(const void* a_ptr, const void* b_ptr) {
	int64_t a = *((int64_t*) a_ptr);
	int64_t b = *((int64_t*) b_ptr);
	if (a > b)		// don't return a-b, because it (somehow) breaks 45.c
		return 1;
	else if (a < b)
		return -1;
	return 0;
}

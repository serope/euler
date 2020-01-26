/*
 * Project Euler
 * array.h
 * 
 * These are simple convenience functions for arrays (mostly int arrays).
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>	// for memcpy()
#include "euler.h"	// for digit_count()

/**
 * Appends an element to an array, incrementing its length by 1.
 * 
 * @param	arr			the array to be modified
 * @param	x			the element to append
 * @param	len_ptr		a pointer to an integer representing the array's
 * 						length
 * @return				the array, after x has been appended to it
 */
int* arr_append(int* arr, int x, int* len_ptr);


/**
 * Finds the smallest element in an array of integers.
 * 
 * @param	arr		the array to search
 * @param	len		the array's length
 * @return			the array's smallest element
 */
int arr_min(int* arr, int len);


/**
 * Finds the largest element in an array of integers.
 * 
 * @param	arr		the array to search
 * @param	len		the array's length
 * @return			the array's largest element
 */
int arr_max(int* arr, int len);


/**
 * Computes the sum of an array of integers.
 * 
 * @param	arr		the array
 * @param	len		the array's length
 * @return			the sum
 */
int arr_sum(int* arr, int len);


/**
 * Shifts every element 1 space left, pushing the leftmost element to the
 * final position.
 * 
 * @param	arr		the array to modify
 * @param	len		the array's length
 * @return			the array, after it has been modified
 */
int* arr_shift_left(int* arr, int len);


/**
 * Shifts every element 1 space right, pushing the rightmost element to
 * position 0.
 * 
 * @param	arr		the array to modify
 * @param	len		the array's length
 * @return			the array, after it has been modified
 */
int* arr_shift_right(int* arr, int len);


/**
 * Combines two arrays into a new array.
 * 
 * @param	arr1	the first array
 * @param	len1	the first array's length
 * @param	arr2	the second array
 * @param	len2	the second array's length
 * @return			a new, heap-allocated array of length len1+len2
 */
int* arr_merge(int* arr1, int len1, int* arr2, int len2);


/**
 * Concatenates the elements of an int array.
 * 
 * @param	arr		an array
 * @param	len		the array's length
 * @return			an integer
 */
int arr_cat_elems(int* arr, int len);


/**
 * Filters out repeated elements from the input array, creating a new
 * array in the process. The input array may be destroyed afterwards.
 * Note: The input array must be sorted!
 * 
 * @param	arr			a sorted input array
 * @param	len			the input array's length
 * @param	cmp_fun		a comparison function which returns 0 if two
 * 						elements are equal
 * @param	cpy_fun		a copy function for copying an element from one
 * 						array to another
 * @param	len_ptr		a pointer to an integer which takes on the length
 * 						of the output array
 * @return				a heap-allocated array
 */
void** arr_filter_repeats(	void**	arr,
							int		len,
							int		(*cmp_fun)(void* x, void* y),
							void*	(*cpy_fun)(void* x),
							int*	len_ptr
						);


/**
 * Frees the given 2-dimensional int array and its elements.
 * 
 * @param	arr		the array to be freed
 * @param	len		the array's length
 */
void arr_free_full(int** arr, int len);


/**
 * Prints an array of integers.
 * 
 * @param	arr		the array
 * @param	len		the array's length
 */
void arr_print(int* arr, int len);


/**
 * Prints a 2-dimensional array of integers.
 * 
 * @param	m	the matrix to print
 * @param	n	the amount of rows and columns
 */
void arr_print_matrix(int** m, int n);


/**
 * Returns true if x is in the given ordered array. This is a wrapper
 * around bsearch().
 * 
 * @param	arr		the array to search
 * @param	len		the array's length
 * @param	x		the element to search for
 * @return			true or false
 */
bool arr_bsearch(int* arr, int len, int x);


/**
 * Returns true if x is in the given ordered array. This is a wrapper
 * around bsearch().
 * 
 * @param	arr		the array to search
 * @param	len		the array's length
 * @param	x		the 64-bit element to search for
 * @return			true or false
 */
bool arr_bsearch64(int64_t* arr, int len, int64_t x);


/**
 * Returns true if the given array is a palindrome.
 * 
 * @param	arr		the array to check
 * @param	len		the array's length
 */
bool arr_is_palindrome(int* arr, int len);


/**
 * Compares two integers. This is passed to bsearch().
 * 
 * @param	a_ptr	a pointer to an integer
 * @param	b_ptr	a pointer to an integer
 * @return			positive if a>b
 * 					negative if a<b
 * 					zero if a==b
 */
static int __int_cmp(const void* a_ptr, const void* b_ptr);


/**
 * Compares two integers. This is passed to bsearch().
 * 
 * @param	a_ptr	a pointer to an integer
 * @param	b_ptr	a pointer to an integer
 * @return			positive if a>b
 * 					negative if a<b
 * 					zero if a==b
 */
static int __int64_cmp(const void* a_ptr, const void* b_ptr);

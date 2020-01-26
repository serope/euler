/*
 * Project Euler
 * big.h
 * 
 * These are functions for performing bignum arithmetic.
 * TODO: Finish implementing Karatsuba's algorithm.
 */
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h> // for memcpy()
#include "array.h"	// for arr_is_palindrome()
#include "euler.h"	// for digits_of()

/*
 * The big_t type uses a short int array to store digits in reverse
 * order, e.g. 28751 would be {1,5,7,8,2} with a len of 5.
 */
typedef struct big_s {
	short int* arr;
	int len;
} big_t;


/**
 * Creates a new big based on the given stringed integer (ignoring
 * leading zeroes).
 * 
 * @param	str		a stringed integer
 * @return			a new big
 */
big_t* big_new(char* str);


/**
 * Creates a new big from the given unsigned integer.
 * 
 * @param	ui		an unsigned integer
 * @return			a new big
 */
big_t* big_new_ui(unsigned int ui);


/**
 * Performs a+b=c, returning c.
 * To perform a+=b, use big_pluseq().
 * 
 * @param	a	the first big
 * @param	b	the second big
 * @return		the sum, c
 */
big_t* big_add(big_t* a, big_t* b);


/**
 * Performs a+=b.
 * 
 * @param	a_ptr	a pointer to the term to be added to
 * @param	b		the addition value
 */
void big_pluseq(big_t** a_ptr, big_t* b);


/**
 * Performs x+=1.
 * 
 * @param	x_ptr	a pointer to the term to be incremented
 */
void big_incr(big_t** x_ptr);


/**
 * Performs a-b=c, returning c.
 * 
 * @param	a	the first big
 * @param	b	the second big
 * @return		the difference, c
 */
big_t* big_sub(big_t* a, big_t* b);


/**
 * Performs a*b=c via long multiplication, returning c.
 * 
 * @param	a	the base
 * @param	b	the multiplier
 * @return		the product, c
 */
big_t* big_mul_slow(big_t* a, big_t* b);


/**
 * Performs a*b=c via Karatsuba's algorithm, returning c.
 * 
 * @param	a	the base
 * @param	b	the multiplier
 * @return		the product, c
 */
big_t* big_mul(big_t* a, big_t* b);


/**
 * Performs x^2=y, returning y.
 * 
 * @param	x	the base
 * @return		x^2
 */
big_t* big_sq(big_t* x);


/**
 * Performs x^ui=y, returning y.
 * 
 * @param	x	the base
 * @param	ui	the exponent
 * @return		y
 */
big_t* big_pow_ui(big_t* a, unsigned int ui);


/**
 * Creates a new copy of x.
 * 
 * @param	x		the original big
 * @return			a new big
 */
big_t* big_copy(big_t* x);


/**
 * Compares a to b.
 * 
 * @param	a	the first big
 * @param	b	the second big
 * @return		-1 if a<b
 * 				0 if a==b
 * 				1 if a>b
 */
int big_cmp(big_t* a, big_t* b);


/**
 * Returns true if x is a palindrome.
 * 
 * @param	x	the term to check
 * @return		true or false
 */
bool big_is_palindrome(big_t* x);


/**
 * Computes the sum of x's digits.
 * 
 * @param	x	the term to be evaluated
 * @return		the sum
 */
int big_sum_of_digits(big_t* x);


/**
 * Prints x and its length.
 * 
 * @param	x	the term to be printed
 */
void big_print(big_t* x);


/**
 * Creates a copy of x with its digits in reverse order.
 * 
 * @param	x	the big to copy
 * @return		a new big
 */
big_t* big_reverse(big_t* x);


/**
 * Checks if x is a power of 10.
 * 
 * @param	x	the big to check
 * @return		true or false
 */
bool big_is_pow_of_10(big_t* x); //unused


/**
 * Checks if x is zero.
 * 
 * @param	x	the big to check
 * @return		true or false
 */
bool big_is_zero(big_t* x);


/**
 * Resets an existing big to zero.
 * 
 * @param	x	the big to reset
 * @return		the big, after it has been reset
 */
big_t* big_reset(big_t* x);


/**
 * Frees x.
 * 
 * @param	x	the big to be freed
 */
void big_destroy(big_t* x);


/**
 * Appends zeroes to x's internal array.
 * 
 * @param	x			the big to edit
 * @param	target_len	the new length of the array
 * @return				x, after its array has been expanded
 */
static big_t* __big_pad(big_t* x, int target_len);


/**
 * Removes trailing zeroes from x's internal array.
 * e.g. 3240000 -> 324
 * 
 * @param	x	the big to edit
 * @return		x, after its internal array has been shrunk
 */
static big_t* __big_unpad(big_t* x);


/**
 * Returns the longer length between two bigs, or b's length if both
 * lengths are equal.
 * 
 * @param	a	the first big
 * @param	b	the second big
 * @return		the longer length
 */
static int __big_longer_len(big_t* a, big_t* b);


/**
 * Returns the shorter length between two bigs, or b's length if both
 * lengths are equal.
 * 
 * @param	a	the first big
 * @param	b	the second big
 * @return		the shorter length
 */
static int __big_shorter_len(big_t* a, big_t* b);


/**
 * Removes all leading zeros from a stringed integer.
 * e.g. "00034" -> "34"
 * 
 * @param	str		a heap-allocated string
 * @param	len		the string's length
 */
static char* __truncate_left(char* str, int len);


/**
 * Creates a new big with a value of 0.
 *
 * @return		a new bignum
 */
static big_t* __big_new_zero();


/**
 * Locates the index of the first nonzero in a string.
 * e.g. "000075" -> 4
 * 
 * @param	str		a stringed integer
 * @param	len		the string's length
 * @return			the index of the first nonzero, or -1 if the string
 * 					consists entirely of zeroes
 */
static int __find_nonzero(char* str, int len);


/**
 * Converts an array of digits into a string.
 * e.g. {2 5 6 1 0 0} -> "256100"
 * 
 * @param	arr		an array of short ints
 * @param	len		the array's length
 * @return			a heap-allocated string
 */
static char* __arr_to_str(short int* arr, int len);


/**
 * Performs long addition on a list of numbers, wherein the list is a
 * 2-dimensional grid, and every row represents a number's digits.
 * 
 * @param	grid		a 2-dimensional array of short ints
 * @param	rows		the amount of rows
 * @param	cols		the amount of columns
 * @return				a bignum which must be freed via big_destroy()
 */
static big_t* __grid_sum(short int** grid, int rows, int cols);


/**
 * Computes B^m for Karatsuba's algorithm.
 * 
 * @param	x	the first big
 * @param	y	the second big
 * @return		a new big representing B^m
 */
static big_t* __karatsuba_bm(big_t* x, big_t* y);


/**
 * Computes x1 for Karatsuba's algorithm.
 * 
 * @param	x	the term to evaluate
 * @param	bm	the B^m value
 * @return		a new big representing x1
 */
static big_t* __karatsuba_x1(big_t* x, big_t* bm);


/**
 * Computes x0 for Karatsuba's algorithm.
 * 
 * @param	x	the term to evaluate
 * @param	bm	the B^m value
 * @return		a new big representing x0
 */
static big_t* __karatsuba_x0(big_t* x, big_t* bm);


/**
 * Returns the 1st digit of a 2-digit number.
 * 
 * @param	x	the term to evaluate
 * @return		a digit
 */
#define __1st_digit(x) (x - __2nd_digit(x)) / 10


/**
 * Returns the 2nd digit of a 2-digit number.
 * 
 * @param	x	the term to evaluate
 * @return		a digit
 */
#define __2nd_digit(x) x%10

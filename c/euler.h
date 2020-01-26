/*
 * Project Euler
 * euler.h
 * 
 * General-purpose functions for various problems.
 */
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "array.h"


/**
 * Generates the first n triangular numbers.
 * 
 * @param	n	the amount of triangles to generate
 * @return		a heap-allocated array of length n
 */
int* triangle_numbers(int n);


/**
 * Counts how many digits x has.
 * 
 * @param	x	the term to evaluate
 * @return		x's total digits
 */
int digit_count(int x);


/**
 * Computes the factorial of x.
 * 
 * @param	x	the term in evaluate
 * @return		x! = x * (x-1) * (x-2) * ...
 */
int factorial(int x);


/**
 * Returns an unordered array of x's digits. Use digit_count() to get
 * its length.
 * 
 * @param	x	the term to evaluate
 * @return		a heap-allocated array
 */
int* digits_of(int x);


/**
 * Returns x^y.
 * 
 * @param	x	the base
 * @param	y	the exponent
 * @return		x^y
 */
int int_pow(int x, int y);


/**
 * Forms an array of digits into an integer (make sure it fits!).
 * 
 * @param	arr		an array of digits
 * @param	len		the array's length
 * @return			an integer
 */
int digits_to_int(int* arr, int len);


/**
 * Prints a 64-bit integer (I keep forgetting what the printf() formatter
 * is...).
 * 
 * @param	x	a 64-bit integer
 */
void print64(int64_t x);


/**
 * Creates a list of natural numbers from 1 to n.
 * 
 * @param	n	the number to generate up to
 * @return		a heap-allocated array
 */
int* natural_numbers(int n);


/**
 * Checks if two integers are permutations of each other.
 * 
 * @param	x	the first term
 * @param	y	the second term
 * @return		true or false
 */
bool is_permutation(int x, int y);


/**
 * Returns true if a, b, and c form a Pythagorean triplet; that is, if
 * a < b < c and a^2 + b^2 = c^2.
 * 
 * @param	a	the a term
 * @param	b	the b term
 * @param	c	the c term
 * @param		true or false
 */
bool is_pythagorean_triplet(int a, int b, int c);


/**
 * Returns true if x is a palindrome.
 * 
 * @param	x	the term to check
 * @return		true or false
 */
bool is_palindromic_int(int x);


/**
 * Computes the nth pentagonal number.
 * 
 * @param	n	the iteration to compute
 * @return		a 64-bit pentagonal number
 */
int64_t nth_pentagonal_number(int n);


/**
 * Compares two integers. This is passed to qsort().
 * 
 * @param	a_ptr	a pointer to an integer
 * @param	b_ptr	a pointer to an integer
 * @return			positive if a>b
 * 					negative if a<b
 * 					zero if a==b
 */
static int __int_cmp(const void* a_ptr, const void* b_ptr);

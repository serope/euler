/*
 * Project Euler
 * pandigital.h
 * 
 * Functions for pandigital sequences.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "array.h"
#include "euler.h" // for factorial()

typedef int pand_t;

/**
 * Forms the ith permutation of an n-digit pandigital number.
 * If n=10, then the 1st is permutation is 0123456789 and the last is
 * 9876543210, there being a total of n! = 10! = 3.6 million possible
 * combinations.
 * 
 * @param	i		the iteration to permute
 * @param	n		the length of the pandigital
 * @return			a heap-allocated pandigital (int array)
 */
pand_t* pand_permute_ith(int i, int n);


/**
 * Converts a pandigital into an integer.
 * 
 * @param	p		the pandigital to convert
 * @param	n		the pandigital's length
 * @return			an int
 */
int64_t pand_to_int(pand_t* p, int n);


/**
 * Returns true if the given integer is a pandigital number.
 * 
 * @param	n		the term to check
 * @return			true or false
 */
bool is_pand(int x);


/**
 * Prints a pandigital number followed by a newline.
 * 
 * @param	p	the pandigital to print
 * @param	n	the pandigital's length
 */
void pand_print(pand_t* p, int n);


/**
 * Frees a pandigital number.
 * 
 * @param	p	the pandigital to free
 */
void pand_free(pand_t* p);


/**
 * Returns an array of length n which contains every valid digit for
 * an n-digit pandigital.
 * 
 * @param	n	the pandigital's length
 * @return		a heap-allocated array of length n
 */
static int* __pand_new_pool(int n);


/**
 * Returns an empty pandigital of length n. "Empty" in this context
 * means that every element is a designated empty value (-1), not 0,
 * since the latter is a valid digit for 10-digit pandigitals.
 * 
 * @param	n	the pandigital's length
 * @return		a heap-allocated array of length n
 */
static int* __pand_new_empty(int n);


/**
 * Returns true if x is not an empty value (see above function).
 * 
 * @param	x	the digit to check
 * @return		true or false
 */
static bool __pand_exists(int x);

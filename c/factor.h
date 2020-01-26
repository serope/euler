/*
 * Project Euler
 * factor.h
 * 
 * Factorization functions.
 */
#include <stdlib.h>
#include <stdbool.h>
#include "array.h"


/**
 * Finds x's factors through trial division.
 * 
 * @param	x			the term to factorize
 * @param	len_ptr		a pointer to an integer to take on the length
 * 						of the output array
 * @return				an unordered array of x's factors
 */
int* factors_of(int x, int* len_ptr);


/**
 * Counts the amount of x's factors (including 1 and itself).
 * 
 * @param	x	the term to factorize
 * @return		the amount of x's factors
 */
int factor_count(int x);


/**
 * Counts the amount of x's proper divisors (all factors except itself).
 * 
 * @param	x	the term to factorize
 * @return		the amount of x's proper divisors
 */
int	proper_divisor_count(int x);


/**
 * Finds x's proper divisors.
 * 
 * @param	x			the term to factorize
 * @param	len_ptr		a pointer to an integer to take on the length
 * 						of the output array
 * @return				an int array
 */
int* proper_divisors(int x, int* len_ptr);


/*
 * Project Euler.
 * binary.h
 * 
 * Functions for converting between binary and decimal.
 * A binary (bin_t*) is simply an int array consisting of 0s and 1s.
 * TODO: Think of a better way to go about doing this (bit fields?).
 */
#include <stdlib.h>
#include <stdio.h>

typedef int bin_t;

/**
 * Converts a decimal number into a binary sequence (int array).
 * 
 * @param	x			the decimal term to evaluate
 * @param	len_ptr		a pointer to an integer to take on the output
 * 						array's length
 * @return				x's binary form
 */
bin_t* bin_new(int x, int* len_ptr);


/**
 * Converts a binary sequence into a decimal number.
 * 
 * @param	b		the binary sequence to evaluate
 * @param	len		the sequence's length
 * @return			b's decimal form
 */
int bin_to_dec(bin_t* b, int len);


/**
 * Prints a binary sequence.
 * 
 * @param	b		a binary sequence
 * @param	len		the sequence's length
 */
void bin_print(bin_t* b, int len);


/**
 * Frees a binary sequence.
 * 
 * @param	b		the binary sequence to be freed
 */
void bin_free(bin_t* b);

/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * euler_bignum.h
 * 
 * Function and struct prototypes
 **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//Type
struct big_s {
	int* array;
	int len;
};
typedef struct big_s* big;

//New big
big		big_new(char* string);
big		big_new_1_digit(int i);
big		big_new_2_digits(int i);
big		big_new_3_digits(int i);

//Operations
void	big_add(big base, big addition);
void	big_subtract(big base, big subtraction);
void	big_multiply(big base, big multiplier);
void	big_pow(big base, unsigned int exponent);
void	big_copy(big source, big destination);

//Property
bool	big_equals(big a, big b);
int		big_compare(big a, big b);
bool	big_is_palindrome(big b);

//Other
int		big_sum_of_digits(big b);
void	big_print(big b);
big		big_reverse(big b);
bool	big_is_pow_of_10(big b); //unused


//Problem 48
void big_multiply_last_10_digits(big base, big multiplier);
void big_pow_last_10_digits(big base, unsigned int exponent);

//Free
#define BIG_FREE(b)		free(b->array); free(b)

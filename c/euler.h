/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * euler.h
 * 
 * Function prototypes
 **********************************************************************/
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

//Array functions
int*		append(int* set, int x, int* len_ptr);
int64_t*	append_int64(int64_t* set, int64_t x, int* len_ptr);
int			min(int* set, int len);
int64_t		min_int64(int64_t* set, int len);
bool		contains(int* set, int target, int len);
bool		contains_int64(int64_t* set, int64_t target, int len);
void		print_set(int* set, int len);
int*		insert(int* set, int x, int* len_ptr);
int			product_of_list(int* list, int len);

//Digit functions
int*		digits_of(int x);
int			digit_count(int x);
int*		sorted_digits_of(int x);
int			replace_digit(int x, int new_digit, int index);
int			int_pow(int base, int exp); //used in digit functions

//Factor/divisor functions
int64_t*	odd_factors_of(int64_t x);
int			odd_factor_count(int64_t x);
int*	    factors_of(int x);
int     	factor_count(int x);
int*		proper_divisors_of(int x);
int			proper_divisor_count(int x);
int			sum_of_proper_divisors_of(int x);
int			distinct_prime_factor_count(int x, int* primes, int primes_len);

//Sequence functions
int*		eratosthenes(int limit);
int			eratosthenes_count(int limit);
int			nth_triangular_number(int n);
int64_t		nth_pentagonal_number_int64(int n);
int64_t		nth_triangular_number_int64(int n);
int64_t		nth_hexagonal_number_int64(int n);
int			factorial(int x);
int*		rotations_of(int x);
int*		truncated_stages(int x);
int			total_truncated_stages(int x);


//Pandigital functions
int*		nth_permutation_of_pandigital(int n, int length);
void		print_pandigital(int* pandigital, int len);

//Property functions
bool		is_prime(int x);
bool		is_prime_int64(int64_t x);
bool		is_palindromic_int(int x);
bool		is_palindromic_array(int* x, int len);
bool		is_pythagorean_triplet(int a, int b, int c);
bool		is_abundant(int x);
bool		is_pandigital_1_to_9(int64_t x);
bool		is_permutation(int x, int y);
bool		is_equal_array(int* set1, int len1, int* set2, int len2);


//Macro functions
#define		IS_EVEN(x)			x%2==0
#define		IS_ODD(x)			x%2!=0
#define		IS_DIVISIBLE(x,d)	x%d==0
#define		IS_NEGATIVE(x)		x<0
#define		NOT_DIVISIBLE(x,d)	x%d!=0
#define		CHAR_TO_INT(c)		c-48
#define		INT_TO_CHAR(d)		d+48
#define		STRING_TO_INT(str)	atoi(str)

//Misc. functions
int64_t		string_to_int64(char* str);
int         final_digit_of(int64_t x);

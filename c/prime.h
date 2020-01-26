/*
 * Project Euler
 * prime.h
 * 
 * Functions for generating primes and verifying primality.
 */
#include <math.h>
#include "array.h"
#include "euler.h"

/**
 * Generates an array of prime numbers from 2 to n.
 * 
 * @param	n			the limit to sieve up to
 * @param	len_ptr		a pointer to an int which takes on the length
 * 						of the output array
 * @return				a heap-allocated array
 */
int* eratosthenes(int n, int* len_ptr);


/**
 * Returns true if x is prime via trial divison, utilizing an array of
 * primes sieved up to at least sqrt(x).
 * 
 * @param	x			the term to test
 * @param	primes		an array of primes
 * @param	primes_len	the array's length
 * @return				true or false
 * @see					https://en.wikipedia.org/wiki/Primality_test
 */
bool is_prime_trial(int x, int* primes, int primes_len);


/**
 * Returns true if x is prime via trial divison, utilizing an array of
 * primes sieved up to at least sqrt(x).
 * 
 * @param	x			the term to test
 * @param	primes		an array of primes
 * @param	primes_len	the array's length
 * @return				true or false
 * @see					https://en.wikipedia.org/wiki/Primality_test
 */
bool is_prime_trial64(int64_t x, int* primes, int primes_len);

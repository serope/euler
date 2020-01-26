/**
 * Project Euler
 * vector.h
 * 
 * This is a generic vector for some Project Euler problems.
 */
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // for memcpy()

typedef void** vec_arr;
typedef struct vec_s {
	vec_arr arr;
	int cap;
	int len;
} vec_t;


/**
 * Creates a new vector, which should later be destroyed with 
 * vec_destroy().
 * 
 * @return	an empty vector
 */
vec_t* vec_new();


/**
 * Appends x to a vector. The element is copied into the vector, so the
 * original may be freed immediately after.
 * 
 * @param	v	the vector
 * @param	x	the element to be appended
 * @return		the vector
 */
vec_t* vec_append(vec_t* v, void* x);


/**
 * Appends an integer (or character) to a vector.
 * 
 * @param	v	the vector
 * @param	d	the value to be appended
 * @return		the vector
 */
vec_t* vec_append_int(vec_t* v, int d);


/**
 * Removes the element at position i, shifting everything else leftwards.
 * The element is freed using the given freeing function, or stdlib
 * free() if none is given.
 * 
 * @param	v			the vector
 * @param	i			the element's position
 * @param	free_fun	the freeing function to be called on the element
 * @return				the vector
 */
vec_t* vec_remove(vec_t* v, int i, void (*free_fun)(void* x));


/**
 * Replaces the element at position i with the vector's final element.
 * This shouldn't be used in cases where the elements' order matters.
 * 
 * @param	v			the vector
 * @param	i			the element's position
 * @param	free_fun	the freeing function to be called on the element
 * @return				the vector
 */
vec_t* vec_remove_fast(vec_t* v, int i, void (*free_fun)(void* x));


/**
 * Appends one vector to another.
 * 
 * @param	v	the base vector
 * @param	w	the vector to be appended to v
 * @return		the base vector, after w has been appended to it
 */
vec_t* vec_append_vec(vec_t* v, vec_t* w);


/**
 * Returns the element at position i.
 * 
 * @param	v	the vector
 * @param	i	the position where the element resides
 * @return		the element
 */
void* vec_get(vec_t* v, int i);


/**
 * Returns an integer at position i.
 * 
 * @param	v	the vector
 * @param	i	the position where the integer resides
 * @return		the integer
 */
int vec_get_int(vec_t* v, int i);



/**
 * Prints a vector by calling print_fun on every element.
 * 
 * @param	v			the vector
 * @param	print_fun	the printing function
 */
void vec_print(vec_t* v, void (*print_fun)(void* x));


/**
 * Prints a vector of integers.
 * 
 * @param	v	the vector
 */
void vec_print_ints(vec_t* v);


/**
 * Prints a string (vector of characters).
 * 
 * @param	v	the vector
 */
void vec_print_string(vec_t* v);


/**
 * Computes the sum of a vector of integers.
 * 
 * @param	v	the vector
 */
int vec_int_sum(vec_t* v);


/**
 * Destroys a vector after applying the given freeing function, or
 * stdlib free() if none is given, to every element.
 * 
 * @param	v			the vector to be destroyed
 * @param	free_fun	the freeing function to be called on every
 * 						element
 */
void vec_destroy(vec_t* v, void (*free_fun)(void* x));


/**
 * Grows or shrinks a vector's internal array if needed. This is called
 * from every function that adds or removes elements.
 * 
 * @param	v	the vector
 * @return		the vector, after it has been resized
 */
static vec_t* __vec_resize(vec_t* v);

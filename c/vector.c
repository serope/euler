/*
 * Project Euler
 * vector.c
 */
#include "vector.h"


vec_t* vec_new() {
	vec_t* v = malloc(sizeof(vec_t));
	v->cap = 2;
	v->arr = calloc(v->cap, sizeof(vec_arr));
	v->len = 0;
	return v;
}


vec_t* vec_append(vec_t* v, void* x) {
	int i = v->len;
	v->arr[i] = malloc(sizeof(void*));
	memcpy(v->arr[i], x, sizeof(void*));
	v->len += 1;
	return __vec_resize(v);
}


vec_t* vec_append_int(vec_t* v, int d) {
	int* ptr = malloc(sizeof(int));
	ptr[0] = d;
	v = vec_append(v, ptr);
	free(ptr);
	return v;
}


vec_t* vec_remove(vec_t* v, int i, void (*free_fun)(void* x)) {
	if (!free_fun)										// free
		free_fun = free;
	free_fun(v->arr[i]);
	for (int j=i; j < v->len - 1; j++)					// shift
		memcpy(v->arr[j], v->arr[j+1], sizeof(void*));
	v->len -= 1;
	return __vec_resize(v);
}


vec_t* vec_remove_fast(vec_t* v, int i, void (*free_fun)(void* x)) {
	if (!free_fun)				// free
		free_fun = free;
	free_fun(v->arr[i]);
	int final = v->len - 1;		// move
	v->arr[i] = v->arr[final];
	v->len -= 1;
	return __vec_resize(v);
}


vec_t* vec_append_vec(vec_t* v, vec_t* w) {
	for (int i=0; i < w->len; i++)
		v = vec_append(v, vec_get(w, i));
	return v;
}


void* vec_get(vec_t* v, int i) {
	return v->arr[i];
}


int vec_get_int(vec_t* v, int i) {
	int* x = vec_get(v, i);
	return *x;
}


void vec_print(vec_t* v, void (*print_fun)(void* x)) {
	printf("{");
	for (int i=0; i < v->len; i++) {
		print_fun(v->arr[i]);
		if (i < v->len-1)
			printf(" ");
	}
	printf("} \n");
}


void vec_print_ints(vec_t* v) {
	printf("{");
	for (int i=0; i < v->len; i++) {
		int x = *((int*) v->arr[i]);
		printf("%d", x);
		if (i < v->len-1)
			printf(" ");
	}
	printf("} \n");
}


void vec_print_string(vec_t* v) {
	for (int i=0; i < v->len; i++) {
		char c = *((int*) v->arr[i]);
		printf("%c", c);
	}
	printf("\n");
}


int vec_int_sum(vec_t* v) {
	int sum = 0;
	for (int i=0; i < v->len; i++) {
		int x = *((int*) v->arr[i]);
		sum += x;
	}
	return sum;
}


void vec_destroy(vec_t* v, void (*free_fun)(void* x)) {
	if (!free_fun)
		free_fun = free;
	for (int i=0; i < v->len; i++)
		free_fun(v->arr[i]);
	free(v->arr);
	free(v);
}


static vec_t* __vec_resize(vec_t* v) {
	if (v->len < v->cap/2)						// shrink
		v-> cap /= 2;
	else if (v->len == v->cap)					// grow
		v->cap *= 2;
	size_t new_size = v->cap * sizeof(vec_arr);
	v->arr = realloc(v->arr, new_size);
	return v;
}

/*
 * Project Euler
 * 24.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"
#include "pandigital.h"

int main() {
	int i = 1000000;
	int n = 10;
	pand_t* p = pand_permute_ith(i, n);
	pand_print(p, n);
	pand_free(p);
	return 0;
}

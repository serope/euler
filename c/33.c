/*
 * Project Euler
 * 33.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct frac_s {
	int top;
	int bottom;
} frac_t;

frac_t frac_new(int top, int bottom);
frac_t frac_reduce(frac_t f);
frac_t frac_mul(frac_t f1, frac_t f2);
bool frac_equal(frac_t f1, frac_t f2);
bool frac_has_problem33_property(frac_t f);
void frac_print(frac_t f);


int main() {
	// init
	frac_t* arr = NULL;
	int arr_len = 0;
	
	// test every 2-digit fraction
	for (int top=10; top<=99; top++) {
		for (int bottom=top+1; bottom<=99; bottom++) {
			if (top%10 == 0)	// skip as suggested in problem text
				continue;
			frac_t f = frac_new(top, bottom);
			if (frac_has_problem33_property(f)) {
				frac_print(f);
				arr = realloc(arr, sizeof(frac_t) * (arr_len + 1));
				arr[arr_len] = f;
				arr_len++;
			}
		}
	}
	
	// product
	frac_t p = frac_new(1, 1);
	for (int i=0; i<arr_len; i++) {
		frac_t q = frac_mul(p, arr[i]);
		p = q;
	}
	
	// end
	printf("%d \n", p.bottom);
	free(arr);
	return 0;
}


/**
 * Creates a new fraction.
 * 
 * @param	top			numerator
 * @param	bottom		denominator
 * @return				a new fraction struct
 */
frac_t frac_new(int top, int bottom) {
	frac_t f;
	f.top = top;
	f.bottom = bottom;
	return f;
}


/**
 * Returns a new fraction which is f reduced.
 * 
 * @param	f		the fraction to reduce
 * @return			a new fraction
 */
frac_t frac_reduce(frac_t f) {
	int t = f.top;
	int b = f.bottom;
	int factor = 2;
	while (factor<=99) {
		if ((t%factor==0) && (b%factor==0)) {
			t = t/factor;
			b = b/factor;
			factor = 2;
		}
		else
			factor += 1;
	}
	return frac_new(t, b);
}


/**
 * Returns true if both fractions reduce to equal values.
 * 
 * @param	f1		a fraction
 * @param	f2		another fraction
 * @return			true or false
 */
bool frac_equal(frac_t f1, frac_t f2) {
	frac_t r1 = frac_reduce(f1);
	frac_t r2 = frac_reduce(f2);
	if (r1.top==r2.top && r1.bottom==r2.bottom)
		return true;
	return false;
}

/**
 * Returns a new, reduced fraction which is a product of two fractions.
 * 
 * @param	f1		a fraction
 * @param	f2		another fraction
 * @return			f1*f2
 */
frac_t frac_mul(frac_t f1, frac_t f2) {
	frac_t prod = frac_new(f1.top*f2.top, f1.bottom*f2.bottom);
	return frac_reduce(prod);
}


/**
 * Returns true if the same digit exists in both the top and bottom and
 * removing both instances of it results in a fraction that is
 * is equal to the original.
 * 
 * @param	f		the fraction to test
 * @return			true or false
 */
bool frac_has_problem33_property(frac_t f) {
	// digits
	int t_1st = f.top/10;
	int t_2nd = f.top - 10*t_1st;
	int b_1st = f.bottom/10;
	int b_2nd = f.bottom - 10*b_1st;
	
	// reduce and compare
	// scenario A: top 1st matches bottom 1st
	if (t_1st==b_1st) {
		frac_t g = frac_new(t_2nd, b_2nd);
		if (frac_equal(f, g)) {
			return true;
		}
	}
	// scenario B: top 1st matches bottom 2nd
	else if (t_1st==b_2nd) {
		frac_t g = frac_new(t_2nd, b_1st);
		if (frac_equal(f, g)) {
			return true;
		}
	}
	// scenario C: top 2nd matches bottom 2nd
	else if (t_2nd==b_2nd) {
		frac_t g = frac_new(t_1st, b_1st);;
		if (frac_equal(f, g)) {
			return true;
		}
	}
	// scenario D: top 2nd matches bottom 1st
	else if (t_2nd==b_1st) {
		frac_t g = frac_new(t_1st, b_2nd);
		if (frac_equal(f, g)) {
			return true;
		}
	}
	return false;
}


/**
 * Prints a fraction followed by a newline.
 * 
 * @param	f		the fraction to print
 */
void frac_print(frac_t f) {
	printf("%d/%d \n", f.top, f.bottom);
}

/*
 * Project Euler
 * big.c
 */
#include "big.h"


big_t* big_new(char* str) {
	// find first nonzero in string
	int len = strlen(str);
	int j = __find_nonzero(str, len);
	if (j == -1) {
		return __big_new_zero();
	}
	
	// init
	big_t* x = malloc(sizeof(big_t));
	x->arr = calloc(len, sizeof(short int));
	x->len = len - j;
	
	// copy str into arr backwards
	int k = 0;
	for (int i=len-1; i>=j; i--) {
		x->arr[k] = (short int) str[i]-48;
		k++;
	}
	return x;
}


big_t* big_new_ui(unsigned int ui) {
	// init
	big_t* x = malloc(sizeof(big_t));
	
	// get digits
	int* digits = digits_of(ui);
	int digits_len = digit_count(ui);
	
	// copy digits into arr backwards
	x->arr = calloc(digits_len, sizeof(short int));
	int j = digits_len-1;
	for (int i=0; i<digits_len; i++) {
		x->arr[j] = (short int) digits[i];
		j--;
	}
	
	// end
	free(digits);
	x->len = digits_len;
	return x;
}


big_t* big_reset(big_t* x) {
	x->arr = realloc(x->arr, sizeof(short int));
	x->arr[0] = 0;
	x->len = 1;
	return x;
}


big_t* big_sub(big_t* a, big_t* b) {
	// edge cases
	int cmp = big_cmp(a, b);
	if (cmp < 0) {
		printf("\tbig_sub() failed: b > a \n");
		printf("\ta: "); big_print(a);
		printf("\tb: "); big_print(b);
		return NULL;
	}
	else if (cmp == 0)
		return big_new("0");
	else if (big_is_zero(b))
		return big_copy(a);
	
	// create diff
	big_t* c = big_copy(a);
	
	// pad
	int longest = __big_longer_len(c, b);
	c = __big_pad(c, longest+1);
	b = __big_pad(b, longest+1);
	
	// paper subtraction
	for (int i=0; i < b->len; i++) {
		c->arr[i] -= b->arr[i];
		if (c->arr[i] < 0) {
			c->arr[i] += 10;
			c->arr[i+1] -= 1;
		}
	}
		
	// unpad
	b = __big_unpad(b);
	c = __big_unpad(c);
	
	// end
	return c;
}


big_t* big_copy(big_t* x) {
	big_t* y = big_new("0");
	size_t arr_size = sizeof(short int) * x->len;
	y->arr = realloc(y->arr, arr_size);
	y->arr = memcpy(y->arr, x->arr, arr_size);
	y->len = x->len;
	return y;
}


void big_print(big_t* x) {
	for (int i=x->len-1; i>=0; i--)
		printf("%i", x->arr[i]);
	printf(" (len %i) \n", x->len);
}


big_t* big_mul_slow(big_t* a, big_t* b) {
	// a*0 or 0*b
	if (big_is_zero(a) || big_is_zero(b))
		return big_new("0");
	
	// assign larger as x
	big_t* x = a;
	big_t* y = b;
	if (big_cmp(a, b) < 0) {
		x = b;
		y = a;
	}
	
	// prepare numbers to be added (below multiplication line)
	int adder_len = x->len + y->len;		// the length of one adder
	int adders_len = y->len;				// the amount of adders
	short int** adders = calloc(adders_len, sizeof(short int*));
	for (int i=0; i<adders_len; i++)
		adders[i] = calloc(adder_len, sizeof(short int));
	
	// paper multiplication
	int adder_i;								// current adder's index
	for (int j=0; j < y->len; j++) {			// current y digit
		adder_i = adder_len - 1 - j;
		for (int i=0; i < x->len; i++) {		// current x digit
			int m = x->arr[i] * y->arr[j];
			adders[j][adder_i] += m;
			m = adders[j][adder_i];
			if (m >= 10) {
				adders[j][adder_i-1] = __1st_digit(m);
				adders[j][adder_i] = __2nd_digit(m);
			}
			adder_i--;
		}
	}
	
	// paper addition
	big_t* sum = __grid_sum(adders, adders_len, adder_len);
	
	// end
	for (int i=0; i<adders_len; i++)
		free(adders[i]);
	free(adders);
	return sum;
}


big_t* big_mul(big_t* x, big_t* y) {
	// Karatsuba's multiplication algorithm
	// B^m
	big_t* bm = __karatsuba_bm(x, y);
	
	// x1 and y1
	big_t* x1 = __karatsuba_x1(x, bm);
	big_t* y1 = __karatsuba_x1(y, bm);
	
	// x0 and y0
	big_t* x0 = __karatsuba_x0(x, bm);
	big_t* y0 = __karatsuba_x0(y, bm);
	
	// z2 = x1*y1
	big_t* z2 = big_mul_slow(x1, y1);
	
	// z1 = x1*y0 + x0*y1
	//    = za    + zb
	big_t* za = big_mul_slow(x1, y0);
	big_t* zb = big_mul_slow(x0, y1);
	big_t* z1 = big_add(za, zb);
	
	// z0 = x0*y0
	big_t* z0 = big_mul_slow(x0, y0);
	
	// result = z2*(bm^2) + z1*bm + z0
	//        = ra        + rb    + z0
	big_t* bm2		= big_sq(bm);
	big_t* ra		= big_mul_slow(z2, bm2);
	big_t* rb		= big_mul_slow(z1, bm);
	big_t* result	= big_add(ra, rb);
	big_pluseq(&result, z0);
	
	// end
	big_destroy(bm);
	big_destroy(x1);
	big_destroy(y1);
	big_destroy(x0);
	big_destroy(y0);
	big_destroy(z2);
	big_destroy(za);
	big_destroy(zb);
	big_destroy(z1);
	big_destroy(z0);
	big_destroy(bm2);
	big_destroy(ra);
	big_destroy(rb);
	return result;
}


big_t* big_sq(big_t* x) {
	big_t* s = big_copy(x);
	big_t* y = big_mul_slow(x, s);
	big_destroy(s);
	return y;
}


big_t* big_add(big_t* a, big_t* b) {
	// zero check
	if (big_is_zero(a))
		return big_copy(b);
	else if (big_is_zero(b))
		return big_copy(a);
	
	// create sum
	big_t* c = big_copy(a);
	
	// pad
	int longest = __big_longer_len(c, b);
	c = __big_pad(c, longest+1);
	b = __big_pad(b, longest+1);
	
	// paper addition
	for (int i=0; i < c->len-1; i++) {
		c->arr[i] += b->arr[i];
		if (c->arr[i] >= 10) {
			c->arr[i] -= 10;
			c->arr[i+1] += 1;
		}
	}
		
	// unpad
	b = __big_unpad(b);
	c = __big_unpad(c);
	return c;
}


void big_pluseq(big_t** a_ptr, big_t* b) {
	big_t* c = big_add(*a_ptr, b);
	big_destroy(*a_ptr);
	*a_ptr = big_copy(c);
	big_destroy(c);
}


void big_incr(big_t** x_ptr) {
	big_t* one = big_new("1");
	big_pluseq(x_ptr, one);
	big_destroy(one);
}


big_t* big_pow_ui(big_t* x, unsigned int ui) {
	// edge cases
	if (ui == 0)
		return big_new("1");
	else if (ui == 1)
		return big_copy(x);
	else if (big_is_zero(x))
		return big_new("0");
	
	// x^ui = y
	big_t* y = big_copy(x);
	for (int p=0; p<ui-1; p++) {
		big_t* m = big_mul_slow(y, x);
		big_destroy(y);
		y = big_copy(m);
		big_destroy(m);
	}
	return y;
}


int big_sum_of_digits(big_t* x) {
	int sum = 0;
	for (int i=0; i < x->len; i++)
		sum += x->arr[i];
	return sum;
}


int big_cmp(big_t* a, big_t* b) {
	if (a->len > b->len)
		return 1;
	else if (a->len < b->len)
		return -1;
	for (int i=a->len-1; i>=0; i--) {
		if (a->arr[i] > b->arr[i])
			return 1;
		else if (a->arr[i] < b->arr[i])
			return -1;
	}
	return 0;
}


bool big_is_pow_of_10(big_t* b) {
	if (b->len < 2)
		return false;
	
	int first_digit = b->arr[0];
	int final_digit = b->arr[b->len-1];
	
	if (first_digit!=1 || final_digit!=0)
		return false;
	
	for (int i=1; i<b->len; i++)
		if (b->arr[i]!=0)
			return false;
	
	return true;
}


bool big_is_zero(big_t* x) {
	return x->arr[0]==0 && x->len==1;
}


bool big_is_palindrome(big_t* x) {
	return arr_is_palindrome((int*) x->arr, x->len);
}


big_t* big_reverse(big_t* x) {
	big_t* r = big_copy(x);
	int i = 0;
	int j = r->len-1;
	short int tmp;
	while (i < j) {
		tmp = r->arr[i];
		r->arr[i] = r->arr[j];
		r->arr[j] = tmp;
		i++;
		j--;
	}
	return r;
}


void big_destroy(big_t* x) {
	free(x->arr);
	free(x);
}


static big_t* __big_new_zero() {
	big_t* x = malloc(sizeof(big_t));
	x->arr = malloc(sizeof(short int));
	x->arr[0] = 0;
	x->len = 1;
	return x;
}


static big_t* __big_pad(big_t* x, int target_len) {
	size_t new_size = sizeof(short int) * target_len;
	x->arr = realloc(x->arr, new_size);
	while (x->len != target_len) {
		x->arr[x->len] = 0;
		x->len += 1;
	}
	return x;
}


static big_t* __big_unpad(big_t* x) {
	int i = -1;									// find first nonzero
	for (int j=x->len-1; j>=0; j--) {
		if (x->arr[j] != 0) {
			i = j+1;
			break;
		}
	}
	if (i == -1)								// x is zero
		return x;
	size_t new_size = sizeof(short int) * i;	// unpad
	x->arr = realloc(x->arr, new_size);
	x->len = i;
	return x;
}


static int __big_longer_len(big_t* a, big_t* b) {
	if (a->len > b->len)
		return a->len;
	return b->len;
}


static int __big_shorter_len(big_t* a, big_t* b) {
	if (a->len < b->len)
		return a->len;
	return b->len;
}


static int __find_nonzero(char* str, int len) {
	int j = -1;
	for (int i=0; i<len; i++) {
		if (str[i] == '0')
			continue;
		else {
			j = i;
			break;
		}
	}
	return j;
}


static char* __arr_to_str(short int* arr, int len) {
	char* str = calloc(len+1, sizeof(char));
	for (int i=0; i<len; i++)
		str[i] = arr[i] + 48;
	return str;
}


static big_t* __grid_sum(short int** grid, int rows, int cols) {
	big_t* sum = big_new("0");
	for (int i=0; i<rows; i++) {
		char* str = __arr_to_str(grid[i], cols);
		big_t* add = big_new(str);
		big_pluseq(&sum, add);
		free(str);
		big_destroy(add);
	}
	return sum;
}


static big_t* __karatsuba_bm(big_t* x, big_t* y) {
	int bm_len = __big_shorter_len(x, y);
	char* bm_str = calloc(bm_len+1, sizeof(char));
	bm_str[0] = '1';
	for (int i=1; i<bm_len; i++)
		bm_str[i] = '0';
	big_t* bm = big_new(bm_str);
	free(bm_str);
	return bm;
}


static big_t* __karatsuba_x1(big_t* x, big_t* bm) {
	int x1_len = x->len - bm->len + 1;
	char* x1_str = calloc(x1_len+1, sizeof(char));
	int i = 0;
	int j = x->len - 1;
	while (i != x1_len) {
		x1_str[i] = x->arr[j] + 48; // int to char
		i++;
		j--;
	}
	big_t* x1 = big_new(x1_str);
	free(x1_str);
	return x1;
}


static big_t* __karatsuba_x0(big_t* x, big_t* bm) {
	int x0_len = bm->len - 1;
	char* x0_str = calloc(x0_len+1, sizeof(char));
	int i = 0;
	int j = x0_len - 1;
	while (i != x0_len) {
		x0_str[i] = x->arr[j] + 48; // int to char
		i++;
		j--;
	}
	big_t* x0 = big_new(x0_str);
	free(x0_str);
	return x0;
}

/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * euler.c
 * 
 * Functions definitions
 **********************************************************************/
#include "euler.h"
#include "euler_binary.h"

/* Array functions */
int* append(int* set, int x, int* len_ptr) {
	int len = *len_ptr;
	
	if (set==NULL || len==0) {
		set = (int*) malloc(sizeof(int));
		set[0] = x;
		*len_ptr += 1;
		return set;
	}
	
	set = (int*) realloc(set, sizeof(int)*(len+1));
	set[len] = x;
	*len_ptr += 1;
	return set;
}

int min(int* set, int len) {
	if (len==0)
		return 0;
	
	int x = set[0];
	
	for (int i=0; i<len; i++)
		if (set[i]<x)
			x = set[i];
	
	return x;
}

int64_t* append_int64(int64_t* set, int64_t x, int* len_ptr) {
	int len = *len_ptr;
	
	if (set==NULL || len==0) {
		set = (int64_t*) malloc(sizeof(int64_t));
		set[0] = x;
		*len_ptr += 1;
		return set;
	}
	
	set = (int64_t*) realloc(set, sizeof(int64_t)*(len+1));
	set[len] = x;
	*len_ptr += 1;
	return set;
}






int64_t min_int64(int64_t* set, int len) {
	int64_t x = set[0];
	
	for (int i=0; i<len; i++)
		if (set[i]<x)
			x = set[i];
	
	return x;
}



bool contains(int* set, int target, int len) {
	//1. Return false if the list is empty
	if (set==NULL || len==0)
		return false;
		
	//2. Set the borders and halfway point for the binary search
	int left = 0;
	int right = len-1;
	int halfway = len/2;
	
	//3. Return if the target is the first or last item
	if (set[left]==target || set[right]==target)
		return true;
	
	//4. Otherwise, proceed with the binary search
	while (true) {
		if (target < set[halfway])
			right = halfway;
		
		else if (target > set[halfway])
			left = halfway;
		
		else if (target==set[halfway])
			return true;
		
		halfway = (right-left)/2 + left;
		
		if (halfway==left || halfway==right)
			break;
	}
	
	//5. Return false if the target wasn't found
	return false;
}



bool contains_int64(int64_t* set, int64_t target, int len) {
	//1. Return false if the list is empty
	if (set==NULL || len==0)
		return false;
		
	//2. Set the borders and halfway point for the binary search
	int left = 0;
	int right = len-1;
	int halfway = len/2;
	
	//3. Return if the target is the first or last item
	if (set[left]==target || set[right]==target)
		return true;
	
	//4. Otherwise, proceed with the binary search
	while (true) {
		if (target < set[halfway])
			right = halfway;
		
		else if (target > set[halfway])
			left = halfway;
		
		else if (target==set[halfway])
			return true;
		
		halfway = (right-left)/2 + left;
		
		if (halfway==left || halfway==right)
			break;
	}
	
	//5. Return false if the target wasn't found
	return false;
}





void print_set(int* set, int len) {
	if (set==NULL || len==0) {
		puts("{}");
		return;
	}
	
	printf("{");
	for (int i=0; i<len; i++)
		printf("%d ", set[i]);
	printf("\b} (len: %d) \n", len);
}





int* insert(int* set, int x, int* len_ptr) {
	/*******************************************************************
	 * 1. Insert 'x' if the set is empty or has only 1 item
	 ******************************************************************/
	int len = *len_ptr;
	
	if (set==NULL || len==0) {
		set = (int*) malloc(sizeof(int));
		set[0] = x;
		*len_ptr = 1;
		return set;
	}


	/*******************************************************************
	 * 2. If possible, insert 'x' at the beginning or end
	 ******************************************************************/
	//Beginning
	if (x <= set[0]) {
		set = (int*) realloc(set, sizeof(int) * (len+1));
		
		for (int i=len; i>0; i--)
			set[i] = set[i-1];
		
		set[0] = x;
		*len_ptr += 1;
		return set;
	}
	
	//End
	else if (x >= set[len-1]) {
		set = (int*) realloc(set, sizeof(int) * (len+1));
		set[len] = x;
		*len_ptr += 1;
		return set;
	}
	
	
	/*******************************************************************
	 * 3. Otherwise, find an index where 'x' should be inserted
	 ******************************************************************/
	int index;
	int halfway_value = set[len/2];
	
	//If 'x' is small
	if (x <= halfway_value) {
		for (int i=0; i<=len-2; i++) {
			if (x>=set[i] && x<=set[i+1]) {
				index = i+1;
				break;
			}
		}
	}
	
	//If 'x' is large
	else if (x > halfway_value) {
		for (int i=len-2; i>=0; i--) {
			if (x>=set[i] && x<=set[i+1]) {
				index = i+1;
				break;
			}
		}
	}
	
	
	/*******************************************************************
	 * 4. Shift items over and insert 'x' at the index
	 ******************************************************************/
	set = (int*) realloc(set, sizeof(int) * (len+1));
	
	for (int i=len; i>index; i--)
		set[i] = set[i-1];

	
	set[index] = x;
	*len_ptr += 1;
	
	return set;
}



int product_of_list(int* list, int len) {
	if (list==NULL || len==0)
		return 0;
		
	int product = 1;
	for (int i=0; i<len; i++)
		product = product*list[i];
	return product;
}




/* Digit functions */
int* digits_of(int x) {
	/*******************************************************************
	 * 1. If 'x' is one digit, return an allocated pointer to it
	 ******************************************************************/
	if (x<=9) {
		int* list = (int*) malloc(sizeof(int));
		list[0] = x;
		return list;
	}
	
	/*******************************************************************
	 * 2. Count the digits of 'x' and prepare the 'digit_column'
	 ******************************************************************/
	int count = digit_count(x);
	int digit_column = int_pow(10, count-1);
	
	/*******************************************************************
	 * 3. Prepare the list of digits
	 ******************************************************************/
	int* list = (int*) calloc(count, sizeof(int));
	int index = 0;
	
	/*******************************************************************
	 * 4. Record every digit of 'x' on the list
	 ******************************************************************/
	while (digit_column > 0) {
		int current_digit = x/digit_column - 10*(x/(digit_column*10));
		
		list[index] = current_digit;
		index += 1;
		
		digit_column = digit_column/10;
	}
	
	/*******************************************************************
	 * 5. Return the allocated list
	 ******************************************************************/
	return list;
}



int digit_count(int x) {
	if (x<=9)
		return 1;
	else if (x<=99)
		return 2;
	else if (x<=999)
		return 3;
	else if (x<=9999)
		return 4;
	else if (x<=99999)
		return 5;
	else if (x<=999999)
		return 6;
	else if (x<=9999999)
		return 7;
	else if (x<=99999999)
		return 8;
	else if (x<=999999999)
		return 9;
	return 0;
}



int* sorted_digits_of(int x) {
	/*******************************************************************
	 * 1. If 'x' is one digit, return an allocated pointer to it
	 ******************************************************************/
	if (x<=9) {
		int* list = malloc(sizeof(int));
		list[0] = x;
		return list;
	}
	
	
	/*******************************************************************
	 * 2. Count the digits of 'x' and prepare the 'digit_column'
	 ******************************************************************/
	int count = digit_count(x);
	int digit_column = int_pow(10, count-1);
	
	
	/*******************************************************************
	 * 3. Prepare the list of digits
	 ******************************************************************/
	int* list = (int*) calloc(count, sizeof(int));
	int index = 0;
	
	
	/*******************************************************************
	 * 4. Record every digit of 'x' on the list
	 ******************************************************************/
	while (digit_column > 0) {
		int current_digit = x/digit_column - 10*(x/(digit_column*10));
		
		list = insert(list, current_digit, &index);
		
		digit_column = digit_column/10;
	}
	
	
	/*******************************************************************
	 * 5. Return the allocated list
	 ******************************************************************/
	return list;
}





int replace_digit(int x, int new_digit, int index) {
	/*******************************************************************
	 * 1. Get the list of digits of 'x'
	 ******************************************************************/
	int* list = digits_of(x);
	int list_len = digit_count(x);
	
	
	/*******************************************************************
	 * 2. Replace the digit at 'index' with 'new_digit'
	 ******************************************************************/
	list[index] = new_digit;
	
	
	/*******************************************************************
	 * 3. Convert the list back into an integer
	 ******************************************************************/
	int integer = 0;
	int multiplier = 1;
	for (int d=list_len-1; d>=0; d--) {
		integer += list[d]*multiplier;
		multiplier *= 10;
	}
	return integer;
}






//This is used in digits_of() and sorted_digits_of()
int int_pow(int base, int exp) {
	if (base==1 || exp==0)
		return 1;
	
	int x = base;
	for (int e=1; e<exp; e++)
		x *= base;
	
	return x;
}




/* Factor functions */
//Use odd_factor_count() to get the size of this array
int64_t* odd_factors_of(int64_t x) {
	/*******************************************************************
	 * 1. Make an exception for 1
	 ******************************************************************/
	if (x==1) {
		int64_t* set = (int64_t*) malloc(sizeof(int64_t));
		set[0] = 1;
		return set;
	}
	
	
	/*******************************************************************
	 * 2. Prepare the sets of factors
	 ******************************************************************/
	int64_t* upper = (int64_t*) malloc(sizeof(int64_t));
	int upper_len = 1;
	upper[0] = x;
	
	int64_t* lower = NULL;
	int lower_len;
	
	if (IS_EVEN(x)) {
		lower = (int64_t*) malloc(sizeof(int64_t)*2);
		lower_len = 2;
		lower[0] = 1;
		lower[1] = 2;
	}
	else {
		lower = (int64_t*) malloc(sizeof(int64_t));
		lower_len = 1;
		lower[0] = 1;
	}
	
	
	
	/*******************************************************************
	 * 3. Starting at 3, find every odd factor of 'x'
	 *    Put the small ones in 'lower' and the large ones in 'upper'
	 ******************************************************************/
	int64_t factor = 3;
	
	while (factor < min_int64(upper, upper_len)) {
		if (IS_DIVISIBLE(x, factor)) {
			lower = append_int64(lower, factor, &lower_len);
			
			if (IS_ODD(x/factor) && factor*factor != x)
				upper = append_int64(upper, x/factor, &upper_len);
		}
			
		factor += 2;
	}
	
	
	/*******************************************************************
	 * DEBUG: Print the two sets
	 ******************************************************************/
	//printf("lower: {");
	//for (int i=0; i<lower_len; i++)
		//printf("%lld ", lower[i]);
	//printf("\b}\nupper: {");
	//for (int i=0; i<upper_len; i++)
		//printf("%lld ", upper[i]);
	//printf("\b} \n");
	
	
	
	/*******************************************************************
	 * 4. If 'x' is even and 'upper' contains only it, return 'lower'
	 ******************************************************************/
	if (upper_len==1 && IS_EVEN(x)) {
		free(upper);
		return lower;
	}
	
	
	
	/*******************************************************************
	 * 5. Otherwise, combine 'upper' and 'lower' into one set
	 ******************************************************************/
	upper = (int64_t*) realloc(upper, sizeof(int64_t) * upper_len * 2);
	
	for (int i=0; i<lower_len; i++) {
		upper[upper_len] = lower[i];
		upper_len++;
	}
	
	free(lower);
	return upper;
}




int odd_factor_count(int64_t x) {
	/*******************************************************************
	 * 1. Make an exception for some 1-digit numbers
	 ******************************************************************/
	if (x==1 || x==2 || x==4 || x==6 || x==8)
		return 1;
	else if (x==3 || x==5 || x==7)
		return 2;
	else if (x==9)
		return 3;
	
	
	
	/*******************************************************************
	 * 2. Prepare the sets of factors
	 ******************************************************************/
	int64_t* upper = (int64_t*) malloc(sizeof(int64_t));
	int upper_len = 1;
	upper[0] = x;
	
	int64_t* lower = NULL;
	int lower_len;
	
	if (IS_EVEN(x)) {
		lower = (int64_t*) malloc(sizeof(int64_t)*2);
		lower_len = 2;
		lower[0] = 1;
		lower[1] = 2;
	}
	else {
		lower = (int64_t*) malloc(sizeof(int64_t));
		lower_len = 1;
		lower[0] = 1;
	}
	
	
	
	/*******************************************************************
	 * 3. Starting at 3, find every odd factor of 'x'
	 *    Put the small ones in 'lower' and the large ones in 'upper'
	 ******************************************************************/
	int64_t factor = 3;
	
	while (factor < min_int64(upper, upper_len)) {
		if (IS_DIVISIBLE(x, factor)) {
			lower = append_int64(lower, factor, &lower_len);
			
			if (IS_ODD(x/factor) && factor*factor != x)
				upper = append_int64(upper, x/factor, &upper_len);
		}
			
		factor += 2;
	}
	
	
	/*******************************************************************
	 * DEBUG: Print the two sets
	 ******************************************************************/
	//printf("lower: {");
	//for (int i=0; i<lower_len; i++)
		//printf("%lld ", lower[i]);
	//printf("\b}\nupper: {");
	//for (int i=0; i<upper_len; i++)
		//printf("%lld ", upper[i]);
	//printf("\b} \n");
	
	
	
	/*******************************************************************
	 * 4. If 'x' is even and 'upper' contains only it, return 
	 *    'lower_len'
	 ******************************************************************/
	if (upper_len==1 && IS_EVEN(x)) {
		free(upper);
		free(lower);
		return lower_len;
	}
	
	
	
	/*******************************************************************
	 * 5. Otherwise, return the combined lengths
	 ******************************************************************/
	free(upper);
	free(lower);
	return upper_len+lower_len;
}



int* factors_of(int x) {
	/*******************************************************************
	 * 1. Make an exception for 1
	 ******************************************************************/
	if (x==1) {
		int* set = (int*) malloc(sizeof(int));
		set[0] = 1;
		return set;
	}
	
	
	/*******************************************************************
	 * 2. Prepare the sets of factors
	 ******************************************************************/
	int* upper = (int*) malloc(sizeof(int));
	int* lower = (int*) malloc(sizeof(int));
	
	upper[0] = x;
	lower[0] = 1;
	
	int upper_len = 1;
	int lower_len = 1;
	
	
	
	/*******************************************************************
	 * 3. Starting at 2, find every factor of 'x'
	 *    Put the small ones in 'lower' and the large ones in 'upper'
	 ******************************************************************/
	int factor = 2;
	
	while (factor<min(upper, upper_len)) {
		if (IS_DIVISIBLE(x, factor)) {
			lower = append(lower, factor, &lower_len);
			
			if (factor*factor != x)
				upper = append(upper, x/factor, &upper_len);
		}
			
		factor += 1;
	}
	
	
	/*******************************************************************
	 * DEBUG: Print the two sets
	 ******************************************************************/
	//printf("lower: {");
	//for (int i=0; i<lower_len; i++)
		//printf("%ld ", lower[i]);
	//printf("\b}\nupper: {");
	//for (int i=0; i<upper_len; i++)
		//printf("%ld ", upper[i]);
	//printf("\b} \n");
	
	
	/*******************************************************************
	 * 4. Combine 'upper' and 'lower' into one set, then return
	 ******************************************************************/
	upper = (int*) realloc(upper, sizeof(int) * upper_len * 2);
	
	for (int i=0; i<lower_len; i++) {
		upper[upper_len] = lower[i];
		upper_len++;
	}
	
	free(lower);
	return upper;
}





int factor_count(int x) {
	/*******************************************************************
	 * 1. Make an exception for 1
	 ******************************************************************/
	if (x==1)
		return 1;
		
		
	/*******************************************************************
	 * 2. Prepare the sets of factors
	 ******************************************************************/
	int* upper = (int*) malloc(sizeof(int));
	int* lower = (int*) malloc(sizeof(int));
	
	upper[0] = x;
	lower[0] = 1;
	
	int upper_len = 1;
	int lower_len = 1;
	
	
	
	/*******************************************************************
	 * 3. Starting at 2, find every factor of 'x'
	 *    Put the small ones in 'lower' and the large ones in 'upper'
	 ******************************************************************/
	int factor = 2;
	
	while (factor<min(upper, upper_len)) {
		if (IS_DIVISIBLE(x, factor)) {
			lower = append(lower, factor, &lower_len);
			
			if (factor*factor != x)
				upper = append(upper, x/factor, &upper_len);
		}
			
		factor += 1;
	}
	
	
	/*******************************************************************
	 * 4. Cleanup, then return the total count
	 ******************************************************************/
	free(upper);
	free(lower);
	return upper_len+lower_len;
}







int sum_of_proper_divisors_of(int x) {
	/*******************************************************************
	 * Get the list of x's proper divisors
	 ******************************************************************/
	int* list = proper_divisors_of(x);
	int list_len = proper_divisor_count(x);
	
	/*******************************************************************
	 * Sum them and return
	 ******************************************************************/
	int sum = 0;
	for (int i=0; i<list_len; i++)
		sum += list[i];
	return sum;
}








int proper_divisor_count(int x) {
	/*******************************************************************
	 * 0. Make a special case for some 1-digit numbers
	 ******************************************************************/
	if (x==1 || x==2 || x==3 || x==5 || x==7)
		return 1;
	
	
	/*******************************************************************
	 * 1. Prepare the sets of factors
	 ******************************************************************/
	int* upper = (int*) malloc(sizeof(int));
	int* lower = (int*) malloc(sizeof(int));
	
	upper[0] = x;
	lower[0] = 1;
	
	int upper_len = 1;
	int lower_len = 1;
	
	
	/*******************************************************************
	 * 2. Starting at 2, find every factor of 'x'
	 *    Put the small ones in 'lower' and the large ones in 'upper'
	 ******************************************************************/
	int factor = 2;
	
	while (factor<min(upper, upper_len)) {
		if (IS_DIVISIBLE(x, factor)) {
			lower = append(lower, factor, &lower_len);
			
			if (factor*factor != x)
				upper = append(upper, x/factor, &upper_len);
		}
			
		factor += 1;
	}
	
	
	/*******************************************************************
	 * DEBUG: Print the two sets
	 ******************************************************************/
	//printf("lower: {");
	//for (int i=0; i<lower_len; i++)
		//printf("%ld ", lower[i]);
	//printf("\b}\nupper: {");
	//for (int i=0; i<upper_len; i++)
		//printf("%ld ", upper[i]);
	//printf("\b} \n");

	
	
	/*******************************************************************
	 * 4. Return the combined lengths of 'upper' and 'lower' minus 1
	 *    (the "minus 1" is 'x' itself, which isn't considered a
	 *     proper divisor)
	 ******************************************************************/
	free(upper);
	free(lower);
	return upper_len+lower_len-1;
}







int* proper_divisors_of(int x) {
	/*******************************************************************
	 * 0. Make a special case for some 1-digit numbers
	 ******************************************************************/
	if (x==1 || x==2 || x==3 || x==5 || x==7) {
		int* set = (int*) malloc(sizeof(int));
		set[0] = 1;
		return set;
	}
	
	
	
	/*******************************************************************
	 * 1. Prepare the sets of factors
	 ******************************************************************/
	int* upper = malloc(sizeof(int));
	int* lower = malloc(sizeof(int));
	
	upper[0] = x;
	lower[0] = 1;
	
	int upper_len = 1;
	int lower_len = 1;
	
	
	
	/*******************************************************************
	 * 2. Starting at 2, find every factor of 'x'
	 *    Put the small ones in 'lower' and the large ones in 'upper'
	 ******************************************************************/
	int factor = 2;
	
	while (factor<min(upper, upper_len)) {
		if (IS_DIVISIBLE(x, factor)) {
			lower = append(lower, factor, &lower_len);
			
			if (factor*factor != x)
				upper = append(upper, x/factor, &upper_len);
		}
			
		factor += 1;
	}
	
	
	
	/*******************************************************************
	 * DEBUG: Print the two sets
	 ******************************************************************/
	//printf("lower: {");
	//for (int i=0; i<lower_len; i++)
		//printf("%ld ", lower[i]);
	//printf("\b}\nupper: {");
	//for (int i=0; i<upper_len; i++)
		//printf("%ld ", upper[i]);
	//printf("\b} \n");
	
	
	
	/*******************************************************************
	 * 3. Remove 'x' from 'upper'
	 ******************************************************************/
	for (int i=0; i<upper_len; i++)
		upper[i] = upper[i+1];
	upper_len--;
	
	
	
	/*******************************************************************
	 * 4. Combine 'upper' and 'lower' into one set, then return
	 ******************************************************************/
	upper = (int*) realloc(upper, sizeof(int) * (upper_len+lower_len));
	
	for (int i=0; i<lower_len; i++) {
		upper[upper_len] = lower[i];
		upper_len++;
	}
	
	free(lower);
	return upper;
}




int distinct_prime_factor_count(int x, int* primes, int primes_len) {
	/*******************************************************************
	 * If 'x' is prime, then it's its own sole prime factor
	 ******************************************************************/
	if (is_prime(x))
		return 1;
	
	
	/*******************************************************************
	 * If 'x' is the square of a prime, then return 1
	 ******************************************************************/
	for (int p=0; p<primes_len; p++) {
		int square = primes[p]*primes[p];
		
		if (square==x)
			return 1;
		else if (square>x)
			break;
	}
	
	
	
	/*******************************************************************
	 * Otherwise, find the distinct prime factors
	 ******************************************************************/
	int* factors = NULL;
	int len = 0;
	int y = x;
	
	for (int p=0; p<primes_len; p++) {
		int prime = primes[p];
		
		if (prime>x)
			break;
		
		if (IS_DIVISIBLE(y, prime)) {
			factors = append(factors, prime, &len);
			y = y/prime;
			
			while (is_prime(y)) {
				factors = append(factors, y, &len);
				if (IS_DIVISIBLE(y, prime))
					y = y/prime;
				else
					break;
			}
		}
		
		if (product_of_list(factors, len)==x)
			break;
	}
	
	
	/*******************************************************************
	 * Remove repeating terms from the list
	 ******************************************************************/
	for (int i=0; i<len-1; i++) {
		if (factors[i]==0)
			continue;
		
		for (int j=i+1; j<len; j++)
			if (factors[i]==factors[j]) {
				factors[j] = 0;
			}
	}

	
	/*******************************************************************
	 * Count the remaining terms
	 ******************************************************************/
	int count = 0;
	for (int i=0; i<len; i++)
		if (factors[i] > 0)
			count++;

	free(factors);
	return count;
}





/* Property functions ("is" functions) */
inline bool is_prime_int64(int64_t x) {
	if (x==1)
		return false;
	
	else if (x==3 || x==5)
		return true;
	
	for (int64_t d=5; d<x; d+=2)
		if (x%d==0)
			return false;
	
	return true;
}



bool is_palindromic_int(int x) {
	/*******************************************************************
	 * 1. Get the list of x's digits
	 ******************************************************************/
	int* list = digits_of(x);
	int len = digit_count(x);
	
	
	/*******************************************************************
	 * 2. Compare every left digit with its equally-distanced right
	 *    digit
	 * 
	 *    If the left doesn't match the right, return false
	 ******************************************************************/
	int left = 0;
	int right = len-1;
	
	while (left <= right) {
		if (list[left] != list[right]) {
			free(list);
			return false;
		}
		
		left++;
		right--;
	}
	
	free(list);
	return true;
}



bool is_palindromic_array(int* x, int len) {
	/*******************************************************************
	 * Compare every left item with its equally-distanced right item.
	 * If they all match, the array is a palindrome.
	 ******************************************************************/
	int left = 0;
	int right = len-1;
	
	while (left <= right) {
		if (x[left] != x[right])
			return false;
		left++;
		right--;
	}
	return true;
}



bool is_permutation(int x, int y) {
	int x_len = digit_count(x);
	int y_len = digit_count(y);
	
	if (x_len != y_len)
		return false;
		
	int* x_list = sorted_digits_of(x);
	int* y_list = sorted_digits_of(y);
	
	if (is_equal_array(x_list, x_len, y_list, y_len))
		return true;
	
	return false;
}



//Pythagorean triplet conditions:
//1. a<b<c
//2. a^2 + b^2 = c^2
bool is_pythagorean_triplet(int a, int b, int c) {
	if (a<b && b<c && a*a+b*b==c*c)
		return true;
	return false;
}


bool is_abundant(int x) {
	/*******************************************************************
	 * 1. Find the proper divisors of 'x'
	 ******************************************************************/
	int* proper_divisors = proper_divisors_of(x);
	int len = proper_divisor_count(x);
	
	
	/*******************************************************************
	 * 2. Sum the proper divisors
	 *    If the sum ever exceeds 'x', return true
	 ******************************************************************/
	int sum = 0;
	for (int d=0; d<len; d++) {
		sum += proper_divisors[d];
		
		if (sum>x) {
			free(proper_divisors);
			return true;
		}
	}

	free(proper_divisors);
	return false;
}



bool is_prime(int x) {
	if (x==2 || x==3)
		return true;
	
	else if (x%2==0 || x==1 || x<=0)
		return false;
	
	for (int y=3; y<x; y+=2)
		if (x%y==0)
			return false;
	
	return true;
}



bool is_pandigital_1_to_9(int64_t x) {
	/*******************************************************************
	 * 1. Convert to string
	 ******************************************************************/
	char* str = (char*) calloc(16, sizeof(char));
	sprintf(str, "%lld", x);
	
	
	/*******************************************************************
	 * 2. If x doesn't have exactly 9 digits, return false
	 ******************************************************************/
	if (strlen(str) != 9) {
		free(str);
		return false;
	}
	
	
	/*******************************************************************
	 * 3. If any digits repeat, OR if any digit is zero, return false
	 ******************************************************************/
	for (int i=0; i<8; i++) {
		for (int j=i+1; j<9; j++) {
			if (str[i]==str[j] || str[i]=='0' || str[j]=='0') {
				free(str);
				return false;
			}
		}
	}
	
	/*******************************************************************
	 * 4. If x passed all of the above tests, return true
	 ******************************************************************/
	free(str);
	return true;
}



bool is_equal_array(int* set1, int len1, int* set2, int len2) {
	if (len1 != len2)
		return false;
	
	for (int i=0; i<len1; i++)
		if (set1[i] != set2[i])
			return false;
	
	return true;
}



/* Sequence functions */
int* eratosthenes(int limit) {
	int* numbers = (int*) calloc(limit, sizeof(int));
	if (numbers==NULL) {
		printf("eratosthenes(%d) failed \n", limit);
		return NULL;
	}
	
	int* primes = NULL;
	int primes_len = 0;
	
	for (int i=0; i<limit; i++)
		numbers[i] = i+1;
	
	int cross_out_index;
	for (int i=1; i<limit; i++) {
		if (numbers[i]>0) {
			//1. Resize 'primes'
			size_t new_primes_size = sizeof(int)*(primes_len+1);
			primes = (int*) realloc(primes, new_primes_size);
			if (primes==NULL) {
				printf("eratosthenes(%d) failed \n", limit);
				return NULL;
			}
			
			//2. Append
			primes[primes_len] = numbers[i];
			primes_len++;
			
			//3. Cross the multiples out
			cross_out_index = i+numbers[i];
			while (cross_out_index < limit) {
				numbers[cross_out_index] = 0;
				cross_out_index += numbers[i];
			}
		}
	}
	
	free(numbers);
	return primes;
}


int eratosthenes_count(int limit) {
	int* numbers = (int*) calloc(limit, sizeof(int));
	if (numbers==NULL) {
		printf("eratosthenes_count(%d) failed \n", limit);
		return -1;
	}
	
	int count = 0;
	
	for (int i=0; i<limit; i++)
		numbers[i] = i+1;
	
	int cross_out_index;
	for (int i=1; i<limit; i++) {
		if (numbers[i]>0) {
			//1. Count this prime
			count++;
			
			//2. Cross the multiples out
			cross_out_index = i+numbers[i];
			while (cross_out_index < limit) {
				numbers[cross_out_index] = 0;
				cross_out_index += numbers[i];
			}
		}
	}
	
	free(numbers);
	return count;
}

int nth_triangular_number(int n) {
	int sum = 0;
	
	for (int x=0; x<=n; x++)
		sum += x;
	
	return sum;
}


int64_t nth_pentagonal_number_int64(int n) {
	int64_t p = n;
	p = p*(3*n-1);
	p = p/2;
	return p;
}


int64_t nth_triangular_number_int64(int n) {
	int64_t sum = 0;
	for (int x=1; x<=n; x++)
		sum += x;
	return sum;
}



int64_t nth_hexagonal_number_int64(int n) {
	int64_t h = 2*n-1;
	return h*n;
}


int factorial(int x) {
	int a=1;
	
	for (int b=0; b<x; b++)
		a *= (b+1);
		
	return a;
}




int* rotations_of(int x) {
	/*******************************************************************
	 * 1. Prepare the necessary resources (list of digits, etc.)
	 ******************************************************************/
	int* digit_list			= digits_of(x);
	int total_digits		= digit_count(x);
	int multiplier			= int_pow(10, total_digits-1);
	int total_rotations		= total_digits;
	
	
	/*******************************************************************
	 * 2. Prepare the list of rotations of 'x'
	 ******************************************************************/
	int* rotations = calloc(total_rotations, sizeof(int));
	int rotation_index = 0;
	
	
	
	/*******************************************************************
	 * 3. Perform the rotation (shift every digit one space to the
	 *    left, then move the first digit to the end)
	 ******************************************************************/
	for (int r=0; r<total_rotations; r++) {
		/***************************************************************
		 * 3a. Get the first digit
		 **************************************************************/
		int first_digit = digit_list[0];
		
		
		/***************************************************************
		 * 3b. Move the other digits 1 space to the left
		 **************************************************************/
		for (int d=0; d<total_digits-1; d++)
			digit_list[d] = digit_list[d+1];
			
			
		/***************************************************************
		 * 3c. Put the first digit on the end
		 **************************************************************/
		digit_list[total_digits-1] = first_digit;
		
		
		/***************************************************************
		 * 3d. Convert this array of digits into an integer
		 **************************************************************/
		int integer = 0;
		int m = multiplier;
		
		for (int d=0; d<total_digits; d++) {
			integer += (digit_list[d] * m);
			m = m/10;
		}
		
		
		/***************************************************************
		 * 3e. Add this integer to the list of rotations
		 **************************************************************/
		rotations[rotation_index] = integer;
		rotation_index++;
	}
	
	
	/*******************************************************************
	 * 4. Return the list of rotations
	 ******************************************************************/
	free(digit_list);
	return rotations;
}






int* truncated_stages(int x) {
	/*******************************************************************
	 * 1. Prepare:
	 *     - The list of x's digits
	 *     - The digit count
	 *     - The digit column (largest multiple of 10 which is smaller 
	 *       than x, e.g. 1000 for 3797)
	 ******************************************************************/
	int* digits = digits_of(x);
	int count = digit_count(x);
	int digit_column = int_pow(10, count-1);
	
	
	/*******************************************************************
	 * 2. Prepare the list of stages (truncated forms of x)
	 ******************************************************************/
	int* stages = NULL;
	int stages_len = 0;
	
	
	/*******************************************************************
	 * 3. Truncate digits from left to right
	 *    Save each stage
	 ******************************************************************/
	int stage = x;
	
	for (int d=0; d<count-1; d++) {
		/***************************************************************
		 * 3a. Get the stage (truncate the leftmost digit)
		 **************************************************************/
		stage = stage - digits[d]*digit_column;
		
		
		/***************************************************************
		 * 3b. Add it to the list
		 **************************************************************/
		stages = append(stages, stage, &stages_len);
		
		
		/***************************************************************
		 * 3c. Divide digit_column by 10
		 **************************************************************/
		digit_column = digit_column/10;
	}
	
	
	
	/*******************************************************************
	 * 4. Do the same thing, but from right to left
	 ******************************************************************/
	stage = x;
	
	for (int d=count-1; d>0; d--) {
		/***************************************************************
		 * 4a. Get the stage (truncate the rightmost digit)
		 **************************************************************/
		stage = stage - digits[d];
		stage = stage/10;
		
		
		/***************************************************************
		 * 4b. Add it to the list
		 **************************************************************/
		stages = (int*) realloc(stages, sizeof(int)*(stages_len+1) );
		stages[stages_len] = stage;
		stages_len++;
	}
	
	
	/*******************************************************************
	 * 5. Return the list of stages
	 ******************************************************************/
	free(digits);
	return stages;
}



int total_truncated_stages(int x) {
	int count = digit_count(x);
	
	return (2*count)-2;
}





int* nth_permutation_of_pandigital(int n, int length) {
	/*******************************************************************
	 * Prepare the pool (array which represents the smallest pandigital
	 * number that is exactly 'length' digits long) and solution set.
	 * 
	 * Note: If a pandigital is 10 digits long, it goes from 0 to 9.
	 *       Otherwise, it goes from 1 to n.
	 ******************************************************************/
	int* pool 						= calloc(length, sizeof(int));
	int* solution					= calloc(length, sizeof(int));
	int _							= -1; //Represents an empty slot
	int solution_len				= 0;
	int total_possible_permutations	= factorial(length);
	
	for (int i=0; i<length; i++) {
		if (length==10)
			pool[i] = i;
		else
			pool[i] = i+1;
		
		solution[i] = _;
	}


	
	/*******************************************************************
	 * Repeatedly perform the method described in 24_explanation.txt
	 * until the length of solution set equals the length of the
	 * original pool
	 ******************************************************************/
	int range_size = total_possible_permutations/length;
	int range_marker = 0;
	
	while (1) {
		/***************************************************************
		 * 1. Find which row is correct
		 **************************************************************/
		int row = 0;
		
		while (range_marker+range_size < n) {
			row += 1;
			range_marker += range_size;
		}
		
		
		/***************************************************************
		 * 2. Create a list of items that remain in the pool
		 **************************************************************/
		int remaining_pool_len = 0;
		for (int p=0; p<length; p++)
			if (pool[p] != _)
				remaining_pool_len += 1;
		
		int* remaining_pool = calloc(remaining_pool_len, sizeof(int));
		int r = 0;
		for (int p=0; p<length; p++)
			if (pool[p] != _) {
				remaining_pool[r] = pool[p];
				r += 1;
			}
		
		
		/***************************************************************
		 * 3. Transfer the appropriate item from the remaining_pool into
		 *    the solution
		 **************************************************************/
		int remaining_pool_index = row;
		
		solution[solution_len] = remaining_pool[remaining_pool_index];
		solution_len += 1;
		
		int remove_index = 0;
		while (pool[remove_index] != solution[solution_len-1])
			remove_index += 1;
		
		pool[remove_index] = _;
		free(remaining_pool);
		
		//print_set(solution, length);
		
		
		/***************************************************************
		 * 4. Stop if the the solution has the same length as the
		 *    original set
		 **************************************************************/
		if (solution_len==length)
			break;
		
		
		/***************************************************************
		 * 5. Otherwise, perform another pass with new ranges
		 **************************************************************/
		int range_start = range_marker;
		int range_end = range_marker + range_size;
		
		range_marker = range_start;
		
		range_size = (range_end-range_start)/(length-solution_len);
	}

	
	
	/*******************************************************************
	 * Free memory and return
	 ******************************************************************/
	free(pool);
	return solution;
}


void print_pandigital(int* pandigital, int len) {
	for (int i=0; i<len; i++)
		printf("%d", pandigital[i]);
	printf("\n");
}









int64_t string_to_int64(char* str) {
	int64_t x = 0;
	int64_t multiply = 1;
	int len = (int) strlen(str);
	
	for (int i=len-1; i>=0; i--) {
		int64_t digit = CHAR_TO_INT(str[i]);
		digit *= multiply;
		x += digit;
		multiply *= 10;
	}
	
	return x;
}





int final_digit_of(int64_t x) {
	if (x<=9)
		return x;
	
	for (int d=0; d<=9; d++)
		if ( (x-d)%10==0 )
			return d;

	return -1;
}


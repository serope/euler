/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * euler.c
 **********************************************************************/
#include "euler_binary.h"


bool binary_sequence_is_palindrome(bool* x, int len) {
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



int binary_sequence_count(int x) {
	int pow = 1;
	
	while (true) {
		int max = int_pow(2, pow);
		
		if (max <= x)
			pow++;
		else
			break;
	}
	return pow;
}



bool* binary_sequence_of(int x) {
	/*******************************************************************
	 * 1. Get the length of the binary sequence
	 ******************************************************************/
	int len;
	int pow = 1;
	
	while (true) {
		int max = int_pow(2, pow);
		
		if (max <= x)
			pow++;
		else
			break;
	}
	len = pow;


	/*******************************************************************
	 * 2. Get the decimal multiplier of the first bit in the sequence
	 ******************************************************************/
	int m = int_pow(2, len-1);
	
	
	
	/*******************************************************************
	 * 3. Create the binary sequence
	 ******************************************************************/
	bool* sequence = calloc(len, sizeof(bool));
	int y = x;
	
	for (int i=0; i<len; i++) {
		if (m <= y) {
			sequence[i] = true;
			y -= m;
		}
		m = m/2;
	}
	
	return sequence;
}



void binary_sequence_print(bool* b, int len) {
	for (int i=0; i<len; i++)
		printf("%d", (int) b[i]);
	printf("\n");
}







bool* append_bool(bool* set, bool b, int* len_ptr) {
	int len = *len_ptr;
	
	if (set==NULL || len==0) {
		set = (bool*) malloc(sizeof(bool));
		set[0] = b;
		*len_ptr += 1;
		return set;
	}
	
	set = (bool*) realloc(set, sizeof(bool)*(len+1));
	set[len] = b;
	*len_ptr += 1;
	return set;
}






bool* prepend_bool(bool* set, bool b, int* len_ptr) {
	int len = *len_ptr;
	if (set==NULL || len==0) {
		set = malloc(sizeof(bool));
		set[0] = b;
		return set;
	}
	
	set = realloc(set, sizeof(bool) * (len+1) );
	for (int i=len; i>0; i--)
		set[i] = set[i-1];
	
	set[0] = b;
	*len_ptr += 1;
	return set;
}


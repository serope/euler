/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 43
 **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int* digits_of(int x);
int** make_problem43_list(int divisor, int* list_len);
void free_problem43_list(int** list, int list_len);

bool contains(int* set, int set_len, int x);
bool has_repeating_elements(int* set , int set_len);
bool shares_element(int* list1, int list1_len, int* list2, int list2_len);



int main() {
	/*
	 * Generate lists of 3-digit sequences whose integer forms are
	 * divisible by 2, 3, 5, etc.
	 */
	int list2_len = 0;
	int list3_len = 0;
	int list5_len = 0;
	int list7_len = 0;
	int list11_len = 0;
	int list13_len = 0;
	int list17_len = 0;
	
	int** list2		= make_problem43_list(2, &list2_len);
	int** list3		= make_problem43_list(3, &list3_len);
	int** list5		= make_problem43_list(5, &list5_len);
	int** list7		= make_problem43_list(7, &list7_len);
	int** list11	= make_problem43_list(11, &list11_len);
	int** list13	= make_problem43_list(13, &list13_len);
	int** list17	= make_problem43_list(17, &list17_len);
	
	/*
	 * Try combining every term from every list into a pandigital
	 * sequence as shown in the example.
	 * 
	 * If the combination is a valid pandigital, add its integer form
	 * to the sum.
	 */
	int64_t sum = 0;
	for (int i2=0; i2<list2_len; i2++) {
		int* x2 = list2[i2];
		
		for (int i3=0; i3<list3_len; i3++) {
			//Check matches
			int* x3 = list3[i3];
			if (x3[0]!=x2[1] || x3[1]!=x2[2])
				continue;
			
			for (int i5=0; i5<list5_len; i5++) {
				//Check matches
				int* x5 = list5[i5];
				if (x5[0]!=x3[1] || x5[1]!=x3[2])
					continue;
				
				for (int i7=0; i7<list7_len; i7++) {
					//Check matches
					int* x7 = list7[i7];
					if (x7[0]!=x5[1] || x7[1]!=x5[2])
						continue;
					
					for (int i11=0; i11<list11_len; i11++) {
						//Check matches
						int* x11 = list11[i11];
						if (x11[0]!=x7[1] || x11[1]!=x7[2])
							continue;
						
						for (int i13=0; i13<list13_len; i13++) {
							//Check matches
							int* x13 = list13[i13];
							if (x13[0]!=x11[1] || x13[1]!=x11[2])
								continue;
								
							for (int i17=0; i17<list17_len; i17++) {
								//Check matches
								int* x17 = list17[i17];
								if (x17[0]!=x13[1] || x17[1]!=x13[2])
									continue;
								
								/*
								 * Form the last 9 digits of the
								 * pandigital sequence as shown in the
								 * example
								 */
								int* pan = calloc(10, sizeof(int));
								pan[1] = x2[0];
								pan[2] = x2[1];
								pan[3] = x2[2];
								pan[4] = x7[0];
								pan[5] = x7[1];
								pan[6] = x7[2];
								pan[7] = x17[0];
								pan[8] = x17[1];
								pan[9] = x17[2];
								
								//Fill in the missing 1st digit
								for (int i=0; i<10; i++) {
									if (contains(pan, 10, i))
										continue;
									else {
										pan[0] = i;
										break;
									}
								}
								
								/*
								 * If any digits repeat, then this is
								 * NOT a valid pandigital
								 */
								if (has_repeating_elements(pan, 10)) {
									free(pan);
									continue;
								}
								
								//Print
								for (int i=0; i<10; i++)
									printf("%d", pan[i]);
								printf("\n");
								
								//Convert pandigital into integer
								int64_t i = 0;
								int64_t m = 1000000000;
								for (int j=0; j<10; j++) {
									int digit = pan[j];
									i += m*digit;
									m = m/10;
								}
								
								//Add to sum
								sum += i;
								free(pan);
							}
						}
					}
				}
			}
		}
	}
	
	//Memory cleanup
	free_problem43_list(list2, list2_len);
	free_problem43_list(list3, list3_len);
	free_problem43_list(list5, list5_len);
	free_problem43_list(list7, list7_len);
	free_problem43_list(list11, list11_len);
	free_problem43_list(list13, list13_len);
	free_problem43_list(list17, list17_len);
	
	//Print sum
	printf("sum: %lld \n", sum);
	return 0;
}



/*
 * Returns true of the set has a repeating element
 */
bool has_repeating_elements(int* set , int set_len) {
	for (int i=0; i<set_len-1; i++)
		for (int j=i+1; j<set_len; j++)
			if (set[i]==set[j])
				return true;
	return false;
}


/*
 * Returns true if both sets have a common element
 */
bool shares_element(int* list1, int list1_len, int* list2, int list2_len) {
	for (int i=0; i<list1_len; i++)
		for (int j=0; j<list2_len; j++)
			if (list1[i]==list2[j])
				return true;
	return false;
}


/*
 * Generates a list of all 3-digit sequences whose integer forms are 
 * divisible by the given divisor
 * 
 * Free the returned list with free_problem43_list()
 */
int** make_problem43_list(int divisor, int* list_len) {
	//Declare list for storing 3-digit arrays
	int** list = NULL;
	
	for (int x=12; x<=999; x++) {
		if (x%divisor==0) {
			//Get digits
			int* digits = digits_of(x);
			
			//Get length
			int len;
			if (x<=99)
				len = 2;
			else
				len = 3;
			
			//If any digits repeat, skip this x
			if (has_repeating_elements(digits, len)) {
				free(digits);
				continue;
			}

			//If x has 2 digits, prepend 0
			if (len==2) {
				digits = (int*) realloc(digits, sizeof(int)*3);
				digits[2] = digits[1];
				digits[1] = digits[0];
				digits[0] = 0;
			}
			
			//Append x's digits to the list
			list = (int**) realloc(list, sizeof(int*) * ((*list_len)+1));
			list[*list_len] = digits;
			(*list_len)++;
		}
	}
	
	return list;
}


/*
 * Frees the memory returned by make_problem43_list()
 */
void free_problem43_list(int** list, int list_len) {
	for (int i=0; i<list_len; i++)
		free(list[i]);
	free(list);
}



/*
 * Performs a linear search and returns whether x is in set
 */
bool contains(int* set, int set_len, int x) {
	for (int i=0; i<set_len; i++)
		if (set[i]==x)
			return true;
	return false;
}



/*
 * Returns a slice of x's digits
 * e.g. digits_of(207) -> {2, 0, 7}
 */
int* digits_of(int x) {
	//If 'x' is one digit
	if (x<=9) {
		int* set = (int*) malloc(sizeof(int));
		set[0] = x;
		return set;
	}
	
	//Find the largest power of 10 which is smaller than 'x'
	int column = 10;
	while (column*10 < x)
		column *= 10;
	
	//Find every digit of 'x'
	int* digits = NULL;
	int digits_len = 0;
	
	while (column > 0) {
		//Get the digit
		int current = x/column - 10*(x/(column*10));
		
		//Append it to the list
		digits = (int*) realloc(digits, sizeof(int) * (digits_len+1) );
		digits[digits_len] = current;
		digits_len++;
		
		//Go to next column
		column /= 10;
	}

	return digits;
}

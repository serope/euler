/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * euler_bignum.c
 * 
 * Functions for handling big positive integers in Project Euler
 **********************************************************************/
#include "euler_bignum.h"





big big_new(char* string) {
	big b = (big) malloc(sizeof(struct big_s));
	b->array = NULL;
	b->len = 0;
	
	if (string==NULL)
		return b;
	
	int length = strlen(string);
	b->array = (int*) calloc(length, sizeof(int));
	b->len = length;
	
	for (int c=0; c<length; c++)
		b->array[c] = (int) (string[c]-48);
		
	return b;
}



void big_subtract(big base, big subtraction) {
	/*******************************************************************
	 * 1. Decompose the 'big' structs into int arrays
	 *    Set the larger one as 'a'
	 ******************************************************************/
	int* a = NULL;
	int* b = NULL;
	int a_len;
	int b_len;
	int comparison = big_compare(base, subtraction);
	
	//If 'a' is larger
	if (comparison==1) {
		a = calloc(base->len, sizeof(int));
		a = memcpy(a, base->array, sizeof(int)*base->len);
		a_len = base->len;

		b = calloc(subtraction->len, sizeof(int));
		b = memcpy(b, subtraction->array, sizeof(int)*subtraction->len);
		b_len = subtraction->len;
	}
	
	//If 'b' is larger
	else if (comparison==-1) {
		a = calloc(subtraction->len, sizeof(int));
		a = memcpy(a, subtraction->array, sizeof(int)*subtraction->len);
		a_len = subtraction->len;

		b = calloc(base->len, sizeof(int));
		b = memcpy(b, base->array, sizeof(int)*base->len);
		b_len = base->len;
	}
	
	//If 'a' and 'b' are equal
	else if (comparison==0) {
		base->array = (int*) realloc(base->array, sizeof(int));
		base->array[0] = 0;
		base->len = 1;
		return;
	}
	
	
	/*******************************************************************
	 * 2. If necessary, prepend zeros to 'b' so that  both 'a' and 'b'
	 *    have the same amount of digits
	 ******************************************************************/
	if (a_len > b_len) {
		int zeros_to_insert = a_len-b_len;
		
		int* new_b = (int*) calloc(a_len, sizeof(int));
		
		int old_b_index = 0;
		
		for (int i=zeros_to_insert; i<a_len; i++) {
			new_b[i] = b[old_b_index];
			old_b_index++;
		}
		
		free(b);
		b = (int*) calloc(a_len, sizeof(int));
		memcpy(b, new_b, sizeof(int)*a_len);
		free(new_b);
		
		b_len = a_len;
	}
	
	
	/*******************************************************************
	 * 3. Perform paper subtraction on 'a' and 'b'
	 ******************************************************************/
	int result_len = a_len;
	int* result = calloc(result_len, sizeof(int));
	
	for (int c=result_len-1; c>=0; c--) {
		//If necessary, borrow from the next-left column
		if (b[c] > a[c]) {
			a[c-1] -= 1;
			a[c] += 10;
		}
		
		//Subtract
		result[c] = a[c] - b[c];
	
	}
		
		
	/*******************************************************************
	 * 4. If the result has any leading zeros, remove them
	 ******************************************************************/
	if (result[0]==0) {
		//Count leading zeros and get the index of the first nonzero
		int leading_zeros = 0;
		int index;
		
		for (int i=0; i<result_len; i++) {
			if (result[i]==0)
				leading_zeros++;
			else {
				index = i;
				break;
			}
		}
		
		//Shift all the nonzeros (items from 'index' onward) to the left
		for (int i=index; i<result_len; i++)
			result[i-leading_zeros] = result[i];
			
		
		//Resize
		result_len -= leading_zeros;
		result = (int*) realloc(result, sizeof(int)*result_len);
	}
	
	
	
	/*******************************************************************
	 * 5. Copy the result to 'base'
	 ******************************************************************/
	base->len = result_len;
	free(base->array);
	base->array = calloc(result_len, sizeof(int));
	base->array = memcpy(base->array, result, sizeof(int)*result_len);
	
	
	/*******************************************************************
	 * 6. Free everything
	 ******************************************************************/
	free(a);
	free(b);
	free(result);
}



void big_copy(big source, big destination) {
	//1. Free the destination array
	free(destination->array);
	
	//2. Copy the size
	destination->len = source->len;
	
	//3. Copy the array
	destination->array = (int*) calloc(destination->len, sizeof(int));
	destination->array = (int*) memcpy(destination->array,
										source->array,
										sizeof(int)*destination->len);
}







big big_new_1_digit(int i) {
	big b = (big) malloc(sizeof(struct big_s));
	b->array = (int*) malloc(sizeof(int));
	b->array[0] = i;
	b->len = 1;
	
	return b;
}






big big_new_2_digits(int i) {
	big b = (big) malloc(sizeof(struct big_s));
	b->array = (int*) calloc(2, sizeof(int));
	
	int digit1 = i/10 - 10*(i/100);
	int digit2 = i - 10*(i/10);
	
	b->array[0] = digit1;
	b->array[1] = digit2;
	
	b->len = 2;
	
	return b;
}






big big_new_3_digits(int i) {
	big b = (big) malloc(sizeof(struct big_s));
	b->array = (int*) calloc(3, sizeof(int));
	
	int digit1 = i/100 - 10*(i/1000);
	int digit2 = i/10 - 10*(i/100);
	int digit3 = i - 10*(i/10);
	
	b->array[0] = digit1;
	b->array[1] = digit2;
	b->array[2] = digit3;
	
	b->len = 3;
	
	return b;
}






void big_print(big b) {
	for (int d=0; d<b->len; d++)
		printf("%d", b->array[d]);
	printf(" (len: %d) \n", b->len);
}







void big_multiply(big base, big multiplier) {
	/*******************************************************************
	 * 1. Decompose the 'big' structs into int arrays
	 *    Set the longer one as 'a'
	 ******************************************************************/
	int* a = NULL;
	int* b = NULL;
	int a_len;
	int b_len;
	
	if (base->len > multiplier->len) {
		a = (int*) calloc(base->len, sizeof(int));
		a = (int*) memcpy(a, base->array, sizeof(int)*base->len);
		a_len = base->len;

		b = (int*) calloc(multiplier->len, sizeof(int));
		b = (int*) memcpy(b, multiplier->array, sizeof(int)*multiplier->len);
		b_len = multiplier->len;
	}
	
	else {
		a = (int*) calloc(multiplier->len, sizeof(int));
		a = (int*) memcpy(a, multiplier->array, sizeof(int)*multiplier->len);
		a_len = multiplier->len;

		b = (int*) calloc(base->len, sizeof(int));
		b = (int*) memcpy(b, base->array, sizeof(int)*base->len);
		b_len = base->len;
	}
	
	
	
	/*******************************************************************
	 * 2. Get the maximum length of the result
	 ******************************************************************/
	int result_len = a_len*2;
	
	
	
	/*******************************************************************
	 * 3. Prepare the 'lines' (the numbers that are written under the
	 *    line when doing multiplication on paper) grid
	 ******************************************************************/
	int lines_len = 0;
	int total_lines = b_len;
	int** lines = (int**) calloc(total_lines, sizeof(int*));
	
	for (int l=0; l<total_lines; l++)
		lines[l] = (int*) calloc(result_len, sizeof(int));
	
	
	
	
	/*******************************************************************
	 * 4. Perform paper multiplication
	 ******************************************************************/
	int trailing_zeros = 0;
	
	for (int b_index = b_len-1; b_index!=-1; b_index--) {
		
		int* list = (int*) calloc(result_len, sizeof(int));
		int list_len = trailing_zeros;
		
		for (int a_index = a_len-1; a_index!=-1; a_index--) {
			
			int a_int = a[a_index];
			int b_int = b[b_index];
			int product = a_int*b_int + list[list_len];
			
			
			/***********************************************************
			 * Put the result on the list
			 * 
			 * If the product is 2 digits long (i.e. a "carry" is to
			 * take place), then add the left digit into the next
			 * spot on the list
			 **********************************************************/
			if (product>9) {
				int left_digit = product/10;
				int right_digit = product - 10*(product/10);
				
				list[list_len] = right_digit;
				list[list_len+1] += left_digit;
			}
			else
				list[list_len] = product;
			
			list_len += 1;
			
			
		}
		

		/***************************************************************
		 * Print the list
		 **************************************************************/
		//for (int l=result_len-1; l>-1; l--)
			//printf("%d ", list[l]);
		//printf("\n");
		
		
		/***************************************************************
		 * Copy the list to the 'result' grid, in reversed order
		 **************************************************************/
		int lines_index = 0;
		for (int l=result_len-1; l>-1; l--) {
			lines[lines_len][lines_index] = list[l];
			lines_index += 1;
		}
		lines_len += 1;
		
		
		/***************************************************************
		 * Free the list and increment 'trailing_zeros' for the next
		 * line
		 **************************************************************/
		free(list);
		trailing_zeros += 1;
	}
	
	
	
	/*******************************************************************
	 * _. Print the 'lines' grid
	 ******************************************************************/
	//for (int l=0; l<lines_len; l++) {
		//for (int d=0; d<result_len; d++)
			//printf("%d ", lines[l][d]);
		//printf("\n");
	//}
	
	
	
	/*******************************************************************
	 * 5. Perform paper addition on 'lines'
	 ******************************************************************/
	int* result = (int*) calloc(result_len, sizeof(int));
	int result_index = result_len-1;
	
	for (int c=result_len-1; c>-1; c--) {
		for (int r=0; r<lines_len; r++) {
			result[result_index] += lines[r][c];
			
			/***********************************************************
			 * If the value at the current result_index is greater
			 * than 10, then perform a "carry over"
			 **********************************************************/
			if (c>0 && result[result_index] > 9) {
				int x = result[result_index];
				while (x%10 != 0)
					x--;
				
				result[result_index-1] += x/10;
				
				result[result_index] -= x;
			}
		}
		
		result_index--;
	}
	
	//puts("result");
	//for (int r=0; r<result_len; r++)
		//printf("%d ", result[r]);
		
		
	/*******************************************************************
	 * 6. Determine the new size of the base (count the leading zeros,
	 *    then subtract it from the result len)
	 ******************************************************************/
	int leading_zeros = 0;
	int starting_index;
	int new_len;
	
	for (int i=0; i<result_len; i++) {
		if (result[i]==0)
			leading_zeros += 1;
		else {
			starting_index = i;
			break;
		}
	}
	
	new_len = result_len - leading_zeros;
	
	/*******************************************************************
	 * 7. Save the result into 'base'
	 ******************************************************************/
	free(base->array);
	
	base->len = new_len;
	base->array = (int*) calloc(new_len, sizeof(int));
	
	int big_array_index = 0;
	for (int i=starting_index; i<result_len; i++) {
		base->array[big_array_index] = result[i];
		big_array_index += 1;
	}
	
	
	/*******************************************************************
	 * 8. Free everything
	 ******************************************************************/
	free(a);
	free(b);
	free(result);
	
	for (int l=0; l<total_lines; l++)
		free(lines[l]);
	free(lines);
}








void big_add(big base, big addition) {
	/*******************************************************************
	 * 1. Decompose the 'big' structs into int arrays
	 *    Set the longer one as 'a'
	 ******************************************************************/
	int* a = NULL;
	int* b = NULL;
	int a_len;
	int b_len;
	
	if (base->len > addition->len) {
		a = (int*) calloc(base->len, sizeof(int));
		a = (int*) memcpy(a, base->array, sizeof(int)*base->len);
		a_len = base->len;

		b = (int*) calloc(addition->len, sizeof(int));
		b = (int*) memcpy(b, addition->array, sizeof(int)*addition->len);
		b_len = addition->len;
	}
	
	else {
		a = (int*) calloc(addition->len, sizeof(int));
		a = (int*) memcpy(a, addition->array, sizeof(int)*addition->len);
		a_len = addition->len;

		b = (int*) calloc(base->len, sizeof(int));
		b = (int*) memcpy(b, base->array, sizeof(int)*base->len);
		b_len = base->len;
	}
	
	
	
	/*******************************************************************
	 * 2. If necessary, insert zeros into the beginning of 'b' so that 
	 *    both 'a' and 'b' have the same amount of digits
	 ******************************************************************/
	if (a_len > b_len) {
		int zeros_to_insert = a_len-b_len;
		
		int* new_b = (int*) calloc(a_len, sizeof(int));
		
		int old_b_index = 0;
		
		for (int i=zeros_to_insert; i<a_len; i++) {
			new_b[i] = b[old_b_index];
			old_b_index++;
		}
		
		free(b);
		b = (int*) calloc(a_len, sizeof(int));
		b = (int*) memcpy(b, new_b, sizeof(int)*a_len);
		free(new_b);
		
		b_len = a_len;
	}
	
	
	
	/*******************************************************************
	 * 2. Get the maximum length of the result
	 ******************************************************************/
	int result_len = a_len+1;
	
	
	
	
	/*******************************************************************
	 * 3. Perform paper addition on 'a' and 'b'
	 ******************************************************************/
	int* result = (int*) calloc(result_len, sizeof(int));
	int result_index = result_len-1;
	
	for (int c=result_len-2; c>-1; c--) {
		result[result_index] += (a[c] + b[c]);
		
		/***********************************************************
		 * If the value at the current result_index is greater
		 * than 10, then perform a "carry over"
		 **********************************************************/
		if (result[result_index] > 9) {
			int x = result[result_index];
			while (x%10 != 0)
				x--;
			
			result[result_index-1] += x/10;
			
			result[result_index] -= x;
		}
	
		result_index--;
	}
	
	//puts("result");
	//for (int r=0; r<result_len; r++)
		//printf("%d ", result[r]);
		
		
	/*******************************************************************
	 * 4. If the result has a leading zero, remove it
	 ******************************************************************/
	if (result[0]==0) {
		for (int i=0; i<result_len-1; i++)
			result[i] = result[i+1];
		
		result = (int*) realloc(result, sizeof(int) * (result_len-1));
		
		result_len--;
	}
	
	
	
	/*******************************************************************
	 * 5. Prepare 'base' so that 'result' can be copied to it
	 * 
	 *    If necessary, make room in 'base' if it isn't big enough to
	 *    have the result copied to it
	 ******************************************************************/
	if (result_len > base->len) {
		base->len = result_len;
		free(base->array);
		base->array = (int*) calloc(result_len, sizeof(int));
	}
	
	/*******************************************************************
	 * 6. Save the result into 'base'
	 ******************************************************************/
	for (int i=0; i<result_len; i++)
		base->array[i] = result[i];
	
	
	/*******************************************************************
	 * 7. Free everything
	 ******************************************************************/
	free(a);
	free(b);
	free(result);
}






void big_pow(big base, unsigned int exponent) {
	/*******************************************************************
	 * 1. If the exponent is 0, then turn the base into 1
	 ******************************************************************/
	if (exponent==0) {
		BIG_FREE(base);
		base = big_new_1_digit(1);
		return;
	}
	
	
	/*******************************************************************
	 * 2. If the base is zero, then do nothing
	 ******************************************************************/
	else {
		big zero = big_new_1_digit(0);
		if (big_equals(base, zero)) {
			BIG_FREE(zero);
			return;
		}
		BIG_FREE(zero);
	}
	
	
	/*******************************************************************
	 * 3. Otherwise, multiply 'base' by itself 'exponent' times
	 ******************************************************************/
	big multiplier = big_new(NULL);
	big_copy(base, multiplier);
	
	for (int e=1; e<exponent; e++)
		big_multiply(base, multiplier);
	
	BIG_FREE(multiplier);
}






int big_sum_of_digits(big b) {
	int sum = 0;
	int len = b->len;
	
	for (int d=0; d<len; d++)
		sum += b->array[d];
	
	return sum;
}





bool big_equals(big a, big b) {
	if (a->len != b->len)
		return false;
	
	for (int i=0; i < a->len; i++)
		if (a->array[i] != b->array[i])
			return false;
	
	return true;
}





int big_compare(big a, big b) {
	//Return 1 if a>b
	//Return 0 if a=b
	//Return -1 if a<b
	
	if (a->len > b->len)
		return 1;
	else if (a->len < b->len)
		return -1;
	
	for (int i=0; i<a->len; i++) {
		if (a->array[i] > b->array[i])
			return 1;
		else if (a->array[i] < b->array[i])
			return -1;
	}
			
	return 0;
}





bool big_is_pow_of_10(big b) {
	if (b->len < 2)
		return false;
	
	int first_digit = b->array[0];
	int final_digit = b->array[b->len-1];
	
	if (first_digit!=1 || final_digit!=0)
		return false;
	
	for (int i=1; i<b->len; i++)
		if (b->array[i]!=0)
			return false;
	
	return true;
}









void big_pow_last_10_digits(big base, unsigned int exponent) {
	/*******************************************************************
	 * 1. If the exponent is 0, then turn the base into 1
	 ******************************************************************/
	if (exponent==0) {
		BIG_FREE(base);
		base = big_new_1_digit(1);
		return;
	}
	
	
	/*******************************************************************
	 * 2. If the base is zero, then do nothing
	 ******************************************************************/
	big zero = big_new_1_digit(0);
	if (big_equals(base, zero)) {
		BIG_FREE(zero);
		return;
	}
	
	
	/*******************************************************************
	 * 3. Otherwise, multiply 'base' by itself 'exponent' times
	 ******************************************************************/
	big multiplier = big_new(NULL);
	big_copy(base, multiplier);
	
	for (int e=1; e<exponent; e++) {
		big_multiply_last_10_digits(base, multiplier);
		if (big_equals(base, zero)) {
			BIG_FREE(zero);
			BIG_FREE(multiplier);
			return;
		}
	}
	
	
	BIG_FREE(zero);
	BIG_FREE(multiplier);
}






void big_multiply_last_10_digits(big base, big multiplier) {
	/*******************************************************************
	 * Case: Either input is zero
	 ******************************************************************/
	big zero = big_new_1_digit(0);
	if (big_equals(base, zero) || big_equals(multiplier, zero)) {
		BIG_FREE(base);
		big_copy(zero, base);
		return;
	}

	/*******************************************************************
	 * 1. Decompose the 'big' structs into int arrays
	 *    Set the longer one as 'a'
	 ******************************************************************/
	int* a = NULL;
	int* b = NULL;
	int a_len;
	int b_len;
	
	if (base->len > multiplier->len) {
		//p48
		if (base->len >= 10) {
			a = calloc(10, sizeof(int));
			a_len = 10;
			
			int index = 0;
			for (int i=base->len-10; i<base->len; i++) {
				a[index] = base->array[i];
				index++;
			}
		}
		
		//normal
		else {
			a = calloc(base->len, sizeof(int));
			a = memcpy(a, base->array, sizeof(int)*base->len);
			a_len = base->len;
		}
		
		//p48
		if (multiplier->len >= 10) {
			b = calloc(10, sizeof(int));
			b_len = 10;
			
			int index = 0;
			for (int i=multiplier->len-10; i<multiplier->len; i++) {
				b[index] = multiplier->array[i];
				index++;
			}
		}
		
		//normal
		else {
			b = calloc(multiplier->len, sizeof(int));
			b = memcpy(b, multiplier->array, sizeof(int)*multiplier->len);
			b_len = multiplier->len;
		}
	}
	
	else {
		//p48
		if (multiplier->len >= 10) {
			a = calloc(10, sizeof(int));
			a_len = 10;
			
			int index = 0;
			for (int i=multiplier->len-10; i<multiplier->len; i++) {
				a[index] = multiplier->array[i];
				index++;
			}
		}
		
		//normal
		else {
			a = calloc(multiplier->len, sizeof(int));
			a = memcpy(a, multiplier->array, sizeof(int)*multiplier->len);
			a_len = multiplier->len;
		}
		
		//p48
		if (base->len >= 10) {
			b = calloc(10, sizeof(int));
			b_len = 10;
			
			int index = 0;
			for (int i=base->len-10; i<base->len; i++) {
				b[index] = base->array[i];
				index++;
			}
		}
		
		//normal
		else {
			b = calloc(base->len, sizeof(int));
			b = memcpy(b, base->array, sizeof(int)*base->len);
			b_len = base->len;
		}
	}
	
	
	/*
	printf("a: ");
	for (int i=0; i<a_len; i++)
		printf("%d", a[i]);
	
	printf("\n");
	printf("b: ");
	for (int i=0; i<b_len; i++)
		printf("%d", b[i]);
	printf("\n\n");
	*/
	
	/*******************************************************************
	 * Case: If the last 10 digits of 'a' or 'b' are entirely zeros,
	 *       return zero
	 ******************************************************************/
	bool all_zeros = true;
	
	for (int i=0; i<a_len; i++)
		if (a[i]!=0) {
			all_zeros = false;
			break;
		}

	if (all_zeros) {
		free(a);
		free(b);
		BIG_FREE(base);
		base = big_new_1_digit(0);
		return;
	}

	all_zeros = true;

	for (int i=0; i<b_len; i++)
		if (b[i]!=0) {
			all_zeros = false;
			break;
		}
		
	
	if (all_zeros) {
		free(a);
		free(b);
		BIG_FREE(base);
		base = big_new_1_digit(0);
		return;
	}

	
	/*******************************************************************
	 * 2. Get the maximum length of the result
	 ******************************************************************/
	int result_len = a_len*2;
	
	
	
	/*******************************************************************
	 * 3. Prepare the 'lines' (the numbers that are written under the
	 *    line when doing multiplication on paper) grid
	 ******************************************************************/
	int lines_len = 0;
	int total_lines = b_len;
	int** lines = calloc(total_lines, sizeof(int*));
	
	for (int l=0; l<total_lines; l++)
		lines[l] = calloc(result_len, sizeof(int));
	
	
	
	
	/*******************************************************************
	 * 4. Perform paper multiplication
	 ******************************************************************/
	int trailing_zeros = 0;
	
	for (int b_index = b_len-1; b_index!=-1; b_index--) {
		
		int* list = calloc(result_len, sizeof(int));
		int list_len = trailing_zeros;
		
		for (int a_index = a_len-1; a_index!=-1; a_index--) {
			
			int a_int = a[a_index];
			int b_int = b[b_index];
			int product = a_int*b_int + list[list_len];
			
			
			/***********************************************************
			 * Put the result on the list
			 * 
			 * If the product is 2 digits long (i.e. a "carry" is to
			 * take place), then add the left digit into the next
			 * spot on the list
			 **********************************************************/
			if (product>9) {
				int left_digit = product/10;
				int right_digit = product - 10*(product/10);
				
				list[list_len] = right_digit;
				list[list_len+1] += left_digit;
			}
			else
				list[list_len] = product;
			
			list_len += 1;
						
			//if (list_len==10)
				//break;
			
		}
		

		/***************************************************************
		 * Print the list
		 **************************************************************/
		//for (int l=result_len-1; l>-1; l--)
			//printf("%d ", list[l]);
		//printf("\n");
		
		
		/***************************************************************
		 * Copy the list to the 'result' grid, in reversed order
		 **************************************************************/
		int lines_index = 0;
		for (int l=result_len-1; l>-1; l--) {
			lines[lines_len][lines_index] = list[l];
			lines_index += 1;
		}
		lines_len += 1;
		
		
		/***************************************************************
		 * Free the list and increment 'trailing_zeros' for the next
		 * line
		 **************************************************************/
		free(list);
		trailing_zeros += 1;
	}
	
	
	
	/*******************************************************************
	 * _. Print the 'lines' grid
	 ******************************************************************/
	//for (int l=0; l<lines_len; l++) {
		//for (int d=0; d<result_len; d++)
			//printf("%d ", lines[l][d]);
		//printf("\n");
	//}
	
	
	
	/*******************************************************************
	 * 5. Perform paper addition on 'lines'
	 ******************************************************************/
	int* result = calloc(result_len, sizeof(int));
	int result_index = result_len-1;
	
	for (int c=result_len-1; c>-1; c--) {
		for (int r=0; r<lines_len; r++) {
			result[result_index] += lines[r][c];
			
			/***********************************************************
			 * If the value at the current result_index is greater
			 * than 10, then perform a "carry over"
			 **********************************************************/
			if (c>0 && result[result_index] > 9) {
				int x = result[result_index];
				while (x%10 != 0)
					x--;
				
				result[result_index-1] += x/10;
				
				result[result_index] -= x;
			}
		}
		
		result_index--;
	}
	
	//puts("result");
	//for (int r=0; r<result_len; r++)
		//printf("%d ", result[r]);
		
		
	/*******************************************************************
	 * 6. Determine the new size of the base (count the leading zeros,
	 *    then subtract it from the result len)
	 ******************************************************************/
	int leading_zeros = 0;
	int starting_index;
	int new_len;
	
	for (int i=0; i<result_len; i++) {
		if (result[i]==0)
			leading_zeros += 1;
		else {
			starting_index = i;
			break;
		}
	}
	
	new_len = result_len - leading_zeros;
	
	/*******************************************************************
	 * 7. Save the result into 'base'
	 ******************************************************************/
	free(base->array);
	
	base->len = new_len;
	base->array = calloc(new_len, sizeof(int));
	
	int big_array_index = 0;
	for (int i=starting_index; i<result_len; i++) {
		base->array[big_array_index] = result[i];
		big_array_index += 1;
	}
	
	
	//Reduce the final result to 10 digits
	if (base->len > 10) {
		int left_index = 0;
		int right_index = (base->len)-10;
		
		while (left_index < 10) {
			base->array[left_index] = base->array[right_index];
			left_index++;
			right_index++;
		}
		
		base->array = (int*) realloc(base->array, sizeof(int)*10);
		base->len = 10;
		
	}
	
	
	/*******************************************************************
	 * 8. Free everything
	 ******************************************************************/
	free(a);
	free(b);
	free(result);
	
	for (int l=0; l<total_lines; l++)
		free(lines[l]);
	
	/*******************************************************************
	 * DEBUG: Attempting to free 'lines' when 'base' is a multiple of
	 *        10 causes a segfault
	 ******************************************************************/
	free(lines);
}





bool big_is_palindrome(big b) {
	/*******************************************************************
	 * Compare every left item with its equally-distanced right item.
	 * If they all match, the array is a palindrome.
	 ******************************************************************/
	int left = 0;
	int right = b->len-1;
	
	while (left <= right) {
		if (b->array[left] != b->array[right])
			return false;
		left++;
		right--;
	}
	
	return true;
}




big big_reverse(big b) {
	int len = b->len;
	
	big reverse = big_new(NULL);
	reverse->array = (int*) calloc(len, sizeof(int));
	reverse->len = len;
	
	int index = len-1;
	
	for (int i=0; i<len; i++) {
		reverse->array[index] = b->array[i];
		index--;
	}
	
	return reverse;
}

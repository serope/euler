/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 57
 **********************************************************************/
#include <stdio.h>
#include "euler_bignum.h"

int main() {
	/*******************************************************************
	 * After studying the examples on paper, one can eventually
	 * determine the following method for generating the next fraction
	 * in the sequence:
	 * 
	 *    1. Flip the fraction
	 *    2. Double the denominator
	 *    3. Subtract the denominator of the previous iteration's
	 *       fraction from the denominator 
	 *       (if this is the first iteration, subtract 1)
	 *    4. Add the denominator to the numerator
	 *
	 ******************************************************************/
	big top			= big_new("3");
	big bot			= big_new("2");
	big prev_bot	= big_new("1");
	big doubler		= big_new("2");
	int total		= 0;
	
	for (int i=0; i<1000; i++) {
		//1.
		big original_bot	= big_new(NULL);
		big flip			= big_new(NULL);
		big_copy(bot, original_bot);
		big_copy(top, flip);
		big_copy(bot, top);
		big_copy(flip, bot);
		
		//2.
		big_multiply(bot, doubler);
		
		//3.
		big_subtract(bot, prev_bot);
		
		//4.
		big_add(top, bot);
		
		//Check
		if (top->len > bot->len)
			total++;
		
		//Use this iteration's original denominator as the next
		//iteration's prev_bot
		big_copy(original_bot, prev_bot);
		
		//Free and continue
		BIG_FREE(original_bot);
		BIG_FREE(flip);
	}
	
	BIG_FREE(top);
	BIG_FREE(bot);
	BIG_FREE(prev_bot);
	BIG_FREE(doubler);
	printf("%d \n", total);
	return 0;
}

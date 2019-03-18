/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 33
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DIVISIBLE(x,y)		x%y==0

struct fraction {
	int top;
	int bottom;
};

struct fraction fraction_reduced(struct fraction f);
bool fractions_are_equal(struct fraction f1, struct fraction f2);


int main() {
	/*******************************************************************
	 * 1. Prepare the list of fractions
	 ******************************************************************/
	struct fraction* list = NULL;
	int list_len = 0;
	
	
	/*******************************************************************
	 * 2. For every fraction that can be formed whose top and bottom go
	 *    from 10 to 99...
	 ******************************************************************/
	for (int top=10; top<=99; top++) {
		for (int bottom=top+1; bottom<=99; bottom++) {
			/***********************************************************
			 * 2a. If the top is a factor of 10, then skip this loop 
			 *     because the problem considers this fraction a 
			 *     trivial one that doesn't count
			 **********************************************************/
			if (DIVISIBLE(top, 10))
				continue;
				
				
				
			/***********************************************************
			 * 2b. Get the digits of the current fraction, which is
			 *     in the form top/bottom (or t/b)
			 **********************************************************/
			int t_1st = top/10;
			int t_2nd = top - 10*t_1st;
			
			int b_1st = bottom/10;
			int b_2nd = bottom - 10*b_1st;
			
			

			/***********************************************************
			 * 2c. If the same digit appears in the top and bottom, 
			 *     remove it from the top and bottom, then check if
			 *     this new fraction is equal to the old one
			 * 
			 *     If it is, add the new fraction to the list
			 **********************************************************/
			struct fraction old;
			old.top = top;
			old.bottom = bottom;
			
			
			
			/***********************************************************
			 * Scenario A
			 * The top 1st digit matches the bottom 1st digit
			 **********************************************************/  
			if (t_1st==b_1st) {
				struct fraction new;
				new.top = t_2nd;
				new.bottom = b_2nd;
				
				if (fractions_are_equal(old, new)) {
					printf("%d/%d -> %d/%d \n", top, bottom, t_2nd, b_2nd);
					
					list = (struct fraction*) realloc(list, sizeof(struct fraction)*(list_len+1) );
					list[list_len] = new;
					list_len += 1;
				}
			}
			
			
			
			/***********************************************************
			 * Scenario B
			 * The top 1st digit matches the bottom 2nd digit
			 **********************************************************/  
			if (t_1st==b_2nd) {
				struct fraction new;
				new.top = t_2nd;
				new.bottom = b_1st;
				
				if (fractions_are_equal(old, new)) {
					printf("%d/%d -> %d/%d \n", top, bottom, t_2nd, b_1st);
					
					list = (struct fraction*) realloc(list, sizeof(struct fraction)*(list_len+1) );
					list[list_len] = new;
					list_len += 1;
				}
			}
			
			
			
			/***********************************************************
			 * Scenario C
			 * The top 2nd digit matches the bottom 2nd digit
			 **********************************************************/  
			if (t_2nd==b_2nd) {
				struct fraction new;
				new.top = t_1st;
				new.bottom = b_1st;
				
				if (fractions_are_equal(old, new)) {
					printf("%d/%d -> %d/%d \n", top, bottom, t_1st, b_1st);
					
					list = (struct fraction*) realloc(list, sizeof(struct fraction)*(list_len+1) );
					list[list_len] = new;
					list_len += 1;
				}
			}
			
			
				
			/***********************************************************
			 * Scenario D
			 * The top 2nd digit matches the bottom 1st digit
			 **********************************************************/  
			if (t_2nd==b_1st) {
				struct fraction new;
				new.top = t_1st;
				new.bottom = b_2nd;
				
				if (fractions_are_equal(old, new)) {
					printf("%d/%d -> %d/%d \n", top, bottom, t_1st, b_2nd);
					
					list = (struct fraction*) realloc(list, sizeof(struct fraction)*(list_len+1) );
					list[list_len] = new;
					list_len += 1;
				}
			}
		}
	}
	
	
	/*******************************************************************
	 * 3. Compute and print the product of all items on the list
	 ******************************************************************/
	struct fraction product;
	product.top = 1;
	product.bottom = 1;
	
	for (int l=0; l<list_len; l++) {
		product.top *= list[l].top;
		product.bottom *= list[l].bottom;
	}
	printf("\n");
	printf("product:      %d/%d \n", product.top, product.bottom);
	
	
	/*******************************************************************
	 * 4. Reduce and print the product
	 ******************************************************************/
	product = fraction_reduced(product);
	printf("reduced:      %d/%d \n", product.top, product.bottom);
	
	
	
	/*******************************************************************
	 * 5. Free memory and exit
	 ******************************************************************/
	free(list);
	return 0;
}





struct fraction fraction_reduced(struct fraction f) {
	int t = f.top;
	int b = f.bottom;
	int factor = 2;
	
	while (factor<=99) {
		if (DIVISIBLE(t, factor) && DIVISIBLE(b, factor)) {
			t = t/factor;
			b = b/factor;
			factor = 2;
		}
		else
			factor += 1;
	}
	
	struct fraction r;
	r.top = t;
	r.bottom = b;
	
	return r;
}





bool fractions_are_equal(struct fraction f1, struct fraction f2) {
	struct fraction r1 = fraction_reduced(f1);
	struct fraction r2 = fraction_reduced(f2);
	
	if (r1.top==r2.top && r1.bottom==r2.bottom)
		return true;
	
	return false;
}

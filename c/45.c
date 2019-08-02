/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 45
 **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int64_t		nth_pentagonal_number(int n);
int64_t		nth_hexagonal_number(int n);
int			final_digit_of(int64_t x);
bool		contains(int64_t* set, int64_t target, int len);


int main() {
	/*
	 * Declare lists of triangular, pengatonal, and hexagonal numbers
	 * (50k is sufficient for this problem)
	 */
	int limit = 50000;
	int64_t* tri_list = (int64_t*) calloc(limit, sizeof(int64_t));
	int64_t* pen_list = (int64_t*) calloc(limit, sizeof(int64_t));
	int64_t* hex_list = (int64_t*) calloc(limit, sizeof(int64_t));
	
	
	/*
	 * Build the lists
	 * 
	 * Note 1: As per the problem's description, the three lists may
	 *         start at n=286, n=166, and n=144, respectively
	 * 
	 * Note 2: All triangular numbers after n=286 seem to end with
	 *         either 0, 1, 3, 5, 6, or 8.
	 *         All pentagonal numbers after n=166 seem to end with
	 *         either 0, 1, 2, 5, 6, or 7.
	 *         All hexagonal numbers after n=144 seem to end with
	 *         either 0, 1, 3, 5, 6, or 8.
	 *         Therefore, the final answer likely ends with either 
	 *         0, 1, 3, 5, or 6.
	 ******************************************************************/
	int tri_index = 0;
	int pen_index = 0;
	int hex_index = 0;
	
	int tri_n = 286;
	int pen_n = 166;
	int hex_n = 144;
	
	//Triangular list
	int64_t t	= 40755;
	while (tri_index < limit) {
		t += tri_n;
		int d		= final_digit_of(t);
		if (d==0 || d==1 || d==3 || d==5 || d==6) {
			tri_list[tri_index] = t;
			tri_index++;
		}
		tri_n++;
	}
	
	//Pentagonal list
	while (pen_index < limit) {
		int64_t p	= nth_pentagonal_number(pen_n);
		int d		= final_digit_of(p);
		if (d==0 || d==1 || d==3 || d==5 || d==6) {
			pen_list[pen_index] = p;
			pen_index++;
		}
		pen_n++;
	}
	
	//Hexagonal list
	while (hex_index < limit) {
		int64_t h	= nth_hexagonal_number(hex_n);
		int d		= final_digit_of(h);
		if (d==0 || d==1 || d==3 || d==5 || d==6) {
			hex_list[hex_index] = h;
			hex_index++;
		}
		hex_n++;
	}
	
	

	//Search for a common number among all three lists
	int64_t number;
	bool solved = false;
	
	for (int t=0; t<limit; t++) {
		number = tri_list[t];
		if (contains(pen_list, number, limit)) {
			if (contains(hex_list, number, limit)) {
				solved = true;
				break;
			}
		}
	}
	
	
	//Print
	if (solved)
		printf("%lld \n", number);
	else {
		printf("Didn't find the answer. Try inreasing the limit. \n");
		printf("tri_list[%d] \t %lld \n", limit-1, tri_list[limit-1]);
		printf("pen_list[%d] \t %lld \n", limit-1, pen_list[limit-1]);
		printf("hex_list[%d] \t %lld \n", limit-1, hex_list[limit-1]);
	}
	
	//Free
	free(tri_list);
	free(pen_list);
	free(hex_list);
	return 0;
}





/*
 * Returns the final digit of x
 */
int final_digit_of(int64_t x) {
	if (x<=9)
		return x;
	for (int d=0; d<=9; d++)
		if ( (x-d)%10==0 )
			return d;
	return -1;
}



/*
 * Returns the nth pentagonal number as an int64
 */
int64_t nth_pentagonal_number(int n) {
	int64_t p = n;
	p = p*(3*n-1);
	p = p/2;
	return p;
}


/*
 * Returns the nth hexagonal number as an int64
 */
int64_t nth_hexagonal_number(int n) {
	int64_t h = 2*n-1;
	return h*n;
}




/*
 * Performs a binary search and returns whether target is in set
 */
bool contains(int64_t* set, int64_t target, int len) {
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

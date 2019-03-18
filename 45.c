/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 45
 **********************************************************************/
#include "euler.h"

int final_digit_of2(int64_t x);

int main() {
	/*******************************************************************
	 * 1. Prepare three lists: triangular numbers, pentagonal numbers,
	 *    and hexagonal numbers
	 *    (50k is sufficient for this problem)
	 ******************************************************************/
	int limit = 50000;
	int64_t* tri_list = (int64_t*) calloc(limit, sizeof(int64_t));
	int64_t* pen_list = (int64_t*) calloc(limit, sizeof(int64_t));
	int64_t* hex_list = (int64_t*) calloc(limit, sizeof(int64_t));
	
	
	
	/*******************************************************************
	 * 2. Build the lists
	 * 
	 *    Note 1: As per the problem's description, the three lists may
	 *            start at n=286, n=166, and n=144, respectively
	 * 
	 *    Note 2: All triangular numbers after n=286 seem to end with
	 *            either 0, 1, 3, 5, 6, or 8
	 * 
	 *            All pentagonal numbers after n=166 seem to end with
	 *            either 0, 1, 2, 5, 6, or 7
	 * 
	 *            All hexagonal numbers after n=144 seem to end with
	 *            either 0, 1, 3, 5, 6, or 8
	 * 
	 *            Therefore, the final answer likely ends with either 
	 *            0, 1, 3, 5, or 6
	 ******************************************************************/
	int tri_index = 0;
	int pen_index = 0;
	int hex_index = 0;
	
	int tri_n = 286;
	int pen_n = 166;
	int hex_n = 144;
	
	//Triangular list
	while (tri_index < limit) {
		int64_t t	= nth_triangular_number_int64(tri_n);
		int d		= final_digit_of(t);
		
		if (d==0 || d==1 || d==3 || d==5 || d==6) {
			tri_list[tri_index] = t;
			tri_index++;
		}
		
		tri_n++;
	}
	
	
	//Pentagonal list
	while (pen_index < limit) {
		int64_t p	= nth_pentagonal_number_int64(pen_n);
		int d		= final_digit_of(p);
		
		if (d==0 || d==1 || d==3 || d==5 || d==6) {
			pen_list[pen_index] = p;
			pen_index++;
		}
		
		pen_n++;
	}
	
	
	//Hexagonal list
	while (hex_index < limit) {
		int64_t h	= nth_hexagonal_number_int64(hex_n);
		int d		= final_digit_of(h);
		
		if (d==0 || d==1 || d==3 || d==5 || d==6) {
			hex_list[hex_index] = h;
			hex_index++;
		}
		
		hex_n++;
	}
	
	

	/*******************************************************************
	 * 3. Search all three lists for a matching number
	 ******************************************************************/
	int64_t number;
	bool solved = false;
	
	for (int t=0; t<limit; t++) {
		number = tri_list[t];
		
		if (contains_int64(pen_list, number, limit))
			if (contains_int64(hex_list, number, limit)) {
				solved = true;
				break;
			}
	}
	
	
	/*******************************************************************
	 * 4. Print, free memory, and exit
	 ******************************************************************/
	if (solved)
		printf("%lld \n", number);
	else {
		printf("Didn't find the answer. Try inreasing the limit. \n");
		printf("tri_list[%d] \t %lld \n", limit-1, tri_list[limit-1]);
		printf("pen_list[%d] \t %lld \n", limit-1, pen_list[limit-1]);
		printf("hex_list[%d] \t %lld \n", limit-1, hex_list[limit-1]);
	}
	
	free(tri_list);
	free(pen_list);
	free(hex_list);
	return 0;
}




int final_digit_of2(int64_t x) {
	if (x<=9)
		return x;
	
	int64_t y = x;
	
	while (y%10!=0)
		y--;
	return x-y;
}

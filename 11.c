/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 11
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Open 'grid.txt'
	 ******************************************************************/
	const char* filename = "11_grid.txt";
	FILE* txtfile = fopen(filename, "r");
	if (!txtfile) {
		printf("Unable to open %s \n", filename);
		return 1;
	}
	
	
	/*******************************************************************
	 * 2. Convert the contents of the textfile to a 2-dimensional
	 *    integer array
	 ******************************************************************/
	int grid[20][20];
	int row				= 0;
	int column			= 0;
	int first_digit		= -1;
	int second_digit	= -1;
	int number;
	int seek;
	
	while ((seek=getc(txtfile)) != EOF) {
		if (seek!=' ' && seek!='\n') {
			if (first_digit==-1)
				first_digit = CHAR_TO_INT(seek);
			
			else if (second_digit==-1) {
				second_digit = CHAR_TO_INT(seek);
				number = first_digit*10 + second_digit;
				grid[row][column] = number;
				column++;
				
				first_digit = -1;
				second_digit = -1;
			}
		}
		
		else if (seek=='\n') {
			column = 0;
			row++;
		}
	}
	fclose(txtfile);
	
	
	
	/*******************************************************************
	 * DEBUG: Print the grid
	 ******************************************************************/
	//for (int r=0; r<20; r++)
		//for (int c=0; c<20; c++)
			//printf("%d ", grid[r][c]);
	
	
	/*******************************************************************
	 * 3. Prepare variables
	 ******************************************************************/
	int
		a,
		b,
		c,
		d,
		index_a,
		index_b,
		index_c,
		index_d,
		row_index_a,
		row_index_b,
		row_index_c,
		row_index_d,
		col_index_a,
		col_index_b,
		col_index_c,
		col_index_d,
		product,
		largest_product = 0;

	
	/*******************************************************************
	 * 4. Check adjacent products in the left-right direction
	 ******************************************************************/
	for (int row=0; row<20; row++) {
		for (int col=0; col<20-4; col++) {
			index_a = col;
			index_b = col+1;
			index_c = col+2;
			index_d = col+3;
			
			a = grid[row][index_a];
			b = grid[row][index_b];
			c = grid[row][index_c];
			d = grid[row][index_d];
			
			product = a*b*c*d;
			
			
			if (product>largest_product) {
				largest_product = product;
				printf("%d-%d-%d-%d product: %d \n\n", a, b, c, d, product);
			}
		}
	}
	
	
	
	/*******************************************************************
	 * 5. Check adjacent products in the up-down direction
	 ******************************************************************/
	for (int row=0; row<20-4; row++) {
		for (int col=0; col<20-4; col++) {
			index_a = row;
			index_b = row+1;
			index_c = row+2;
			index_d = row+3;
			
			a = grid[index_a][col];
			b = grid[index_b][col];
			c = grid[index_c][col];
			d = grid[index_d][col];
			
			product = a*b*c*d;
			
			
			if (product>largest_product) {
				largest_product = product;
				printf("%d\n%d\n%d\n%d\nproduct: %d \n\n", a, b, c, d, product);
			}
		}
	}
	
	
	
	/*******************************************************************
	 * 6. Check adjacent products in back slash (\) diagonals
	 ******************************************************************/
	for (int row=0; row<20-4; row++) {
		for (int col=0; col<20-4; col++) {
			row_index_a = row;
			row_index_b = row+1;
			row_index_c = row+2;
			row_index_d = row+3;
			
			col_index_a = col;
			col_index_b = col+1;
			col_index_c = col+2;
			col_index_d = col+3;
			
			a = grid[row_index_a][col_index_a];
			b = grid[row_index_b][col_index_b];
			c = grid[row_index_c][col_index_c];
			d = grid[row_index_d][col_index_d];
			
			product = a*b*c*d;
		
			if (product>largest_product) {
				largest_product = product;
				printf("%d\n  %d\n    %d\n      %d\nproduct: %d \n\n", a, b, c, d, product);
			}
		}
	}

	
	
	
	
	/*******************************************************************
	 * 7. Check adjacent products in forward slash (/) diagonals
	 ******************************************************************/
	for (int row=3; row<20; row++) {
		for (int col=0; col<20-4; col++) {
			row_index_a = row;
			row_index_b = row-1;
			row_index_c = row-2;
			row_index_d = row-3;
			
			col_index_a = col;
			col_index_b = col+1;
			col_index_c = col+2;
			col_index_d = col+3;
			
			a = grid[row_index_a][col_index_a];
			b = grid[row_index_b][col_index_b];
			c = grid[row_index_c][col_index_c];
			d = grid[row_index_d][col_index_d];
			
			product = a*b*c*d;
		
			if (product>largest_product) {
				largest_product = product;
				printf("      %d\n    %d\n  %d\n%d\nproduct: %d \n\n", d, c, b, a, product);
			}
		}
	}
	
	return 0;
}

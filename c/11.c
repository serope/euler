/*
 * Project Euler
 * 11.c
 */
#include <stdio.h>
#include "array.h"
#include "euler.h"
#include "strings.h"

int max_prod_horiz(int** grid, int n);
int max_prod_verti(int** grid, int n);
int max_prod_fsdiag(int** grid, int n);
int max_prod_bsdiag(int** grid, int n);


int main() {
	// get grid
	int n = 20;
	int** grid = file_to_matrix("11_grid", n);
	
	// products in all 4 directions
	int prods[4];
	prods[0] = max_prod_horiz(grid, n);
	prods[1] = max_prod_verti(grid, n);
	prods[2] = max_prod_fsdiag(grid, n);
	prods[3] = max_prod_bsdiag(grid, n);
	
	// end
	arr_print_matrix(grid, n);
	arr_free_full(grid, n);
	int max_prod = arr_max(prods, 4);
	printf("%d \n", max_prod);
	return 0;
}


/**
 * Finds the largest product formed horizontally.
 * 
 * @param	grid	the grid to search
 * @param	n		the amount of rows and columns
 * @return			the largest product
 */
int max_prod_horiz(int** grid, int n) {
	int max = 0;
	for (int r=0; r<n; r++) {
		for (int c=0; c<n-4; c++) {
			int w = grid[r][c+0];
			int x = grid[r][c+1];
			int y = grid[r][c+2];
			int z = grid[r][c+3];
			int product = w*x*y*z;
			
			if (product > max)
				max = product;
		}
	}
	return max;
}


/**
 * Finds the largest product formed vertically.
 * 
 * @param	grid	the grid to search
 * @param	n		the amount of rows and columns
 * @return			the largest product
 */
int max_prod_verti(int** grid, int n) {
	int max = 0;
	for (int r=0; r<n-4; r++) {
		for (int c=0; c<n-4; c++) {
			int w = grid[r+0][c];
			int x = grid[r+1][c];
			int y = grid[r+2][c];
			int z = grid[r+3][c];
			int product = w*x*y*z;
			
			if (product > max)
				max = product;
		}
	}
	return max;
}


/**
 * Finds the largest product formed in forward-slash diagonals.
 * 
 * @param	grid	the grid to search
 * @param	n		the amount of rows and columns
 * @return			the largest product
 */
int max_prod_fsdiag(int** grid, int n) {
	int max = 0;
	for (int r=3; r<n; r++) {
		for (int c=0; c<n-4; c++) {
			int w = grid[r-0][c+0];
			int x = grid[r-1][c+1];
			int y = grid[r-2][c+2];
			int z = grid[r-3][c+3];
			int product = w*x*y*z;
			
			if (product > max)
				max = product;
		}
	}
	return max;
}


/**
 * Finds the largest product formed in backslash diagonals.
 * 
 * @param	grid	the grid to search
 * @param	n		the amount of rows and columns
 * @return			the largest product
 */
int max_prod_bsdiag(int** grid, int n) {
	int max = 0;
	for (int r=0; r<n-4; r++) {
		for (int c=0; c<n-4; c++) {
			int w = grid[r+0][c+0];
			int x = grid[r+1][c+1];
			int y = grid[r+2][c+2];
			int z = grid[r+3][c+3];
			int product = w*x*y*z;
			
			if (product > max)
				max = product;
		}
	}
	return max;
}

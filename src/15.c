/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 14
 * 
 * Execution speed: VERY VERY BAD ~45m
 * 
 * This solution solves the problem by bruce force via DFS (depth-first
 * search).
 * 
 * DIMENSION		Paths
 * 2				6
 * 5				252
 * 10				184756
 * 15				155 117 520
 * 20				137 846 528 820
 **********************************************************************/
#include <stdio.h>
#define DIMENSION 20

struct point new_point(struct point* down, struct point* right);
void traverse(struct point* start, long int* total_paths_ptr);


struct point {
	struct point* right;
	struct point* down;
};




int main() {
	/*******************************************************************
	 * 1. Initialize the grid.
	 ******************************************************************/
	const int rows		= DIMENSION+1;
	const int columns	= DIMENSION+1;
	struct point grid[rows][columns];
			
			
	
	/*******************************************************************
	 * 2. Set every row and column except the last ones.
	 ******************************************************************/
	for (int r=0; r<DIMENSION; r++)
		for (int c=0; c<DIMENSION; c++)
			grid[r][c] = new_point(&grid[r+1][c], &grid[r][c+1]);
			
			
			
	/*******************************************************************
	 * 3. Set the last row.
	 ******************************************************************/
	for (int c=0; c<DIMENSION; c++)
		grid[DIMENSION][c] = new_point(NULL, &grid[DIMENSION][c+1]);
		
		
		
	/*******************************************************************
	 * 4. Set the last column.
	 ******************************************************************/
	for (int r=0; r<DIMENSION; r++)
		grid[r][DIMENSION] = new_point(&grid[r+1][DIMENSION], NULL);

	
	/*******************************************************************
	 * 5. Set the endpoint (bottom-right corner).
	 ******************************************************************/
	grid[DIMENSION][DIMENSION] = new_point(NULL, NULL);
	
	
	/*******************************************************************
	 * 6. Traverse the graph via recursive DFS.
	 *    Whenever the endpoint is reached, increase 'paths' by 1.
	 ******************************************************************/
	long int paths = 0;
		
	traverse(&grid[0][0], &paths);
	
	printf("%ld \n", paths);
	
	return 0;
}





struct point new_point(struct point* down, struct point* right) {
	struct point l;
	l.right = right;
	l.down = down;
	return l;
}




void traverse(struct point* start, long int* total_paths_ptr) {
	if (start->right!=NULL)
		traverse(start->right, total_paths_ptr);
	
	if (start->down!=NULL)
		traverse(start->down, total_paths_ptr);
		
	if (start->right==NULL && start->down==NULL)
		*total_paths_ptr += 1;
}

/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 18
 **********************************************************************/
#include "euler.h"

struct node {
	int item;
	struct node* left;
	struct node* right;
};

struct node new_node(int i, struct node* l, struct node* r);
void dfs(struct node* start, int* path_len, int* longest_path_len);



int main() {
	/*******************************************************************
	 * 1. Open the file
	 ******************************************************************/
	const char* filename = "18_triangle.txt";
	FILE* txtfile = fopen(filename, "r");
	if (!txtfile) {
		printf("Unable to open %s \n", filename);
		exit(EXIT_FAILURE);
	}
	
	/*******************************************************************
	 * 2. Convert the file's contents into a list of integers, and
	 *    count how many integers the longest row has
	 * 
	 *    Note: Each integer is written as 2 digits (e.g. 04)
	 ******************************************************************/
	int* list			= NULL;
	int list_len		= 0;
	int row_len			= 0;
	int longest			= 0;
	int current;
	bool set_1st_digit	= false;
	bool set_2nd_digit	= false;
	
	while (true) {
		//Get the next char in the file
		int seek = getc(txtfile);
		
		//Break if it's the end
		if (seek==EOF)
			break;
		
		//If it's a space or newline, then the item is complete
		else if (seek==' ' || seek=='\n') {
			list = append(list, current, &list_len);
			set_1st_digit = false;
			set_2nd_digit = false;
			
			//Count how many items were in this row
			if (seek=='\n') {
				if (row_len > longest)
					longest = row_len;
				row_len = 0;
			}
		}
		
		//If it's a digit, then add it to the current item
		else if (!set_1st_digit) {
			current = CHAR_TO_INT(seek);
			current *= 10;
			set_1st_digit = true;
		}
		else if (!set_2nd_digit) {
			current += CHAR_TO_INT(seek);
			set_2nd_digit = true;
			row_len++;
		}
	}
	fclose(txtfile);
	

	/*******************************************************************
	 * 3. Convert the list into a grid
	 *    (this will make it easier to draw the tree later)
	 ******************************************************************/
	int grid[longest][longest];
	int row				= 0;
	int column			= 0;
	row_len				= 1;
	
	for (int i=0; i<list_len; i++) {
		//Append the current integer
		grid[row][column] = list[i];
		column++;
		
		//When the current row is finished, move down to the next one
		if (column==row_len) {
			column = 0;
			row++;
			row_len++;
		}
	}

	
	/*******************************************************************
	 * 4. Convert the grid into a tree
	 ******************************************************************/
	struct node tree[longest][longest];
	int final_row = longest-1;
	
	for (int r=0; r<longest; r++)
		for (int c=0; c<r+1; c++) {
			struct node* left;
			struct node* right;
			
			//If this is the final row, then the children are null
			if (r==final_row) {
				left = NULL;
				right = NULL;
			}
			
			//Otherwise, the children are the two nodes below this one
			else {
				left = &tree[r+1][c];
				right = &tree[r+1][c+1];
			}
			
			//Set the node
			tree[r][c] = new_node(grid[r][c], left, right);
	}
	
	/*******************************************************************
	 * 5. DFS
	 ******************************************************************/
	struct node* head			= &tree[0][0];
	int path_len				= 0;
	int longest_path_len		= 0;
	
	dfs(head, &path_len, &longest_path_len);
	
	
	/*******************************************************************
	 * 6. Print info and exit
	 ******************************************************************/
	printf("list: {");
	for (int i=0; i<list_len; i++)
		printf("%d ", list[i]);
	printf("\b} \n");
	
	puts("grid:\n");
	for (int i=0; i<longest; i++)
		for (int j=0; j<longest; j++)
			printf("grid[%d][%d] \t %d \n", i, j, grid[i][j]);
	
	printf("list_len         \t %d \n", list_len);
	printf("longest          \t %d \n", longest);
	printf("path_len         \t %d \n", path_len);
	printf("longest_path_len \t %d \n", longest_path_len);
	
	exit(EXIT_SUCCESS);
}





struct node new_node(int i, struct node* l, struct node* r) {
	struct node n;
	n.item		= i;
	n.left		= l;
	n.right		= r;
	return n;
}





void dfs(struct node* start, int* path_len, int* longest_path_len) {
	*path_len += start->item;
	
	if (start->right!=NULL) {
		dfs(start->right, path_len, longest_path_len);
		*path_len -= start->right->item;
	}
	
	
	if (start->left!=NULL) {
		dfs(start->left, path_len, longest_path_len);
		*path_len -= start->left->item;
	}
	
	
	if (start->right==NULL && start->left==NULL)
		if (*path_len > *longest_path_len)
			*longest_path_len = *path_len;
}

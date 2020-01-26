/*
 * Project Euler
 * 18.c
 */
#include <stdio.h>
#include "array.h"
#include "euler.h"
#include "strings.h"

struct node {
	int item;
	struct node* left;
	struct node* right;
};


struct node new_node(int i, struct node* l, struct node* r);
void dfs(struct node* start, int* path_len, int* longest_path_len);


int main() {
	// read
	int n = 15;
	int** matrix = file_to_matrix("18_triangle", n);
	
	// matrix -> tree
	struct node tree[n][n];
	int final_row = n-1;
	for (int r=0; r<n; r++)
		for (int c=0; c<r+1; c++) {
			struct node* left;
			struct node* right;
			
			if (r == final_row) {
				left = NULL;
				right = NULL;
			}
			else {
				left = &tree[r+1][c];
				right = &tree[r+1][c+1];
			}
			tree[r][c] = new_node(matrix[r][c], left, right);
	}
	
	// solve
	struct node* head		= &tree[0][0];
	int path_len			= 0;
	int longest_path_len	= 0;
	dfs(head, &path_len, &longest_path_len);
	
	// end
	arr_print_matrix(matrix, n);
	arr_free_full(matrix, n);
	printf("longest_path_len %d \n", longest_path_len);
	return 0;
}


/**
 * Creates a new node for a binary tree.
 * 
 * @param	i	the node's internal weight
 * @param	l	left child
 * @param	r	right child
 * @return		a new node
 */
struct node new_node(int i, struct node* l, struct node* r) {
	struct node n;
	n.item		= i;
	n.left		= l;
	n.right		= r;
	return n;
}


/**
 * Finds the longest path in a weighted binary tree via recursive
 * depth-first search.
 * 
 * @param	start				the tree's root
 * @param	path_len			a pointer to an integer that holds the 
 * 								length of the current path
 * @param	longest_path_len	a pointer to an integer that holds the
 * 								length of the longest path
 */
void dfs(struct node* start, int* path_len, int* longest_path_len) {
	*path_len += start->item;
	if (start->right) {
		dfs(start->right, path_len, longest_path_len);
		*path_len -= start->right->item;
	}
	if (start->left) {
		dfs(start->left, path_len, longest_path_len);
		*path_len -= start->left->item;
	}
	if (!start->right && !start->left)
		if (*path_len > *longest_path_len)
			*longest_path_len = *path_len;
}

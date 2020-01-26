/*
 * Project Euler
 * 14.c
 */
#include <stdio.h>
#include <stdlib.h>

int	collatz_sequence_len(int starting_number, int* list, int list_len);


int main() {
	/* 
	 * Create array in which every index is a starting point and every
	 * value is that starting point's Collatz sequence length.
	 * e.g. lengths[13] = 10
	 */
	int limit = 1000000;
	int* lengths = calloc(limit, sizeof(int));
	lengths[13] = 10;
	
	// find longest
	int longest_starting_number = 13;
	int longest_length = 10;
	for (int x=1; x<limit; x++) {
		int len = collatz_sequence_len(x, lengths, limit);
		if (len > longest_length) {
			longest_starting_number = x;
			longest_length = len;
		}
	}
	
	// end
	printf("%d creates a Collatz sequence of length %d \n",
												longest_starting_number,
												longest_length);
	free(lengths);
	return 0;
}


/**
 * Computes the length of a Collatz sequence.
 * 
 * @param	starting_number		the Collatz sequence start
 * @param	list				a list of Collatz sequence lengths
 * @param	list_len			the list's length
 * @return						this starting point's sequence's length
 */
int collatz_sequence_len(int starting_number, int* list, int list_len) {
	int64_t x = starting_number;
	int length = 1;
	
	while (x>1) {
		// continue sequence
		if (x%2==0)
			x /= 2;
		else
			x = 3*x+1;
		
		/*
		 * Reference the 'lengths' array to see if the current value
		 * of 'x' has been previously used to create a sequence. If
		 * so, add this previously-acquired length to 'length' and
		 * break early.
		 */
		if (x<list_len && list[x]>0) {
			length += list[x];
			break;
		}
		else
			length++;
	}
	
	// end
	list[starting_number] = length;
	return length;
}

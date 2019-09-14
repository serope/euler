/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 54
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"

#define IS_RANK(x)	x>=1 && x<=14
#define IS_SUIT(x)	x==CLUBS || x==DIAMONDS || x==HEARTS || x==SPADES

struct hand     new_hand();
int             char_to_poker_int(char c);
int             get_hand_type(struct hand h);
int             get_highest_card(struct hand h, int hand_type);
bool            beats(struct hand player1, struct hand player2);
void            print_hand(struct hand h);


enum {
	//Royal ranks
	JACK=11, QUEEN, KING, ACE,
	
	//Hand types, in order of strength
	HIGHCARD, PAIR, TWOPAIR, TRIPS, STRAIGHT, FLUSH, FULLHOUSE, QUADS, STRAIGHTFLUSH, ROYALFLUSH,
	
	//Suits
	CLUBS, DIAMONDS, HEARTS, SPADES
};


struct hand {
	int* ranks;
	int* suits;
};






int main() {
	/*******************************************************************
	 * 1. Open the file
	 ******************************************************************/
	const char* filename = "54_poker.txt";
	FILE* txtfile = fopen(filename, "r");
	if (!txtfile) {
		printf("Unable to open %s \n", filename);
		return 1;
	}
	
	
	
	/*******************************************************************
	 * 2. Convert the contents of the textfile into hands and evaluate
	 *    them
	 ******************************************************************/
	int seek;
	int wins = 0;
	int current_game = 1;
	
	struct hand player1 = new_hand();
	struct hand player2 = new_hand();
	int ranks_len = 0;
	int suits_len = 0;
	int current_player = 1;
	
	//For every character 'x' in the textfile...
	while ((seek=getc(txtfile)) != EOF) {
		int x = char_to_poker_int(seek);
		
		if (x==-1)
			continue;
		
		//Add 'x' to player 1's hand
		if (current_player==1) {
			if (IS_RANK(x))
				player1.ranks = append(player1.ranks, x, &ranks_len);
				
			else {
				player1.suits = append(player1.suits, x, &suits_len);
				
				//After 5 cards have been added to player 1's hand,
				//print the hand, reset the length values and switch
				//to player 2
				if (suits_len==5) {
					printf("%d. \t", current_game);
					current_game++;
					
					print_hand(player1);
					printf("    ");
					
					ranks_len = 0;
					suits_len = 0;
					current_player = 2;
				}
			}
		}
		
		//Add 'x' to player 2's hand
		else if (current_player==2) {
			if (IS_RANK(x))
				player2.ranks = append(player2.ranks, x, &ranks_len);
			
			else {
				player2.suits = append(player2.suits, x, &suits_len);
				
				//After 5 cards have been added to player 2's hand,
				//both players' hands are pit against each other.
				//Then, free everything and start over.
				if (suits_len==5) {
					print_hand(player2);
					
					if (beats(player1, player2)) {
						wins++;
						printf("    %d win", wins);
						if (wins>1)
							printf("s");
					}
					printf("\n");
					
					free(player1.ranks);
					free(player1.suits);
					player1 = new_hand();
					
					free(player2.ranks);
					free(player2.suits);
					player2 = new_hand();
					
					ranks_len = 0;
					suits_len = 0;
					current_player = 1;
				}
			}
		}
	}


	/*******************************************************************
	 * 3. Print, cleanup, and exit
	 ******************************************************************/
	printf("\nPlayer 1 won %d games! \n", wins);
	fclose(txtfile);
	return 0;
}





void print_hand(struct hand h) {
	for (int c=0; c<5; c++) {
		int rank = h.ranks[c];
		int suit = h.suits[c];
		
		switch (rank) {
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:			printf("%d", rank); break;
			case 10:		printf("T"); break;
			case JACK:		printf("J"); break;
			case QUEEN:		printf("Q"); break;
			case KING:		printf("K"); break;
			case ACE:		printf("A"); break;
		}
		
		switch (suit) {
			case CLUBS:		printf("C"); break;
			case DIAMONDS:	printf("D"); break;
			case HEARTS:	printf("H"); break;
			case SPADES:	printf("S"); break;
		}
		
		printf(" ");
	}
}



struct hand new_hand() {
	struct hand h;
	h.ranks = NULL;
	h.suits = NULL;
	return h;
}



int get_hand_type(struct hand h) {
	//1. Bubble sort the hand
	for (int i=0; i<5; i++)
		for (int j=0; j<4; j++)
			if (h.ranks[j]>h.ranks[j+1]) {
				int placeholder	= h.ranks[j];
				h.ranks[j]		= h.ranks[j+1];
				h.ranks[j+1]	= placeholder;
			}
	
	
	//2. Check flush status
	bool is_flush = false;
	if (h.suits[0]==h.suits[1] && h.suits[1]==h.suits[2] && h.suits[2]==h.suits[3] && h.suits[3]==h.suits[4])
		is_flush = true;
	
	
	//3. Check straight status
	bool is_straight = false;
	if (h.ranks[0]==h.ranks[1]-1 && h.ranks[1]==h.ranks[2]-1 && h.ranks[2]==h.ranks[3]-1 && h.ranks[3]==h.ranks[4]-1)
		is_straight = true;
	
	
	//4. Check royal flush status
	bool is_royal_flush = false;
	if (is_flush && is_straight && h.ranks[4]==ACE)
		is_royal_flush = true;
	
	
	//5. Return flush, straight, straight flush, or royal flush
	if (is_royal_flush)
		return ROYALFLUSH;
	else if (is_flush && is_straight)
		return STRAIGHTFLUSH;
	else if (is_flush)
		return FLUSH;
	else if (is_straight)
		return STRAIGHT;
	
	
	//6. Count how many distinct card ranks are in the hand
	int* distinct = NULL;
	int distinct_len = 0;
	
	for (int i=0; i<5; i++)
		if (!contains(distinct, h.ranks[i], distinct_len))
			distinct = append(distinct, h.ranks[i], &distinct_len);
	free(distinct);
	
	//7. Return quads or full house
	if (distinct_len==2) {
		//Quads
		if (h.ranks[0]==h.ranks[1] && h.ranks[1]==h.ranks[2] && h.ranks[2]==h.ranks[3])
			return QUADS;
		else if (h.ranks[1]==h.ranks[2] && h.ranks[2]==h.ranks[3] && h.ranks[3]==h.ranks[4])
			return QUADS;
		
		//Full house
		if (h.ranks[0]==h.ranks[1] && h.ranks[1]==h.ranks[2])
			return FULLHOUSE;
		else if (h.ranks[2]==h.ranks[3] && h.ranks[3]==h.ranks[4])
			return FULLHOUSE;
	}
	
	
	//8. Return trips or two pair
	else if (distinct_len==3) {
		//Trips
		if (h.ranks[0]==h.ranks[1] && h.ranks[1]==h.ranks[2])
			return TRIPS;
		else if (h.ranks[1]==h.ranks[2] && h.ranks[1]==h.ranks[2])
			return TRIPS;
		else if (h.ranks[2]==h.ranks[3] && h.ranks[3]==h.ranks[4])
			return TRIPS;
		
		//Two pair
		else
			return TWOPAIR;
	}
	
	
	//9. Return one pair
	if (distinct_len==4) {
		if (h.ranks[0]==h.ranks[1])
			return PAIR;
		else if (h.ranks[1]==h.ranks[2])
			return PAIR;
		else if (h.ranks[2]==h.ranks[3])
			return PAIR;
		else if (h.ranks[3]==h.ranks[4])
			return PAIR;
	}
	
	
	//10. Return high card
	return HIGHCARD;
}




bool beats(struct hand player1, struct hand player2) {
	int player1_hand_type = get_hand_type(player1);
	int player1_highest_card = get_highest_card(player1, player1_hand_type);
	
	int player2_hand_type = get_hand_type(player2);
	int player2_highest_card = get_highest_card(player2, player2_hand_type);
	
	//If P1's hand type beats P2's
	if (player1_hand_type > player2_hand_type)
		return true;
	
	//If P2's hand type beats P1's
	else if (player1_hand_type < player2_hand_type)
		return false;
	
	//If P1 and P2 have the same hand type
	else if (player1_highest_card > player2_highest_card)
		return true;
		
	return false;
}





int char_to_poker_int(char c) {
	switch (c) {
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'T': return 10;
		case 'J': return JACK;
		case 'Q': return QUEEN;
		case 'K': return KING;
		case 'A': return ACE;
		case 'C': return CLUBS;
		case 'D': return DIAMONDS;
		case 'H': return HEARTS;
		case 'S': return SPADES;
	}
	return -1;
}








int get_highest_card(struct hand h, int hand_type) {
	//Bubble sort the hand's ranks
	for (int i=0; i<5; i++)
		for (int j=0; j<4; j++)
			if (h.ranks[j]>h.ranks[j+1]) {
				int placeholder	= h.ranks[j];
				h.ranks[j]		= h.ranks[j+1];
				h.ranks[j+1]	= placeholder;
			}
	
	
	//In these hand types, the final card is the highest
	if (hand_type==ROYALFLUSH || hand_type==STRAIGHTFLUSH || hand_type==STRAIGHT || hand_type==FLUSH || hand_type==HIGHCARD)
		return h.ranks[4];


	//Quads
	else if (hand_type==QUADS) {
		if (h.ranks[0]==h.ranks[1])
			return h.ranks[0];
		else
			return h.ranks[1];
	}
	
	//Full house
	else if (hand_type==FULLHOUSE) {
		if (h.ranks[0]==h.ranks[1] && h.ranks[1]==h.ranks[2])
			return h.ranks[0];
		else
			return h.ranks[4];
	}
	
	//Trips
	else if (hand_type==TRIPS) {
		if (h.ranks[0]==h.ranks[1] && h.ranks[1]==h.ranks[2])
			return h.ranks[0];
		else if (h.ranks[1]==h.ranks[2] && h.ranks[2]==h.ranks[3])
			return h.ranks[1];
		else
			return h.ranks[4];
	}
	
	//Two pair (when sorted, the highest card is always in index 3)
	else if (hand_type==TWOPAIR)
		return h.ranks[3];
	
	//Pair
	else if (hand_type==PAIR) {
		if (h.ranks[0]==h.ranks[1])
			return h.ranks[0];
		else if (h.ranks[1]==h.ranks[2])
			return h.ranks[1];
		else if (h.ranks[2]==h.ranks[3])
			return h.ranks[2];
		else
			return h.ranks[3];
	}
	
	return -1;
}

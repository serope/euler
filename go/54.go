// Project Euler
// 54.go
package main

import (
	"fmt"
	"strings"
	"io/ioutil"
)

const (
	// face cards
	A = 14
	K = 13
	Q = 12
	J = 11
	
	// hand types in descending order of strength
	ROYALFLUSH = iota*-1
	STRAIGHTFLUSH
	QUADS
	FULLHOUSE
	FLUSH
	STRAIGHT
	TRIPS
	TWOPAIR
	ONEPAIR
	HIGHCARD
	
	// suits
	C
	D
	H
	S
)

type Card struct {
	rank int
	suit int
}

type Hand []Card



func main() {
	// read each player's hands
	player1, player2, err := readPokerFile("54_poker")
	if err!=nil {
		panic(err)
	}
	
	// count player 1's wins
	wins := 0
	for i:=0; i<len(player1); i++ {
		hand1 := player1[i]
		hand2 := player2[i]
		fmt.Printf("%d \t %v \t %v \t", i, hand1, hand2)
		if hand1.beats(hand2) {
			wins++
			fmt.Print("wins: ", wins)
		}
		fmt.Print("\n")
	}
	fmt.Println(wins)
}


// readPokerFile reads the given file and returns two slices representing
// all of player 1's hands and all of player 2's hands.
func readPokerFile(filename string) ([]Hand, []Hand, error) {
	// read
	file, err := ioutil.ReadFile(filename)
	if err != nil {
		return nil, nil, err
	}
	text := strings.Split(string(file), "\n")
	i := len(text)-1
	text = append(text[:i], text[i+1:]...) // remove final line (EOF)
	
	// parse
	var player1, player2 []Hand
	for _, line := range(text) {
		hand1, hand2 := parseShowdown(line)
		player1 = append(player1, hand1)
		player2 = append(player2, hand2)
	}
	return player1, player2, nil
}

// parseShowdown takes a string like "8C TS KC 9H 4S 7D 2S 5D 3S AC" and
// returns two hands.
func parseShowdown(line string) (Hand, Hand) {
	split := strings.Split(line, " ")
	var hand1, hand2 Hand
	for i, str := range(split) {
		card := parseCard(str)
		if i<5 {
			hand1 = append(hand1, card)
		} else {
			hand2 = append(hand2, card)
		}
	}
	return hand1, hand2
}

// parseCard takes a string like "5H" and returns an equivalent Card.
func parseCard(str string) Card {
	rank := parseByte(str[0])
	suit := parseByte(str[1])
	return Card{rank, suit}
}

// parseByte takes a byte/char and returns the appropriate poker value.
func parseByte(b byte) int {
	switch b {
		case '1':	return 1
		case '2':	return 2
		case '3':	return 3
		case '4':	return 4
		case '5':	return 5
		case '6':	return 6
		case '7':	return 7
		case '8':	return 8
		case '9':	return 9
		case 'T':	return 10
		case 'J':	return J
		case 'Q':	return Q
		case 'K':	return K
		case 'A':	return A
		case 'C':	return C
		case 'D':	return D
		case 'H':	return H
		case 'S':	return S
	}
	return -1
}

// intToStr returns the appropriate poker symbol for the given const.
func intToStr(i int) string {
	switch i {
		case 1:		return "1"
		case 2:		return "2"
		case 3:		return "3"
		case 4:		return "4"
		case 5:		return "5"
		case 6:		return "6"
		case 7:		return "7"
		case 8:		return "8"
		case 9:		return "9"
		case 10:	return "T"
		case J:		return "J"
		case Q:		return "Q"
		case K:		return "K"
		case A:		return "A"
		case C:		return "♣"
		case D:		return "♦"
		case H:		return "♥"
		case S:		return "♠"
	}
	return "-"
}

// String returns a printable form of the hand.
func (h Hand) String() string {
	str := ""
	for _, card := range(h) {
		str += intToStr(card.rank) + intToStr(card.suit) + " "
	}
	return str
}

// isFlush returns true if every card in the hand has the same suit.
func (h Hand) isFlush() bool {
	suit := h[0].suit
	for i:=1; i<5; i++ {
		card := h[i]
		if card.suit != suit {
			return false
		}
	}
	return true
}

// sort performs a bubble sort on the hand (slices are reference types,
// so nothing need be returned).
func (h Hand) sort() {
	for i:=0; i<len(h)-1; i++ {
		for j:=i+1; j<len(h); j++ {
			if h[i].rank > h[j].rank {
				tmp := h[i]
				h[i] = h[j]
				h[j] = tmp
			}
		}
	}
}

// isStraight returns true if the hand has consecutive ranks.
func (h Hand) isStraight() bool {
	for i:=0; i<4; i++ {
		cardA := h[i]
		cardB := h[i+1]
		if cardA.rank != cardB.rank-1 {
			return false
		}
	}
	return true
}

// isRoyalFlush returns true if the hand is a royal flush (a straight
// flush whose highest card is A).
func (h Hand) isRoyalFlush() bool {
	return h.isStraight() && h.isFlush() && h[4].rank == A
}

// isStraightFlush returns true if the hand is a straight flush.
func (h Hand) isStraightFlush() bool {
	return h.isStraight() && h.isFlush() && h[4].rank != A
}

// isQuads returns true if the hand is a four-of-a-kind (either the first
// 4 cards or last 4 cards have the same rank).
func (h Hand) isQuads() bool {
	if sameRanks(h[0:4]) || sameRanks(h[1:5]) {
		return true
	}
	return false
}

// isFullHouse returns true if the hand is a full house (it has both a
// three-of-a-kind and a pair).
func (h Hand) isFullHouse() bool {
	if sameRanks(h[0:3]) && sameRanks(h[3:5]) {			// AAABB
		return true
	} else if sameRanks(h[0:2]) && sameRanks(h[2:5]) {	// BBAAA
		return true
	}
	return false
}

// isTrips returns true if the hand is a three-of-a-kind (either the
// first 3 cards, middle 3 cards, or last 3 cards have the same rank).
func (h Hand) isTrips() bool {
	if sameRanks(h[0:3]) || sameRanks(h[1:4]) || sameRanks(h[2:5]) {
		return true
	}
	return false
}

// isTwoPair returns true if the hand is a two pair.
func (h Hand) isTwoPair() bool {
	if sameRanks(h[0:2]) && sameRanks(h[2:4]) {			// AABBc
		return true
	} else if sameRanks(h[0:2]) && sameRanks(h[3:5]) {	// AAcBB
		return true
	} else if sameRanks(h[1:3]) && sameRanks(h[3:5]) {	// cAABB
		return true
	}
	return false
}

// isOnePair returns true if the hand is a one pair.
func (h Hand) isOnePair() bool {
	for i:=0; i<len(h)-1; i++ {
		if h[i].rank == h[i+1].rank {
			return true
		}
	}
	return false
}

// sameRanks returns true if every card in the given hand is of the same
// rank.
func sameRanks(h Hand) bool {
	for i:=0; i<len(h)-1; i++ {
		if h[i].rank != h[i+1].rank {
			return false
		}
	}
	return true
}

// eval evaluates the hand and returns its hand type and highest card.
func (h Hand) eval() (int, Card) {
	h.sort()
	var handType int
	var highest Card
	
	switch {
		case h.isRoyalFlush():
			handType = ROYALFLUSH
			highest = h[4]
		case h.isStraightFlush():
			handType = STRAIGHTFLUSH
			highest = h[4]
		case h.isQuads():
			handType = QUADS
			highest = h[2]
		case h.isFullHouse():
			handType = FULLHOUSE
			highest = h[2]
		case h.isFlush():
			handType = FLUSH
			highest = h[4]
		case h.isStraight():
			handType = STRAIGHT
			highest = h[4]
		case h.isTrips():
			handType = TRIPS
			highest = h[2]
		case h.isTwoPair():
			handType = TWOPAIR
			highest = h[3]
		case h.isOnePair():
			handType = ONEPAIR
			for i:=0; i<len(h)-1; i++ {
				if h[i].rank == h[i+1].rank {
					highest = h[i]
					break
				}
			}
		default:
			handType = HIGHCARD
			highest = max(h)
	}
	return handType, highest
}

// max returns the highest-valued card from a hand.
func max(h Hand) Card {
	m := h[0]
	for _, card := range(h) {
		if card.rank > m.rank {
			m = card
		}
	}
	return m
}


// beats returns true if player 1's hand beats player 2's hand.
func (player1 Hand) beats(player2 Hand) bool {
	player1handType, player1highestCard := player1.eval()
	player2handType, player2highestCard := player2.eval()
	if player1handType > player2handType {
		return true
	} else if player1handType < player2handType {
		return false
	}
	return player1highestCard.rank > player2highestCard.rank // tie break
}

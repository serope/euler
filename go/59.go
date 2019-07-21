/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 59
 **********************************************************************/
package main

import (
	"fmt"
	"strings"
	"strconv"
	"io/ioutil"
)


func main() {
	//Load text file
	file, err := ioutil.ReadFile("59_message.txt")
	if err!=nil {
		fmt.Println(err)
		return
	}
	
	//Separate by commas
	sep := strings.Split(string(file), ",")
	
	//Convert to integer slice
	var messageOrig []int
	for _, symbol := range(sep) {
		integer, err := strconv.Atoi(symbol)
		if err!=nil {
			fmt.Println(err)
			return
		} else {
			messageOrig = append(messageOrig, integer)
		}
	}
	
	//Begin cipher
	for i:='a'; i<='z'; i++ {
		for j:='a'; j<='z'; j++ {
			for k:='a'; k<='z'; k++ {
				//Get binary sequences of current cipher combination
				//e.g. 'a','b','c' -> 97,98,99 -> 1100001,1100010,01100011
				ciphers := [][]bool {binarySeq(int(i)), binarySeq(int(j)), binarySeq(int(k))}
				cipherIndex := 0
				
				//Declare slice for storing current attempt
				var messageCiphered []byte
				
				//For each integer in the original message...
				for _, integer := range(messageOrig) {
					//Convert to a binary
					binary := binarySeq(integer)
					
					//XOR the binary with the current cipher combo
					xord := xor(binary, ciphers[cipherIndex])
					
					//Increment selected cipher
					cipherIndex++
					if cipherIndex==3 {
						cipherIndex = 0
					}
					
					//Convert back to integer (ASCII code)
					ascii := binToInt(xord)
					
					//Append to messageCiphered
					messageCiphered = append(messageCiphered, byte(ascii))
				}
				
				//Check if the ciphered message contains common words
				words := []string {"the ", "is ", "are "}
				found := 0
				for _, word := range(words) {
					if strings.Contains(string(messageCiphered), word) {
						found++
					} else {
						break
					}
				}
				
				//If so, print the ciphered message, and compute the
				//sum of each ASCII value, as requested by the problem
				if found==len(words) {
					sum := 0
					for _, ascii := range(messageCiphered) {
						sum += int(ascii)
					}
					fmt.Printf("Cipher   %s%s%s \n", string(i), string(j), string(k))
					fmt.Printf("Sum      %d \n", sum)
					fmt.Printf("%s \n\n", string(messageCiphered))
				}
			}
		}
	}
}






func xor(sequence []bool, key []bool) []bool {
	//Prepare a copy of the input slice
	var seq []bool
	
	//If the sequence and key are equal in length, copy the sequence
	if len(sequence)==len(key) {
		seq = make([]bool, len(sequence))
		copy(seq, sequence)
	} else if len(key)>len(sequence) {
		//Expand the sequence as needed
		dif := len(key)-len(sequence)
		for i:=0; i<dif; i++ {
			seq = append(seq, false)
		}
		for _, bit := range(sequence) {
			seq = append(seq, bit)
		}
	}
	
	/* Apply the XOR cipher
	 * 1 xor 1 = 0
	 * 1 xor 0 = 1
	 * 0 xor 1 = 1
	 * 0 xor 0 = 0
	 */
	for i:=0; i<len(key); i++ {
		//1 xor 1
		if seq[i] && key[i] {
			seq[i] = false
		//1 xor 0, 0 xor 1
		} else if seq[i]!=key[i] {
			seq[i] = true
		}
	}
	return seq
} 

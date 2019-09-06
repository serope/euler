/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 59
 **********************************************************************/
package main

import (
	"fmt"
	"sync"
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
	
	//Split by commas
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
	
	
	/*
	 * Generate a list of every cipher combination that can be formed
	 * using three lowercase characters.
	 * 
	 * Every lowercase character has an 8-bit ASCII code.
	 * Therefore, the list holds 3-element slices of 8-element booleans.
	 * 
	 * The total amount of combinations is 26^3 = 17576.
	 */
	combos := make([][][]bool, 17576)
	index := 0
	for i:='a'; i<='z'; i++ {
		for j:='a'; j<='z'; j++ {
			for k:='a'; k<='z'; k++ {
				combo := [][]bool {binarySeq(int(i)), binarySeq(int(j)), binarySeq(int(k))}
				combos[index] = combo
				index++
			}
		}
	}
	
	//Solve the problem
	var wait sync.WaitGroup
	for _, combo := range(combos) {
		wait.Add(1)
		go solve(messageOrig, combo, &wait)
	}
	
	//Wait for each goroutine to finish
	wait.Wait()
}




func solve(messageOrig []int, combo [][]bool, wait *sync.WaitGroup) {
	i := 0
	var messageCiphered []byte
	
	for _, integer := range(messageOrig) {
		//Convert to a binary
		binary := binarySeq(integer)
		
		//XOR the binary with the current cipher combo
		xord := xor(binary, combo[i])
		
		//Increment selected element of combo
		i++
		if i==3 {
			i = 0
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
	
	//End
	if found==len(words) {
		sum := 0
		for _, ascii := range(messageCiphered) {
			sum += int(ascii)
		}
		fmt.Println(string(messageCiphered))
		fmt.Println("Sum: ", sum)
	}
	wait.Done()
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

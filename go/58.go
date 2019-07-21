/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 58
 **********************************************************************/
package main

import (
	"fmt"
	"math/big"
)


func main() {
	x			:= big.NewInt(1)
	jumpLen		:= 2
	sideLen		:= 0
	jumps		:= 0
	primes		:= 0
	printLine	:= 0
	
	ratio		:= 100.0
	goal		:= 10.0
	
	for ratio > goal {
		//Increment
		x.Add(x, big.NewInt(int64(jumpLen)))
		jumps += 1
		
		/*
		 * Perform Miller-Rabin primality test
		 * 
		 * TO DO: Implement a Miller-Rabin function which performs as
		 *        well as ProbablyPrime() in math/big
		 */
		if x.ProbablyPrime(5) {
			primes++
		}
		
		//Compute ratio
		ratio = 100.0*(float64(primes)/float64(jumpLen*2+1))
		
		//Increment jump len
		if jumps==4 {
			jumps = 0
			jumpLen += 2
			sideLen = jumpLen+1
		}
		
		//Print
		printLine++
		if printLine==3000 {
			fmt.Printf("x = %d \t primes = %d \t sideLen = %d \t ratio = %f \n", x, primes, sideLen, ratio)
			printLine = 0
		}
	}
	
	fmt.Printf("x = %d \t primes = %d \t sideLen = %d \t ratio = %f \n", x, primes, sideLen, ratio)
	fmt.Println("Done!")
}

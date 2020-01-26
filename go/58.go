// Project Euler
// 58.go
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
		x.Add(x, big.NewInt(int64(jumpLen)))
		jumps += 1
		if x.ProbablyPrime(5) {
			primes++
		}
		ratio = computeRatio(primes, jumpLen)
		if jumps==4 {
			jumps = 0
			jumpLen += 2
			sideLen = jumpLen+1
		}
		printLine++ // print every 3000 jumps
		if printLine==3000 {
			fmt.Printf("x %d \t primes %d \t sideLen %d \t ratio %f \n",
						x, primes, sideLen, ratio)
			printLine = 0
		}
	}
	
	fmt.Printf("x %d \t primes %d \t sideLen %d \t ratio %f \n", 
				x, primes, sideLen, ratio)
}


// computeRatio returns the primes-to-side-length ratio for problem 58.
func computeRatio(primes, jumpLen int) float64 {
	return 100.0*(float64(primes)/float64(jumpLen*2+1))
}

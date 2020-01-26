// Project Euler
// 51.go
package main

import (
	"fmt"
	"./euler"
	"./euler/base2"
)

func main() {
	// sieve
	primes := euler.Eratosthenes(1000000)
	
	// solve
	for _, p := range(primes) {
		if p <= 9 {		// don't bother with 1-digit primes
			continue
		}
		fams := families(p)
		for _, fam := range(fams) {
			if hasProblem51Property(fam, primes) {
				fmt.Println(p)
				fmt.Println(fam)
				return
			}
		}
	}
	
	// failed
	fmt.Println("No solution found.")
	fmt.Printf("Sieve range: %d-%d \n", primes[0], primes[len(primes)-1])
}

// hasProblem51Property returns true if the given family contains at
// least 8 primes.
func hasProblem51Property(fam, primes []int) bool {
	total := 0
	for _, member := range(fam) {
		if euler.IsPrime(member, primes) {
			total++
		}
	}
	return total >= 8
}

// families returns all of x's possible families as described in the
// problem text.
func families(x int) [][]int {
	patts := bitPatterns(euler.DigitCount(x))
	var fams [][]int
	for _, patt := range(patts) {
		fams = append(fams, family(x, patt))
	}
	return fams
}

// family returns x's family as described in the problem text, using the
// given bit pattern to indicate which digits should be replaced.
// e.g. x=752, pattern={1,0,1} -> {151, 252, 353, ... 959}
func family(x int, pattern []byte) []int {
	var fam []int
	digits := euler.Digits(x)
	for i:=0; i<=9; i++ {
		var skip bool
		for j, b := range(pattern) {
			if b == 0 {
				continue
			} else if i==0 && j==0 {
				skip = true
				continue
			}
			digits[j] = i
		}
		if !skip {
			fam = append(fam, euler.DigitsToInt(digits))
		}
	}
	return fam
}

// bitPatterns generates all binary/bit/base 2 sequences that have maxLen
// bits, except for:
// - the first sequence (e.g. 0000)
// - the final sequence (e.g. 1111111)
// - any sequence that ends with 1 (e.g. 00101)
func bitPatterns(maxLen int) [][]byte {
	x := 1
	var bins [][]byte
	for {
		bin := base2.New(x, maxLen)
		x++
		if bin[len(bin)-1] == 1 {		// ends with 1
			continue
		}
		bins = append(bins, bin)
		if base2.Len(x+1) > maxLen {	// next is final
			break
		}
	}
	return bins
}

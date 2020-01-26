// Project Euler
// 52.go
package main

import (
	"fmt"
	"./euler"
)

func main() {
	for x:=1; x<999999; x++ {
		if hasProblem52Property(x) {
			fmt.Println(x)
			break
		}
	}
}

// hasProblem52Property returns true if x, x*2, x*3, x*4, x*5, and x*6
// are all permutations of each other.
func hasProblem52Property(x int) bool {
	prods := products(x)
	for i:=0; i<5; i++ {
		if !euler.ArePermutations(prods[i], prods[i+1]) {
			return false
		}
	}
	fmt.Println(prods)
	return true
}


// products returns a slice containing x, x*2, x*3, x*4, x*5, and x*6.
func products(x int) [6]int {
	var prods [6]int
	for i:=0; i<6; i++ {
		prods[i] = x*(i+1)
	}
	return prods
}

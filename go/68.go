// Project Euler
// 68.go
package main

import (
	"fmt"
	"strconv"
	"math/big"
	"./euler"
	"./euler/pandigital"
)

func main() {
	var solutions []*big.Int
	
	// generate every 4th pandigital of length 10
	lim := euler.Factorial(10)
	for i:=1; i<=lim; i+=4 {
		pan := pandigital.New(i, 10)
		
		// one of the first 5 elements must be 0
		if pan[0]>0 && pan[1]>0 && pan[2]>0 && pan[3]>0 && pan[4]>0 {
			continue
		}
		
		// replace 0 with 10
		for i, digit := range(pan) {
			if digit == 0 {
				pan[i] = 10
				break
			}
		}
		
		// if the equalities hold
		if hasProblem68Property(pan) {
			//Convert sequence to solution string
			str := problem68String(pan)
			
			// convert to big
			x := big.NewInt(0)
			x.SetString(str, 10)
			
			// append to solutions
			solutions = append(solutions, x)
			
			// print
			fmt.Print(pan)
			fmt.Printf("\t")
			fmt.Println(x)
		}
	}
	
	// find max
	max := big.NewInt(0)
	for _, x := range(solutions) {
		if x.Cmp(max) > 0 {
			max = x
		}
	}
	fmt.Print("max: ")
	fmt.Println(max)
}

// problem68String takes a 10-digit pandigital sequence and formats its
// values into an appropriate 5-gon string.
func problem68String(pand []int) string {
	// readability
	a,b,c,d,e := pand[0], pand[1], pand[2], pand[3], pand[4]
	f,g,h,i,j := pand[5], pand[6], pand[7], pand[8], pand[9]

	// find lowest external node
	min := a
	external := []int {b, c, d, e}
	for _, node := range(external) {
		if node<min {
			min = node
		}
	}
	
	// form clockwise pattern
	trips := [][]int {{a,g,h}, {b,h,i}, {c,i,j}, {d,j,f}, {e,f,g}}
	switch min {
		case a: shiftLeft(trips, 0)
		case b: shiftLeft(trips, 1)
		case c: shiftLeft(trips, 2)
		case d: shiftLeft(trips, 3)
		case e: shiftLeft(trips, 4)
	}
	
	// return pattern as string
	var str string
	for _, trip := range(trips) {
		for _, n := range(trip) {
			str += strconv.Itoa(n)
		}
	}
	return str
}

// shiftLeft takes a 2-dimensional int slice and moves every element to
// the left n times, pushing the leftmost elements to the end.
func shiftLeft(a [][]int, n int) {
	for i:=0; i<n; i++ {
		elem := make([]int, len(a[0]))
		copy(elem, a[0])
		copy(a, a[1:])
		a[len(a)-1] = elem
	}
}

// hasProblem68Property returns true if every line on the given 5-gon
// ring (represented by a 10-digit pandigital) adds to the same sum.
func hasProblem68Property(pand []int) bool {
	// readability
	a,b,c,d,e := pand[0], pand[1], pand[2], pand[3], pand[4]
	f,g,h,i,j := pand[5], pand[6], pand[7], pand[8], pand[9]
	
	// sum each line
	line1 := a+g+h
	line2 := b+h+i
	line3 := j+i+c
	line4 := f+j+d
	line5 := e+f+g
	lines := []int {line1, line2, line3, line4, line5}
	
	// every line must be equal
	for i:=0; i<len(lines)-1; i++ {
		for j:=i+1; i<len(lines); i++ {
			if lines[i] != lines[j] {
				return false
			}
		}
	}
	return true
}

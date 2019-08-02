/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 68
 **********************************************************************/
package main

import (
	"fmt"
	"math/big"
)


func main() {
	//Create solution list
	list := make([]*big.Int, 0)
	
	//Generate every fourth 10-digit pandigitals
	for n:=1; n<=factorial(10); n+=4 {
		//Generate nth permutation
		pan := nthPermutationOfPandigital(n, 10)
		
		//One of the first 5 elements must be 0
		if pan[0]>0 && pan[1]>0 && pan[2]>0 && pan[3]>0 && pan[4]>0 {
			continue
		}
		
		//Replace 0 with 10
		for i, digit := range(pan) {
			if digit==0 {
				pan[i] = 10
				break
			}
		}
		
		//If the equalities hold
		if hasProblem67Property(pan) {
			//Convert sequence to solution string
			str := pandigitalTo5GonString(pan)
			
			//Convert to big
			x := big.NewInt(0)
			x.SetString(str, 10)
			
			//Append to list
			list = append(list, x)
			
			//Print
			fmt.Print(pan)
			fmt.Printf("\t")
			fmt.Println(x)
		}
	}
	
	//Find largest
	largest := big.NewInt(0)
	for _, x := range(list) {
		if x.Cmp(largest)>0 {
			largest = x
		}
	}
	fmt.Print("largest: ")
	fmt.Println(largest)
}



/*
 * Takes a 10-member sequence and returns the equivalent 5-gon ring
 * solution
 */
func pandigitalTo5GonString(set []int) string {
	//Formatted for readability
	a,b,c,d,e := set[0], set[1], set[2], set[3], set[4]
	f,g,h,i,j := set[5], set[6], set[7], set[8], set[9]

	//Find lowest external node
	lowest := a
	external := []int {b, c, d, e}
	for _, node := range(external) {
		if node<lowest {
			lowest = node
		}
	}
	
	//Return clockwise pattern as a string
	switch lowest {
		case a:
			return fmt.Sprintf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
										a,g,h,b,h,i,c,i,j,d,j,f,e,f,g)
		case b:
			return fmt.Sprintf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
										b,h,i,c,i,j,d,j,f,e,f,g,a,g,h)
		case c:
			return fmt.Sprintf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
										c,i,j,d,j,f,e,f,g,a,g,h,b,h,i)
		case d:
			return fmt.Sprintf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
										d,j,f,e,f,g,a,g,h,b,h,i,c,i,j)
		case e:
			return fmt.Sprintf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
										e,f,g,a,g,h,b,h,i,c,i,j,d,j,f)
	}
	
	return ""
}




/*
 * Checks if every line on a 5-gon ring adds to the same sum
 */
func hasProblem67Property(set []int) bool {
	//Formatted for readability
	a,b,c,d,e := set[0], set[1], set[2], set[3], set[4]
	f,g,h,i,j := set[5], set[6], set[7], set[8], set[9]
	
	//Sum each line
	line1 := a+g+h
	line2 := b+h+i
	line3 := j+i+c
	line4 := f+j+d
	line5 := e+f+g
	lines := []int {line1, line2, line3, line4, line5}
	
	//Every line must be equal
	for i:=0; i<len(lines)-1; i++ {
		for j:=i+1; i<len(lines); i++ {
			if lines[i] != lines[j] {
				return false
			}
		}
	}
	
	return true
}



/*
 * Returns the nth permutation of a pandigital sequence, where
 * the first pandigital is {1 2 3 4 5 6 7 8 9} if length<=9 or
 * {1 2 3 4 5 6 7 8 9 0} if length==10
 */
func nthPermutationOfPandigital(n, length int) []int {
	/*
	 * Prepare the pool (array which represents the smallest pandigital
	 * number that is exactly 'length' digits long) and solution set.
	 * 
	 * Note: If a pandigital is 10 digits long, it goes from 0 to 9.
	 *       Otherwise, it goes from 1 to n.
	 */
	pool		:= make([]int, length)
	solution	:= make([]int, 0)
	totalPerms	:= factorial(length)
	
	for i:=0; i<length; i++ {
		if length==10 {
			pool[i] = i
		} else {
			pool[i] = i+1
		}
	}

	/*
	 * Begin the process of generating the Nth permutation of the
	 * pandigital
	 */
	rangeSize := totalPerms/length
	rangeMarker := 0
	
	for {
		//Find which row is correct
		row := 0
		for rangeMarker+rangeSize < n {
			rangeMarker += rangeSize
			row += 1
		}
		
		//Transfer from pool to solution
		solution = append(solution, pool[row])
		pool = append(pool[:row], pool[row+1:]...)
		
		//Break when complete
		if len(solution) >= length {
			break
		}
		
		//Set ranges for next iteration
		rangeStart	:= rangeMarker
		rangeEnd	:= rangeMarker + rangeSize
		rangeMarker	= rangeStart
		rangeSize	= (rangeEnd-rangeStart)/(length-len(solution))
	}

	return solution
}



/*
 * Returns x!
 */
func factorial(x int) int {
	a := 1
	for b:=0; b<x; b++ {
		a *= (b+1)
	}
	return a
}

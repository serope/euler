/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 62
 **********************************************************************/
package main
import "fmt"

func main() {
	/* 
	 * Create a list of cubes and a parallel list of 10-member arrays
	 * in which each index represents a digit 0-9 and each value
	 * counts how many times that digit appears in the associated cube.
	 * 
	 * Example:
	 *     cubes[i]  = 405
	 *     counts[i] = {1,0,0,0,1,1,0,0,0,0}
	 */
	cubes := make([]uint64, 0)
	counts := make([][10]uint, 0)
	var x uint64 = 405
	var limit uint64 = 999999999999
	var cube uint64
	
	for cube < limit {
		//Compute x^3
		cube := x*x*x
		
		//Count how many times each digit 0-9 appears in the cube
		var count [10]uint
		digits := digitsOf(cube)
		for _, digit := range(digits) {
			count[digit]++
		}
		
		//Append the current cube and count
		cubes = append(cubes, cube)
		counts = append(counts, count)
		
		//Increment
		if cube > limit {
			break
		}
		x++
	}
	
	//Find one which has 5 permutations
	for i, x := range(cubes) {
		permutations := 1
		for j, _ := range(cubes) {
			if j<=i {
				continue
			} else if equalArrays(counts[i], counts[j]) {
				permutations++
			}
		}
		
		if permutations==5 {
			fmt.Printf("%d has %d permutations \n", x, permutations)
			break
		}
		
		//Remove x and its count
		cubes = append(cubes[:0], cubes[1:]...)
		counts = append(counts[:0], counts[1:]...)
	}
}




/*
 * This is the same as digitsOf() from euler.go but for uint64
 */
func digitsOf(x uint64) []uint {
	//If 'x' is one digit
	if (x<=9) {
		return []uint{uint(x)}
	}
	
	//Find the largest power of 10 which is smaller than 'x'
	var column uint64 = 10
	for (column*10 < x) {
		column *= 10
	}
	
	//Find every digit of 'x'
	var digits []uint
	for (column > 0) {
		current := x/column - 10*(x/(column*10))
		digits = append(digits, uint(current))
		column /= 10
	}

	return digits
}



/*
 * Returns whether two 10-member arrays are equal
 */
func equalArrays(a, b [10]uint) bool {
	for i:=0; i<10; i++ {
		if a[i]!=b[i] {
			return false
		}
	}
	return true
}

// Project Euler
// 62.go
package main

import "fmt"

func main() {
	// create two parallel slices:
	// cubes	a slice containing cube terms from 1 to the limit
	// counts	a slice containing 10-element arrays; each index
	//			represents a digit and each value represents how many
	//			times that digit appears in the corresponding cube
	// e.g.		cubes[i] = 405
	// 			counts[i] = {1,0,0,0,1,1,0,0,0,0}
	var cubes []uint64
	var counts [][10]int
	var x uint64 = 405
	var limit uint64 = 999999999999
	var cube uint64
	for cube < limit {
		cube := x*x*x						// x^3
		var count [10]int					// count digits
		digits := digitsOf(cube)
		for _, digit := range(digits) {
			count[digit]++
		}
		cubes = append(cubes, cube)			// append
		counts = append(counts, count)
		if cube > limit {					// end
			break
		}
		x++									// next
	}
	
	// which has 5 permutations?
	for i, x := range(cubes) {
		perms := 1
		for j, _ := range(cubes) {
			if j <= i {
				continue
			} else if equalArrays(counts[i], counts[j]) {
				perms++
			}
		}
		if perms == 5 {
			fmt.Printf("%d has %d perms \n", x, perms)
			break
		}
		cubes = append(cubes[:0], cubes[1:]...)		// remove
		counts = append(counts[:0], counts[1:]...)
	}
}

// digitsOf returns a slice of x's digits.
func digitsOf(x uint64) []int {
	if (x<=9) {
		return []int{int(x)}
	}
	var div uint64 = 10
	for (div*10 < x) {
		div *= 10
	}
	var digits []int
	for (div > 0) {
		current := x/div - 10*(x/(div*10))
		digits = append(digits, int(current))
		div /= 10
	}
	return digits
}

// equalArrays returns true if two 10-element arrays are equal.
func equalArrays(a, b [10]int) bool {
	for i:=0; i<10; i++ {
		if a[i] != b[i] {
			return false
		}
	}
	return true
}

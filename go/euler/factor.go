// Project Euler
// factor.go
package euler

// Factors returns an unordered slice of x's factors.
func Factors(x int) []int {
	if x == 1 {
		return []int{1}
	}
	upper := []int{x}
	lower := []int{1}
	f := 2
	for f < min(upper) {
		if x%f == 0 {
			lower = append(lower, f)
			if f*f != x {
				upper = append(upper, x/f)
			}
		}
		f += 1
	}
	upper = append(upper, lower...)
	return upper
}


// Odd returns an unordered slice of x's odd factors.
func OddFactors(x int) []int {
	if x <= 2 {
		return []int{1}
	}
	upper := []int{x}
	lower := []int{1}
	f := 3
	for f < min(upper) {
		if x%f == 0 {
			lower = append(lower, f)
			if isOdd(x/f) && f*f != x {
				upper = append(upper, x/f)
			}
		}
		f += 2
	}
	upper = append(upper, lower...)
	return upper
}


// min returns the smallest element in the slice.
func min(sl []int) int {
	m := sl[0]
	for _, x := range(sl) {
		if x < m {
			m = x
		}
	}
	return m
}


// isOdd returns true if x is odd.
func isOdd(x int) bool {
	return x%2 != 0
}

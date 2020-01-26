// Project Euler
// pandigital.go
package pandigital

// New generates the ith permutation of an n-digit pandigital using the
// method described on this page: https://serope.com/github/euler.html
func New(i, n int) []int {
	pool := newPool(n)
	var solution []int
	totalPerms := factorial(n)
	
	rangeSize := totalPerms/n
	rangeMarker := 0
	
	for {
		// find next row
		row := 0
		for rangeMarker+rangeSize < i {
			rangeMarker += rangeSize
			row += 1
		}
		
		// move from pool to solution
		solution = append(solution, pool[row])
		pool = append(pool[:row], pool[row+1:]...)
		
		// stop when finished
		if len(solution) >= n {
			break
		}
		
		// tet ranges for next iteration
		rangeStart	:= rangeMarker
		rangeEnd	:= rangeMarker + rangeSize
		rangeMarker	= rangeStart
		rangeSize	= (rangeEnd-rangeStart)/(n-len(solution))
	}

	return solution
}

// newPool returns a new slice of digits. If n is 10, then the range is
// 0-10. Otherwise, the range is 1-n.
func newPool(n int) []int {
	pool := make([]int, n)
	for i:=0; i<n; i++ {
		if n == 10 {
			pool[i] = i
		} else {
			pool[i] = i+1
		}
	}
	return pool
}

// factorial computes x!.
func factorial(x int) int {
	a := 1
	for b:=0; b<x; b++ {
		a *= (b+1)
	}
	return a
}

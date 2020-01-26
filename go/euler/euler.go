// Project Euler
// euler.go
package euler

import (
	"math"
	"math/big"
)

// LSearch performs a linear search and returns true if x is in a.
func LSearch(a []int, x int) bool {
	for _, y := range(a) {
		if y == x {
			return true
		}
	}
	return false
}

// BSearch performs a binary search on the sorted slice a and returns
// true if x was found.
func BSearch(a []int, x int) bool {
	if len(a)==0 {
		return false
	}
	
	l := 0				// left
	r := len(a)-1		// right
	m := len(a)/2		// middle
	
	if a[l]==x || a[r]==x { // x on border
		return true
	} else if x<a[l] || x>a[r] { // out of range
		return false
	}
	
	for m!=l && m!=r {
		if x < a[m] {
			r = m
		} else if x > a[m] {
			l = m
		} else if x==a[m] {
			return true
		}
		m = (r-l)/2 + l
	}
	return false
}

// Last returns the final element of a non-empty integer slice a.
func Last(a []int) int {
	return a[len(a)-1]
}

// Max returns the largest element in an integer slice a.
func Max(a []int) int {
	m := a[0]
	for _, x := range(a) {
		if x > m {
			m = x
		}
	}
	return m
}

// Sum computes the sum of an integer slice a.
func Sum(a []int) int {
	sum := 0
	for _, x := range(a) {
		sum += x
	}
	return sum
}

// Unique returns a slice which is the same as a, but without repeating
// elements. The new slice is not guaranteed to (and most likely will
// not) retain its original order.
func Unique(a []int) []int {
	m := make(map[int]bool)
	for _, x := range(a) {
		m[x] = true
	}
	b := make([]int, len(m))
	i := 0
	for x, _ := range(m) {
		b[i] = x
		i++
	}
	return b
}

// DigitCount returns the amount of digits in x.
func DigitCount(x int) int {
	if x <= 9 {
		return 1
	} else if x <= 99 {
		return 2
	} else if x <= 999 {
		return 3
	} else if x <= 9999 {
		return 4
	} else if x <= 99999 {
		return 5
	} else if x <= 999999 {
		return 6
	} else if x <= 9999999 {
		return 7
	} else if x <= 99999999 {
		return 8
	} else if x <= 999999999 {
		return 9
	} else if x <= 9999999999 {
		return 10
	}
	return -1
}

// Digits returns a slice of x's digits.
func Digits(x int) []int {
	if x <= 9 {
		return []int{x}
	}
	len := DigitCount(x)
	div := pow(10, len-1)
	digits := make([]int, len)
	i := 0
	for div > 0 {
		digit := x/div - 10*(x/(div*10))
		digits[i] = digit
		i++
		div = div/10
	}
	return digits
}

// DigitsToInt takes a slice of digits and returns its integer form.
func DigitsToInt(digits []int) int {
	x := 0	// returning int
	m := 1	// multiplier
	for i:=len(digits)-1; i>=0; i-- {
		x += digits[i]*m
		m *= 10
	}
	return x
}

// Factorial computes x!.
func Factorial(x int) int {
	a := 1
	for b:=0; b<x; b++ {
		a *= (b+1)
	}
	return a
}

// IsPalindrome returns true if x is a palindrome.
func IsPalindrome(x int) bool {
	digits := Digits(x)
	l := 0
	r := len(digits)-1
	for l <= r {
		if digits[l] != digits[r] {
			return false
		}
		l++
		r--
	}
	return true
}

// ArePermutations returns true if two integers are permutations of one
// another.
func ArePermutations(a, b int) bool {
	if a<=9 && b<=9 {
		return a==b
	} else if DigitCount(a) != DigitCount(b) {
		return false
	}
	digsA := Digits(a)
	digsB := Digits(b)
	var countsA, countsB [10]int
	for i:=0; i<len(digsA); i++ {
		countsA[digsA[i]]++
		countsB[digsB[i]]++
	}
	for i:=0; i<10; i++ {
		if countsA[i] != countsB[i] {
			return false
		}
	}
	return true
}

// Concatenate concatetes x and y into a new term.
func Concatenate(x, y int) int {
	if x == 0 {
		return y
	} else if y <= 9 {
		return x*10 + y
	} else if x<0 || y<0 {
		return 0
	}
	m := 10
	for m<y {
		m *= 10
	}
	return (x*m)+y
}

// IsSquare returns true if x is a perfect square.
func IsSquare(x int) bool {
	a := math.Sqrt(float64(x))
	b := int(a)
	c := float64(b)
	return a<=c
}

// ContinuedFraction returns the continued fraction sequence of s.
// See: https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
func ContinuedFraction(s int) []int {
	if IsSquare(s) {
		return nil
	}
	m0 := 0
	d0 := 1
	a0 := int(math.Sqrt(float64(s)))
	var terms []int
	m := m0
	d := d0
	a := a0
	// until a=2*a0...
	for a != 2*a0 {
		// compute m_(n+1)
		mn := d*a-m
		// compute d_(n+1)
		dn := (s-(mn*mn))/d
		// compute a_(n+1)
		an := int(float64((float64(a0) + float64(mn))/float64(dn)))
		terms = append(terms, an)
		// set new values
		m = mn
		d = dn
		a = an
	}
	return terms
}

// ContinuedFractionSlow returns the first max terms of the continued
// fraction sequence of s.
// See: https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
func ContinuedFractionSlow(s, max int) []int {
	if IsSquare(s) {
		return nil
	}
	m0 := 0
	d0 := 1
	a0 := int(math.Sqrt(float64(s)))
	var terms []int
	m := m0
	d := d0
	a := a0
	for n:=1; n<=max; n++ {
		mn := d*a-m
		dn := (s-(mn*mn))/d
		an := int(float64((float64(a0) + float64(mn))/float64(dn)))
		terms = append(terms, an)
		m = mn
		d = dn
		a = an
	}
	return terms
}

// LongestRepeatingSubset finds and returns the longest repeating subset
// that exists within a.
func LongestRepeatingSubset(a []int) []int {
	// if every term is the same
	if allSame(a) {
		return []int {a[0]}
	}
	var sub []int
	for _, x := range(a) {
		sub = append(sub, x)
		indeces := positions(a, sub)
		if len(indeces)<2 {
			continue
		}
		if indeces[0] + indeces[1] == len(sub) && !allSame(sub) {
			// the distance between every adjacent position (except the
			// last) must be equal
			solved := true
			dif := indeces[1] - indeces[0]
			for i:=0; i<len(indeces)-2; i++ {
				if indeces[i+1] - indeces[i] != dif {
					solved = false
					break
				}
			}
			if solved {
				return sub
			}
		}
	}
	return nil
}

// BigDigitSum returns the sum of x's digits.
func BigDigitSum(x *big.Int) int {
	sum := 0
	for _, b := range(x.String()) {
		sum += int(b)-48
	}
	return sum
}

// positions returns a slice of indeces at which the subsequence appears
// in a.
func positions(a, sub []int) []int {
	matches := 0
	j := 0
	var positions []int
	for i:=0; i<len(a); i++ {
		if a[i] == sub[j] {
			matches++
			j++
			if matches == len(sub) {
				positions = append(positions, i - (matches - 1))
				matches = 0
				j = 0
			}
		} else {
			matches = 0
			j = 0
		}
	}
	return positions
}


// pow returns a^b.
func pow(a, b int) int {
	if a==1 || b==0 {
		return 1
	}
	x := a
	for i:=1; i<b; i++ {
		x *= a
	}
	return x
}

// allSame returns true if every element in a is the same.
func allSame(a []int) bool {
	if len(a) == 1 {
		return true
	}
	for i:=1; i<len(a); i++ {
		if a[i] != a[0] {
			return false
		}
	}
	return true
}

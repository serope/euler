/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 **********************************************************************/
package main
import "math"


/*
 * eratosthenes()
 * 
 * Returns a slice of primes from 2 to the limit
 */
func eratosthenes(limit uint) []uint {
	var numbers []uint
	var primes []uint
	var i uint
	
	for i=0; i<limit; i++ {
		numbers = append(numbers, i+1)
	}
	
	for i=1; i<limit; i++ {
		if numbers[i]>0 {
			primes = append(primes, numbers[i])
			
			remove := i+numbers[i]
			for remove < limit {
				numbers[remove] = 0
				remove += numbers[i]
			}
		}
	}
	
	return primes
}






/*
 * Returns a slice of x's digits
 * e.g. digitsOf(207) -> {2, 0, 7}
 */
func digitsOf(x uint) []uint {
	//If 'x' is one digit
	if (x<=9) {
		return []uint{x}
	}
	
	//Find the largest power of 10 which is smaller than 'x'
	var column uint = 10
	for (column*10 < x) {
		column *= 10
	}
	
	//Find every digit of 'x'
	var digits []uint
	for (column > 0) {
		current := x/column - 10*(x/(column*10))
		digits = append(digits, current)
		column /= 10
	}

	return digits
}


/*
 * Returns the amount of digits in n
 */
func digitLen(n uint) uint {
	if n<=9 {
		return 1
	}
	
	var len uint = 2
	var column uint = 10
	for (column*10 < n) {
		column *= 10
		len++
	}
	
	return len
}





/*
 * Performs a binary search for target in set
 * The set must be sorted!
 */
func contains(set []uint, target uint) bool {
	//Return if the slice is empty
	if (set==nil || len(set)==0) {
		return false
	}
	
	//Set borders and halfway point for binary search
	left := 0
	right := len(set)-1
	halfway := len(set)/2
	
	//Return true if the target is the first or last item
	if (set[left]==target || set[right]==target) {
		return true
	}
	
	//Return false if the target is out of range
	if (target < set[left] || target > set[right]) {
		return false
	}
	
	//Binary search
	for {
		if (target < set[halfway]) {
			right = halfway
		} else if (target > set[halfway]) {
			left = halfway
		} else if (target==set[halfway]) {
			return true
		}
		
		halfway = (right-left)/2 + left
		
		if (halfway==left || halfway==right) {
			break
		}
	}
	
	//If the loop terminated, then the target wasn't found
	return false
}




/*
 * Returns the binary form of x
 * e.g. intToBin(5) -> {true, false, true}
 */
func binarySeq(x int) []bool {
	//Find the length of the sequence
	len := 1
	for {
		max := intPow(2, len)
		if (max <= x) {
			len++
		} else {
			break
		}
	}
	
	//Get the decimal multiplier of the first bit in the sequence
	m := intPow(2, len-1)
	
	//Create the binary sequence
	seq := []bool {}
	y := x
	
	for i:=0; i<len; i++ {
		if (m <= y) {
			seq = append(seq, true)
			y -= m;
		} else {
			seq = append(seq, false)
		}
		m = m/2
	}
	
	return seq
}






/*
 * Converts a binary sequence into an int
 */
func binToInt(seq []bool) int {
	index := len(seq)-1
	integer := 0
	multiplier := 1
	
	for index >= 0 {
		if seq[index] {
			integer += multiplier
		}
		multiplier *= 2
		index--
	}
	
	return integer
}




/*
 * Returns base^exp
 */
func intPow(base, exp int) int {
	if base==1 || exp==0 {
		return 1
	}
	
	x := base
	for e:=1; e<exp; e++ {
		x *= base
	}
	
	return x
}





/*
 * Returns the concatenation of two integers
 * e.g. concatenate(25,0) -> 250
 */
func concatenate(x, y uint) uint {
	//Case: 'x' is zero or 'y' is one digit
	if x==0 {
		return y
	} else if y<=9 {
		return x*10 + y
	}
	
	//Find 'm', the smallest multiple of 10 such that m>y
	var m uint = 10
	for m<y {
		m *= 10
	}
	
	return (x*m)+y
}



/*
 * Returns the sum of the given slice
 */
func sum(set []uint) uint {
	var sum uint = 0
	for _, x := range(set) {
		sum += x
	}
	return sum
}







/*
 * Returns whether x is a perfect square
 * e.g. isSquare(4) -> true
 *      isSquare(7) -> false
 */
func isSquare(x int) bool {
	a := math.Sqrt(float64(x))
	b := int(a)
	c := float64(b)
	return a<=c
}






/*
 * Returns the continued fraction sequence of 's' using the algorithm
 * on this page:
 * https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Continued_fraction_expansion
 */
func continuedFraction(s int) []int {
	//Return nil if 's' is a perfect square
	if isSquare(s) {
		return nil
	}
	
	//Initial values
	m0 := 0
	d0 := 1
	a0 := int(math.Sqrt(float64(s)))
	
	//Generate the continued fraction
	var terms []int
	m := m0
	d := d0
	a := a0
	
	//Until a=2*a0...
	for a != 2*a0 {
		//Compute m_(n+1)
		mn := d*a-m
		
		//Compute d_(n+1)
		dn := (s-(mn*mn))/d
		
		//Compute a_(n+1)
		an := int(float64((float64(a0) + float64(mn))/float64(dn)))
		
		//Append a_(n+1) to terms
		terms = append(terms, an)
		
		//Set new values
		m = mn
		d = dn
		a = an
	}
	
	return terms
}







/*
 * Returns the first 'max' terms of the continued fraction sequence of
 * 's' using the algorithm on this page:
 * https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Continued_fraction_expansion
 * 
 * (this was used in 64.go before a faster version was written)
 */
func continuedFractionSlow(s, max int) []int {
	//Return nil if 's' is a perfect square
	if isSquare(s) {
		return nil
	}
	
	//Initial values
	m0 := 0
	d0 := 1
	a0 := int(math.Sqrt(float64(s)))
	
	//Compute the first maxPeriodLen terms of the continued fraction
	var terms []int
	m := m0
	d := d0
	a := a0
	
	for n:=1; n<=max; n++ {
		//Compute m_(n+1)
		mn := d*a-m
		
		//Compute d_(n+1)
		dn := (s-(mn*mn))/d
		
		//Compute a_(n+1)
		an := int(float64((float64(a0) + float64(mn))/float64(dn)))
		
		//Append a_(n+1) to terms
		terms = append(terms, an)
		
		//Set new values
		m = mn
		d = dn
		a = an
	}
	
	return terms
}






/*
 * Checks a set of ints and returns a set which is the longest
 * repeating subset.
 * 
 * Note: The distance between each poisition must be 0, otherwise it
 *       fails in cases like continuedFractionSlow(137) = 
 *       {1 2 2 1 1 2 2 1 22 1 2 2 1 1 2 2 1 22 1 2 2 1 1 2 2 ...}
 * 
 * (this was used in 64.go before continuedFractionSlow() was replaced
 *  with a faster version)
 */
func repeatingTerm(sequence []int) []int {
	//If every term is the same
	if allSame(sequence) {
		return []int {sequence[0]}
	}
	
	var subsequence []int
	for _, x := range(sequence) {
		subsequence = append(subsequence, x)
		positions := positions(sequence, subsequence)
		if len(positions)<2 {
			continue
		}
		
		if positions[0]+positions[1]==len(subsequence) && !allSame(subsequence) {
			//The distance between every adjacent position (except the last) must be equal
			solved := true
			dif := positions[1]-positions[0]
			for i:=0; i<len(positions)-2; i++ {
				if positions[i+1]-positions[i] != dif {
					solved = false
					break
				}
			}
			
			if solved {
				return subsequence
			}
		}
	}
	return nil
}



/*
 * Returns a list of indexes at which the subsequence appears in the
 * sequence
 */
func positions(sequence, subsequence []int) []int {
	matches := 0
	subIndex := 0
	var positions []int
	
	for i:=0; i<len(sequence); i++ {
		if sequence[i]==subsequence[subIndex] {
			matches++
			subIndex++
			
			if matches==len(subsequence) {
				positions = append(positions, i-(matches-1))
				matches = 0
				subIndex = 0
			}
		} else {
			matches = 0
			subIndex = 0
		}
	}
	
	return positions
}



/*
 * Returns whether or not every item in 'set' is the same
 */
func allSame(set []int) bool {
	if len(set)==1 {
		return true
	}
	
	for i:=1; i<len(set); i++ {
		if set[i]!=set[0] {
			return false
		}
	}
	
	return true
}


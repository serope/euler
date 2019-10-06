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
func eratosthenes(limit int) []int {
	var numbers, primes []int
	
	for i:=0; i<limit; i++ {
		numbers = append(numbers, i+1)
	}
	
	for i:=1; i<limit; i++ {
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
 * digitsOf()
 * 
 * Returns a slice of x's digits, e.g. digitsOf(207) -> {2, 0, 7}
 */
func digitsOf(x int) []int {
	if x<=9 {
		return []int{x}
	}
	
	pow := 10
	for pow*10 < x {
		pow *= 10
	}
	
	var digits []int
	for pow > 0 {
		digits = append(digits, x/pow)
		x = x%pow
		pow = pow/10
	}

	return digits
}





/*
 * digitLen()
 * 
 * Returns the amount of digits in n
 */
func digitLen(n int) int {
	if n<=9 {
		return 1
	}
	
	len := 2
	pow := 10
	for pow*10 < n {
		pow *= 10
		len++
	}
	
	return len
}





/*
 * contains()
 * 
 * Performs a binary search on a sorted slice
 */
func contains(set []int, target int) bool {
	if (set==nil || len(set)==0) {
		return false
	}
	
	//Set borders and halfway point for binary search
	left := 0
	right := len(set)-1
	halfway := len(set)/2
	
	//If first or last item
	if (set[left]==target || set[right]==target) {
		return true
	}
	
	//If out of range
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
	
	//Item wasn't found
	return false
}




/*
 * binarySeq()
 * 
 * Returns the binary form of x, e.g. intToBin(5) -> {true, false, true}
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
 * bintoInt()
 * 
 * Reverts a binary sequence returned by intToBin() back to an integer
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
 * intPow()
 * 
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
 * concatenate()
 * 
 * Returns the concatenation of two positive integers
 * e.g. concatenate(25,0) -> 250
 */
func concatenate(x, y int) int {
	if x==0 {
		return y
	} else if y<=9 {
		return x*10 + y
	} else if x<0 || y<0 {
		return 0
	}
	
	//Find 'm', the smallest multiple of 10 such that m>y
	m := 10
	for m<y {
		m *= 10
	}
	
	return (x*m)+y
}





/*
 * sum()
 */
func sum(set []int) int {
	var sum int = 0
	for _, x := range(set) {
		sum += x
	}
	return sum
}







/*
 * isSquare()
 */
func isSquare(x int) bool {
	a := math.Sqrt(float64(x))
	b := int(a)
	c := float64(b)
	return a<=c
}






/*
 * getContinuedFraction()
 * 
 * Returns the continued fraction sequence of 's' using the algorithm
 * on this page:
 * https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Continued_fraction_expansion
 */
func getContinuedFraction(s int) []int {
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
 * getContinuedFractionSlow()
 * 
 * Returns the first 'max' terms of the continued fraction sequence of
 * 's' using the algorithm on this page:
 * https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Continued_fraction_expansion
 * 
 * (this was used in 64.go before a faster version was written)
 */
func getContinuedFractionSlow(s, max int) []int {
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
 * repeatingTerm()
 * 
 * Checks a set of ints and returns a set which is the longest
 * repeating subset.
 * 
 * Note: The distance between each poisition must be 0, otherwise it
 *       fails in cases like getContinuedFractionSlow(137) = 
 *       {1 2 2 1 1 2 2 1 22 1 2 2 1 1 2 2 1 22 1 2 2 1 1 2 2 ...}
 * 
 * (this was used in 64.go before getContinuedFractionSlow() was
 *  replaced with a faster version)
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
 * positions()
 * 
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
 * allSame()
 * 
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


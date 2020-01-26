// Project Euler
// 53.go
package main

import "fmt"

func main() {
	distinct := 0
	for n:=1; n<=100; n++ {
		under := 0
		for r:=1; r<=n; r++ {
			// compute combo
			c := combo(n, r)
			fmt.Printf("combo(%d,%d) \t %d \n", n, r, c)
			
			// if combo under 1M, increment under
			if c<1000000 {
				under++
				continue
			}
			
			// otherwise, if the combo is 1M+, then the amount of further
			// combos which evaluate to 1M+ can be easily determined
			distinct += n-(under*2 + 1)
			break
		}
	}
	fmt.Println(distinct)
}


// combo returns (n r) as described in the problem text.
func combo(n, r int) int {
	if n==r {	// edge cases
		return 1
	} else if n==r+1 {
		return n
	} else if r>n {
		return -1
	}
	
	// assign halt as either r or (n-r), whichever is closer to n
	var halt int
	if (n-r) > r  {
		halt = n-r
	} else {
		halt = r
	}

	// evaluate numerator factorial going down, but stop at halt
	numerator := 1
	for f:=n; f>halt; f-- {
		numerator *= f;
	}
	
	// evaluate denominator based on halt value
	denominator := 1
	if halt == n-r {
		for f:=r; f>1; f-- {
			denominator *= f
		}
	} else {
		for f:=(n-r); f>1; f-- {
			denominator *= f
		}
	}
	return numerator/denominator
}

/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 66
 **********************************************************************/
package main

import (
	"fmt"
	"math/big"
)



func main() {
	/* 
	 * Prepare a map of solutions where each key is a value of D and
	 * each value is the smallest x in the solution, e.g. from the
	 * problem text: solutions[13] = 649
	 */
	solutions := make(map[int]*big.Int, 0)
	limit := 1000
	
	//Find each solution from D=1 to the limit
	for i:=1; i<=limit; i++ {
		//Ignore perfect squares
		if isSquare(i) {
			continue
		}
		
		//Prepare the current D, x, y, and N
		d := big.NewInt(int64(i))
		n := 1
		x, y := nthConvergent(d, n)
		
		//Continue generating the Nth convergent of D until the
		//convergent satisfies the Diophantine equation
		for isDiophantineSolution(d, x, y)==false {
			n++
			x, y = nthConvergent(d, n)
		}
		
		//Save the solution
		solutions[i] = x
	}
	
	fmt.Println(solutions)
	
	//Find D which holds largest x
	largest := 2
	for d, x := range(solutions) {
		if x.Cmp(solutions[largest])>0 {
			largest = d
		}
	}
	
	//Print
	fmt.Printf("D=%d \n", largest)
	fmt.Printf("x=%d \n", solutions[largest])
}



/*
 * Returns whether the given d, x, and y satisfy the following
 * Diophantine equation: x^2 - D * y^2 = 1
 */
func isDiophantineSolution(d, x, y *big.Int) bool {
	//Compute x^2
	x2 := big.NewInt(0)
	x2.Mul(x, x)
	
	//Compute y^2
	y2 := big.NewInt(0)
	y2.Mul(y, y)
	
	//Compute x^2 - D * x^2
	lhs := big.NewInt(0)
	lhs.Mul(d, y2)
	lhs.Sub(x2, lhs)
	
	//Return whether left-hand side of equation equals 1
	return lhs.Cmp(big.NewInt(1))==0
}



/*
 * Returns the first 'n' terms in the continued fraction sequence of
 * the big.Int 's'
 * 
 * This is the same thing as continuedFraction() from 64.go, but for
 * the big.Int type
 */
func bigContinuedFraction(s *big.Int, n int) []*big.Int {
	//Return nil if 's' is a perfect square
	if bigIsSquare(s) {
		return nil
	}
	
	//Initial values
	m0 := big.NewInt(0)
	d0 := big.NewInt(1)
	a0 := big.NewInt(0)
	a0.Sqrt(s)
	
	//Generate the continued fraction
	terms := make([]*big.Int, 0)
	m := m0
	d := d0
	a := a0
	
	for i:=0; i<n; i++ {
		//Compute m_(n+1)
		mn := big.NewInt(0)
		mn.Mul(d, a)
		mn.Sub(mn, m)
		
		//Compute d_(n+1)
		dn := big.NewInt(0)
		dn.Mul(mn, mn)
		dn.Sub(s, dn)
		dn.Div(dn, d)
		
		//Compute a_(n+1)
		an := big.NewInt(0)
		an.Add(a0, mn)
		an.Div(an, dn)
		
		//Append a_(n+1) to terms
		terms = append(terms, an)
		
		//Set new values
		m = big.NewInt(0)
		m.Add(m, mn)
		d = big.NewInt(0)
		d.Add(d, dn)
		a = big.NewInt(0)
		a.Add(a, an)
	}
	
	return terms
}



/*
 * Returns whether 'a' is a perfect square
 */
func bigIsSquare(a *big.Int) bool {
	b := big.NewInt(0)
	b.Sqrt(a)			//sqrt(a)
	b.Mul(b, b)			//sqrt(a)*sqrt(a)
	return b.Cmp(a)==0	//return sqrt(a)^2 == a
}





/*
 * Returns a fraction (in the form of two big.Ints; top and bottom)
 * which represents the Nth convergent of x
 */
func nthConvergent(x *big.Int, n int) (*big.Int, *big.Int) {
	//Generated continued fraction
	sequence := bigContinuedFraction(x, n)
	
	//Generate nth convergent
	var top, bot *big.Int
	printProgress := false
	for i:=len(sequence)-1; i>=0; i-- {
		//Print
		if printProgress {
			fmt.Printf("i=%d \t sequence[i] = %s \t %s / %s -> ", i, sequence[i].String(), top.String(), bot.String())
		}
		
		//If 1st loop
		if i==len(sequence)-1 {
			top = big.NewInt(1)
			bot = sequence[i]
			if printProgress {
				fmt.Printf("%d / %d \n", top, bot)
			}
			continue
		}
		
		//Fraction addition
		product := big.NewInt(0)
		product.Mul(bot, sequence[i])
		top.Add(top, product)
		bot, top = top, bot
		
		//Print
		if printProgress {
			fmt.Printf("%s / %s \n", top.String(), bot.String())
		}
	}
	
	//Finally, add sqrt(x)
	root := big.NewInt(0)
	root.Sqrt(x)
	root.Mul(root, bot)
	top.Add(top, root)
	
	return top, bot
}

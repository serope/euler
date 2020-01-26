// Project Euler
// 66.go
package main

import (
	"fmt"
	"math/big"
	"./euler"
)

func main() {
	// key: a value of D
	// val: the smallest x in that D's solution
	// e.g. from problem text: solutions[13] = 649
	solutions := make(map[int]*big.Int)
	limit := 1000
	
	for i:=1; i<=limit; i++ {
		if euler.IsSquare(i) { // ignore squares
			continue
		}
		d := big.NewInt(int64(i)) // Diophantine
		n := 1
		x, y := nthConvergent(d, n)
		for isDiophantineSolution(d, x, y)==false {
			n++
			x, y = nthConvergent(d, n)
		}
		solutions[i] = x
	}
	
	// find max
	max := 2
	for d, x := range(solutions) {
		if x.Cmp(solutions[max]) > 0 {
			max = d
		}
	}
	fmt.Printf("D=%d \n", max)
	fmt.Printf("x=%d \n", solutions[max])
}

// isDiophantineSolution returns true if d, x, and y satisfy the
// Diophantine equation: x^2 - D * y^2 = 1
func isDiophantineSolution(d, x, y *big.Int) bool {
	x2 := big.NewInt(0) // x^2
	x2.Mul(x, x)
	
	y2 := big.NewInt(0) // y^2
	y2.Mul(y, y)
	
	lhs := big.NewInt(0) // x^2 - D * x^2
	lhs.Mul(d, y2)
	lhs.Sub(x2, lhs)
	
	return lhs.Cmp(big.NewInt(1)) == 0
}

// bigContinuedFraction returns the first n terms of the continued
// fraction of s.
func bigContinuedFraction(s *big.Int, n int) []*big.Int {
	if bigIsSquare(s) {
		return nil
	}
	m0 := big.NewInt(0)
	d0 := big.NewInt(1)
	a0 := big.NewInt(0)
	a0.Sqrt(s)
	terms := make([]*big.Int, 0)
	m := m0
	d := d0
	a := a0
	for i:=0; i<n; i++ {
		mn := big.NewInt(0) // compute m_(n+1)
		mn.Mul(d, a)
		mn.Sub(mn, m)
		
		dn := big.NewInt(0) // compute d_(n+1)
		dn.Mul(mn, mn)
		dn.Sub(s, dn)
		dn.Div(dn, d)
		
		an := big.NewInt(0) // compute a_(n+1)
		an.Add(a0, mn)
		an.Div(an, dn)
		terms = append(terms, an)
		
		m = big.NewInt(0) // set new values
		m.Add(m, mn)
		d = big.NewInt(0)
		d.Add(d, dn)
		a = big.NewInt(0)
		a.Add(a, an)
	}
	return terms
}

// bigIsSquare returns true if a is a perfect square.
func bigIsSquare(a *big.Int) bool {
	b := big.NewInt(0)
	b.Sqrt(a)				// sqrt(a)
	b.Mul(b, b)				// sqrt(a)*sqrt(a)
	return b.Cmp(a) == 0	// sqrt(a)^2 == a
}

// nthConvergent computes the Nth convergent of x, returning the
// numerator and denominator.
func nthConvergent(x *big.Int, n int) (*big.Int, *big.Int) {
	cf := bigContinuedFraction(x, n)	// get continued fraction
	var top, bot *big.Int				// begin computing convergent
	for i:=len(cf)-1; i>=0; i-- {
		if i==len(cf)-1 { // if 1st loop
			top = big.NewInt(1)
			bot = cf[i]
			continue
		}
		
		product := big.NewInt(0) // fraction addition
		product.Mul(bot, cf[i])
		top.Add(top, product)
		bot, top = top, bot
	}
	
	root := big.NewInt(0) // add sqrt(x)
	root.Sqrt(x)
	root.Mul(root, bot)
	top.Add(top, root)
	return top, bot
}

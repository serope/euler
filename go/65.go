// Project Euler
// 65.go
package main

import (
	"fmt"
	"math/big"
	"./euler"
)

func main() {
	// e's continued fraction
	cf := continuedFractionE(100)
	fmt.Println(cf)
	
	// generate 100th term of e's convergents
	var top, bot *big.Int
	for i:=len(cf)-1; i>=0; i-- {
		fmt.Printf("i=%d \t cf[i] = %v \t %v / %v -> ", i, cf[i], top,
																	bot)
		// if 1st loop
		if i==len(cf)-1 {
			top = big.NewInt(1)
			bot = cf[i]
			fmt.Printf("%d / %d \n", top, bot)
			continue
		}
		
		// fraction arithmetic
		if cf[i].Cmp(big.NewInt(1))==0 && top.Cmp(big.NewInt(1))==0 {
			top.Add(bot, big.NewInt(1))
		} else {
			// flip
			bot, top = top, bot
			
			// add
			product := big.NewInt(0)
			product.Mul(bot, cf[i])
			top.Add(top, product)
		}
		fmt.Printf("%v / %v \n", top, bot)
		
	}
	
	fmt.Printf("100th %v / %v \n", top, bot)
	fmt.Printf("sum \t %d \n", euler.BigDigitSum(top))
}


// continuedFractionE generates the first n terms of e's continued
// fraction.
func continuedFractionE(n int) []*big.Int {
	k := 1
	cf := []*big.Int {big.NewInt(2)}
	for len(cf)<n {
		cf = append(cf, []*big.Int {big.NewInt(1), 
									big.NewInt(int64(2*k)),
									big.NewInt(1)} ...)
		k++
	}
	for len(cf) != n { // shrink if over n
		last := len(cf)-1
		cf = cf[:last]
	}
	return cf
}

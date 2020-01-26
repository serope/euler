// Project Euler
// 57.go
package main

import "math/big"

func main() {
	// After studying the examples on paper, one can determine the
	// following method for generating the next fraction in the sequence:
	// 1.	Flip the fraction
	// 2.	Double the denominator
	// 3.	Subtract the previous iteration's denominator from this
	// 		denominator  (if this is the first iteration, subtract 1)
	// 4.	Add the denominator to the numerator
	top := big.NewInt(3)
	bot := big.NewInt(2)
	prev := big.NewInt(1)
	total := 0
	
	for i:=0; i<1000; i++ {
		top, bot = bot, top			// 1
		bot.Mul(bot, big.NewInt(2))	// 2
		bot.Sub(bot, prev)			// 3
		top.Add(top, bot)			// 4
		if (len(top.String()) > len(bot.String())) {
			total++
		}
		prev.Sub(top, bot) // set prev
	}
	
	println(total)
}

/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 65
 **********************************************************************/
package main
import (
	"fmt"
	"math/big"
)



func main() {
	//Generate first N terms of e's continued fraction
	n := 100
	k := 1
	sequence := []*big.Int {big.NewInt(2)}
	for len(sequence)<n {
		sequence = append(sequence, []*big.Int {big.NewInt(1), big.NewInt(int64(2*k)), big.NewInt(1)} ...)
		k++
	}
	
	//If necessary, pop list until len=N
	for len(sequence) != n {
		last := len(sequence)-1
		sequence = sequence[:last]
	}
	fmt.Println(sequence)
	
	//Generate 100th term of e's convergents
	var top, bot *big.Int
	printProgress := true
	for i:=len(sequence)-1; i>=0; i-- {
		//Print
		if printProgress {
			fmt.Printf("i=%d \t sequence[i] = %s \t %s / %s -> ", i, sequence[i].String(), top.String(), bot.String())
		}
		
		//if 1st loop
		if i==len(sequence)-1 {
			top = big.NewInt(1)
			bot = sequence[i]
			if printProgress {
				fmt.Printf("%d / %d \n", top, bot)
			}
			continue
		}
		
		//fraction arithmetic
		if sequence[i].Cmp(big.NewInt(1))==0 && top.Cmp(big.NewInt(1))==0 {
			top.Add(bot, big.NewInt(1))
		} else {
			//flip term
			bot, top = top, bot
			
			//fraction addition
			product := big.NewInt(0)
			product.Mul(bot, sequence[i])
			top.Add(top, product)
		}
		
		//Print
		if printProgress {
			fmt.Printf("%s / %s \n", top.String(), bot.String())
		}
		
	}
	
	//Print Nth term
	fmt.Printf("%dth \t", n)
	fmt.Printf("%s / %s \n", top.String(), bot.String())
	
	//Compute sum of numerator
	sum := sumOfBigDigits(top)
	fmt.Printf("sum \t%d \n", sum)
}





/*
 * sumOfBigDigits()
 * 
 * Returns the sum of the digits of x
 */
func sumOfBigDigits(x *big.Int) int {
	//Convert digits to ints
	digits := make([]int, 0)
	for _, char := range(x.String()) {
		digits = append(digits, int(char)-48)
	}
	
	//Compute sum
	sum := 0
	for _, digit := range(digits) {
		sum += digit
	}
	
	return sum
}

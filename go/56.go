// Project Euler
// 56.go
package main

import (
	"fmt"
	"math/big"
	"./euler"
)

func main() {
	max := 0
	for a:=2; a<=99; a++ {
		for b:=2; b<=a; b++ {
			c := big.NewInt(0) // a^b = c
			c.Exp(big.NewInt(int64(a)), big.NewInt(int64(b)), nil)
			sum := euler.BigDigitSum(c)
			if sum > max {
				fmt.Printf("%v^%v = %v (%d) \n", a, b, c, sum)
				max = sum
			}
		}
	}
	fmt.Println(max)
}

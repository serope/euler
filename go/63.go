// Project Euler
// 63.go
package main

import (
	"fmt"
	"math/big"
)

func main() {
	limit := big.NewInt(30)
	total := 0
	a := big.NewInt(1)
	for a.Cmp(limit) < 1 {
		b := big.NewInt(1)
		for b.Cmp(limit) < 1 {
			pow := big.NewInt(0)
			pow.Exp(a, b, nil)
			digitLen := big.NewInt(int64(len(pow.String())))
			if b.Cmp(digitLen)==0 {
				total++
				fmt.Printf("%v^%v = %v \n", a, b, pow)
			}
			b.Add(b, big.NewInt(1))
		}
		a.Add(a, big.NewInt(1))
	}
	fmt.Printf("total: %d \n", total)
}

// Project Euler
// 64.go
package main

import (
	"fmt"
	"./euler"
)

func main() {
	total := 0
	n := 10000
	for i:=1; i<=n; i++ {
		cf := euler.ContinuedFraction(i)
		if cf == nil { // i was a perfect square
			continue
		}
		if len(cf)%2 != 0 {
			fmt.Printf("%d \t %d \n", i, len(cf))
			total++
		}
	}
	fmt.Println(total)
}

// Project Euler
// 60.go
// TODO: Solve this with dynamic programming
package main

import (
	"fmt"
	"./euler"
)

func main() {
	// sieve (10k is sufficient)
	primes := euler.Eratosthenes(10000)
	
	// remove 2 and 5 (no term that ends with 2 and 5, except 2 and 5
	// themselves, are prime)
	primes = append(primes[:0], primes[1:]...)
	primes = append(primes[:1], primes[2:]...)
	
	// solve
	var set []int
	for i:=0; i<len(primes); i++ {
		a := primes[i]
		for j:=i+1; j<len(primes)-1; j++ {
			b := primes[j]
			if !hasProblem60Property(b, []int{a}, primes) {
				continue
			}
			for k:=j+1; k<len(primes)-2; k++ {
				c := primes[k]
				if !hasProblem60Property(c, []int{a, b}, primes) {
					continue
				}
				for l:=k+1; l<len(primes)-3; l++ {
					d := primes[l]
					if !hasProblem60Property(d, []int{a, b, c}, primes) {
						continue
					}
					for m:=l+1; m<len(primes)-4; m++ {
						e := primes[m]
						if !hasProblem60Property(e, []int{a, b, c, d}, 
																primes) {
							continue
						}
						set = append(set, a, b, c, d, e)
						goto end
					}
				}
			}
		}
	}
	end:
	fmt.Println(set)
	fmt.Println(euler.Sum(set))
}


// hasProblem60Property returns true if x, when concatenated with every
// term in set, produces a prime.
func hasProblem60Property(x int, set, primes []int) bool {
	for _, y := range(set) {
		xy := euler.Concatenate(x, y)
		yx := euler.Concatenate(y, x)
		if euler.IsPrime(xy, primes) && euler.IsPrime(yx, primes) {
			continue
		} else {
			return false
		}
	}
	return true
}

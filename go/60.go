/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 60
 **********************************************************************/
package main

import (
	"fmt"
	"math/big"
)



func main() {
	//Make a list of primes from 1 to a limit (10k is sufficient)
	primes := eratosthenes(10000)
	
	//Remove 2 and 5 from the list (index 0, then index 1)
	primes = append(primes[:0], primes[1:]...)
	primes = append(primes[:1], primes[2:]...)
	
	//Solve the problem
	var set []int
	for i:=0; i<len(primes); i++ {
		a := primes[i]
		
		for j:=i+1; j<len(primes)-1; j++ {
			b := primes[j]
			if !hasProblem60Property([]int {a}, primes, b) {
				continue
			}
			
			for k:=j+1; k<len(primes)-2; k++ {
				c := primes[k]
				if !hasProblem60Property([]int {a, b}, primes, c) {
					continue
				}

				
				for l:=k+1; l<len(primes)-3; l++ {
					d := primes[l]
					if !hasProblem60Property([]int {a, b, c}, primes, d) {
						continue
					}

					
					for m:=l+1; m<len(primes)-4; m++ {
						e := primes[m]
						if !hasProblem60Property([]int {a, b, c, d}, primes, e) {
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
	fmt.Println(sum(set))
}




/*
 * Concatenates y with every x in set
 * If both xy and yx are prime, returns true
 */
func hasProblem60Property(set, primes []int, y int) bool {
	for _, x := range(set) {
		xy := concatenate(x, y)
		yx := concatenate(y, x)
		if isPrime(xy, primes) && isPrime(yx, primes) {
			continue
		} else {
			return false
		}
	}
	return true
}




func isPrime(x int, primes []int) bool {
	//Get largest prime in 'primes'
	largest := primes[len(primes)-1]
	
	//If 'x' is small, do a binary search for it in 'primes'
	if x<=largest {
		return contains(primes, x)
	}
	
	//If 'x' is large, perform the Miller-Rabin test on it
	bigx := big.NewInt(int64(x))
	return bigx.ProbablyPrime(0)
}

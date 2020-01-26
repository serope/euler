// Project Euler
// prime.go
package euler

import "math"

// IsPrime tests x's primality via trial division, utilizing a slice of
// primes sieved up to at least sqrt(x).
func IsPrime(x int, primes []int) bool {
	if x <= 1 {
		return false
	}
	lim := int(math.Sqrt(float64(x)))
	for _, p := range(primes) {
		if (p > lim) {
			break
		} else if x%p==0 {
			return false
		}
	}
	return true
}

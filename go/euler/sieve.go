// Project Euler
// sieve.go
package euler

// Eratosthenes returns a sequence of the first n primes.
// (https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)
func Eratosthenes(n int) []int {
	nums := naturalNumbers(n)
	nums[0] = 0
	var primes []int
	for i, x := range(nums) {
		if x>0 {
			primes = append(primes, x)
			crossOut := i + x
			for (crossOut < n) {
				nums[crossOut] = 0
				crossOut += x
			}
		}
	}
	return primes;
}


// naturalNumbers returns the first n natural numbers.
func naturalNumbers(n int) []int {
	nums := make([]int, n)
	for i:=0; i<n; i++ {
		nums[i] = i+1
	}
	return nums
}

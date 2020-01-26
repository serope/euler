// Project Euler
// 55.go
package main

import "math/big"

func main() {
	total := 0
	lim := 10000
	for i:=1; i<lim; i++ {
		if isLychrel(i) {
			total++
		}
	}
	println(total)
}

// isLychrel returns true if n is a Lychrel number as described in the
// problem text (it never becomes a palindrome after adding its reverse
// to itself 50 times).
func isLychrel(n int) bool {
	x := big.NewInt(int64(n))
	for i:=0; i<50; i++ {
		x = x.Add(x, reverseBig(x))
		if isPalindrome(x) {
			return false
		}
	}
	return true
}

// isPalindrome returns true if x is a palindrome.
func isPalindrome(x *big.Int) bool {
	str := x.String()
	i := 0
	j := len(str)-1
	for i <= j {
		if str[i] != str[j] {
			return false
		}
		i++
		j--
	}
	return true
}

// reverseBig returns the reverse of x as a new *big.Int.
func reverseBig(x *big.Int) *big.Int {
	y := big.NewInt(0)
	y.SetString(reverseString(x.String()), 10)
	return y
}

// reverseString returns the reverse of str.
func reverseString(str string) string {
	rev := make([]rune, len(str))
	i := len(str)-1
	for _, r := range(str) {
		rev[i] = r
		i--
	}
	return string(rev)
}

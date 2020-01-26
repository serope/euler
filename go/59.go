package main

import (
	"fmt"
	"strings"
	"strconv"
	"io/ioutil"
	"./euler/base2"
)

func main() {
	// read file into base 2
	bins, err := readMessageFile("59_message")
	if err!=nil {
		panic(err)
	}
	
	// check every possible 3-lowercase-character cipher
	var answer string
	solved := false
	for i:='a'; i<='z'; i++ {
		for j:='a'; j<='z'; j++ {
			for k:='a'; k<='z'; k++ {
				x := base2.New(int(i), 0)
				y := base2.New(int(j), 0)
				z := base2.New(int(k), 0)
				cipher := []base2.Base2{x, y, z}
				str := decode(cipher, bins)
				if hasProblem59Property(str) {
					answer = str
					solved = true
					break
				}
			}
			if solved {
				break
			}
		}
		if solved {
			break
		}
	}
	
	// end
	fmt.Println(answer)
	fmt.Println(asciiSum(answer))
}


// asciiSum returns the sum of each character's ASCII value.
func asciiSum(str string) int {
	sum := 0
	for _, b := range(str) {
		sum += int(b)
	}
	return sum
}


// decode applies a cipher to a message and returns the resulting decoded
// string.
func decode(cipher, message []base2.Base2) string {
	// copy
	ciphered := make([]base2.Base2, len(message))
	copy(ciphered, message)
	
	// XOR
	j := 0 // cipher index
	for i, b := range(ciphered) {
		ciphered[i] = b.Xor(cipher[j])
		j++
		if j == len(cipher) {
			j = 0
		}
	}
	
	// convert back to string
	var str []byte
	for _, b := range(ciphered) {
		str = append(str, b.Byte())
	}
	return string(str)
}


// hasProblem59Property returns true if a string contains some common
// English words.
func hasProblem59Property(str string) bool {
	words := []string{"the ", "for ", "is ", "are "}
	found := 0
	for _, word := range(words) {
		if strings.Contains(string(str), word) {
			found++
			if found == len(words) {
				return true
			}
		}
	}
	return false
}


// readMessageFile reads the ciphered message into a slice of base 2
// sequences.
func readMessageFile(filename string) ([]base2.Base2, error) {
	// read
	file, err := ioutil.ReadFile(filename)
	if err!=nil {
		return nil, err
	}
	strs := strings.Split(string(file), ",")
	
	// convert to ints
	nums, err := atois(strs)
	if err!=nil {
		return nil, err
	}
	
	// return as base2s
	return intsToBins(nums), nil
}


// atois takes a slice of stringed ints and returns a slice of ints.
func atois(strs []string) ([]int, error) {
	nums := make([]int, len(strs))
	i := 0
	for _, str := range(strs) {
		x, err := strconv.Atoi(str)
		if err!=nil {
			return nil, err
		}
		nums[i] = x
		i++
	}
	return nums, nil
}


// intsToBins takes a slice of integers and returns a slice of each
// element's binary sequence.
func intsToBins(a []int) []base2.Base2 {
	bins := make([]base2.Base2, len(a))
	i := 0
	for _, n := range(a) {
		bins[i] = base2.New(n, 0)
		i++
	}
	return bins
}

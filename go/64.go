/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 64
 **********************************************************************/
package main
import "fmt"


func main() {
	totalOdds := 0
	n := 10000
	
	for i:=1; i<=n; i++ {
		//Generate continued fraction sequence of 'i'
		seq := getContinuedFraction(i)
		
		//Above func returns nil if 'i' is a perfect square
		if seq==nil {
			continue
		}

		//If len of sequence is odd, increment
		if len(seq)%2 > 0 {
			fmt.Printf("%d\t%d\n", i, len(seq))
			totalOdds++
		}
	}
	
	fmt.Println("totalOdds: ", totalOdds)
}

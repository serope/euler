/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 61
 **********************************************************************/
package main
import "fmt"


func main() {
	//Find all 4-digit triangles
	var masterList []uint
	var triangles []uint
	var n uint = 1
	var num uint = 0
	for (num <= 9999) {
		num = nthTriangularNum(n)
		if (is4Digits(num)) {
			triangles = append(triangles, num)
			
			if !linearSearch(masterList, num) {
				masterList = append(masterList, num)
			}
		}
		n++
	}
	
	//Find all 4-digit squares
	var squares []uint
	n = 1
	num = 0
	for (num <= 9999) {
		num = nthSquareNum(n)
		if (is4Digits(num)) {
			squares = append(squares, num)
			
			if !linearSearch(masterList, num) {
				masterList = append(masterList, num)
			}
		}
		n++
	}
	
	//Find all 4-digit pentagons
	var pentagons []uint
	n = 1
	num = 0
	for (num <= 9999) {
		num = nthPentagonalNum(n)
		if (is4Digits(num)) {
			pentagons = append(pentagons, num)
			
			if !linearSearch(masterList, num) {
				masterList = append(masterList, num)
			}
		}
		n++
	}
	
	
	//Find all 4-digit hexagons
	var hexagons []uint
	n = 1
	num = 0
	for (num <= 9999) {
		num = nthHexagonalNum(n)
		if (is4Digits(num)) {
			hexagons = append(hexagons, num)
			
			if !linearSearch(masterList, num) {
				masterList = append(masterList, num)
			}
		}
		n++
	}
	
	//Find all 4-digit heptagons
	var heptagons []uint
	n = 1
	num = 0
	for (num <= 9999) {
		num = nthHeptagonalNum(n)
		if (is4Digits(num)) {
			heptagons = append(heptagons, num)
			
			if !linearSearch(masterList, num) {
				masterList = append(masterList, num)
			}
		}
		n++
	}
	
	//Find all 4-digit octagons
	var octagons []uint
	n = 1
	num = 0
	for (num <= 9999) {
		num = nthOctagonalNum(n)
		if (is4Digits(num)) {
			octagons = append(octagons, num)
			
			if !linearSearch(masterList, num) {
				masterList = append(masterList, num)
			}
		}
		n++
	}

	
	/* 
	 * From the master list, remove all items whose third digit is 0
	 * 
	 * This reduces the list size by removing items which can't form
	 * cycles with other members
	 */
	index := 0
	for index<len(masterList) {
		digits := digitsOf(masterList[index])
		if digits[2]==0 {
			masterList = append(masterList[:index], masterList[index+1:]...)
			index = 0
		} else {
			index++
		}
	}
	
	
	//Solve the problem!
	var solutions [][]uint
	for _, x := range(masterList) {
		solution := []uint {x}
		i := 0
		
		for i<len(masterList) {
			if linearSearch(solution, masterList[i]) {
				i++
				continue
			}
			
			if hasCycle(solution[len(solution)-1], masterList[i]) {
				solution = append(solution, masterList[i])
			}
			i++
		}
		
		if len(solution) != 5 {
			continue
		}
		
		for _, y := range(masterList) {
			if hasCycle(solution[4], y) && hasCycle(y, solution[0]) {
				solution = append(solution, y)
				break
			}
		}
		
		if len(solution)==6 {
			solutions = append(solutions, solution)
		}
	}
	
	//Of all the possible solutions, find which one contains one
	//item from each list
	fmt.Println(solutions)
	for _, solution := range(solutions) {
		totalTriangles := 0
		totalSquares := 0
		totalPentagons := 0
		totalHexagons := 0
		totalHeptagons := 0
		totalOctagons := 0
		for _, x := range(solution) {
			if linearSearch(triangles, x) {
				totalTriangles++
			}
			if linearSearch(squares, x) {
				totalSquares++
			}
			if linearSearch(pentagons, x) {
				totalPentagons++
			}
			if linearSearch(hexagons, x) {
				totalHexagons++
			}
			if linearSearch(heptagons, x) {
				totalHeptagons++
			}
			if linearSearch(octagons, x) {
				totalOctagons++
			}
		}
			
		if totalTriangles==0 || totalSquares==0 || totalPentagons==0 || totalHexagons==0 || totalHeptagons==0 || totalOctagons==0 {
			continue
		} else {
			fmt.Println(solution)
			fmt.Printf("triangles: %d, squares: %d, pentagons: %d, hexagons: %d, heptagons: %d, octagons: %d \n", totalTriangles, totalSquares, totalPentagons, totalHexagons, totalHeptagons, totalOctagons)
			fmt.Printf("sum: %d \n", sum(solution))
		}
	}
}



/*
 * linearSearch()
 * 
 * Returns true if target is in set
 */
func linearSearch(set []uint, target uint) bool {
	for _, x := range(set) {
		if x==target {
			return true
		}
	}
	return false
}

/*
 * hasCycle()
 * 
 * Returns true if x's last 2 digits are y's first 2 digits
 */
func hasCycle(x, y uint) bool {
	digitsx := digitsOf(x)
	digitsy := digitsOf(y)
	if digitsx[2]==digitsy[0] && digitsx[3]==digitsy[1] {
		return true
	}
	return false
}

func is4Digits(x uint) bool {
	return (x>=1000 && x<=9999)
}

func nthTriangularNum(n uint) uint {
	return (n*(n+1))/2
}

func nthSquareNum(n uint) uint {
	return n*n
}

func nthPentagonalNum(n uint) uint {
	return (n*(3*n-1))/2
}

func nthHexagonalNum(n uint) uint {
	return n*(2*n-1)
}

func nthHeptagonalNum(n uint) uint {
	return (n*(5*n-3))/2
}

func nthOctagonalNum(n uint) uint {
	return n*(3*n-2)
}
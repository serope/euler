/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 61
 **********************************************************************/
package main

import (
	"fmt"
	"sort"
	"./euler"
)

func main() {
	// generate all geometric lists
	hep := makeHeptagons()
	hex := makeHexagons()
	oct := makeOctagons()
	pen := makePentagons()
	sqr := makeSquares()
	tri := makeTriangles()
	polys := [][]int{hep, hex, oct, pen, sqr, tri}
	
	// merge all, without repeats and without 3rd-zero terms
	unique := make(map[int]bool)
	for _, shapes := range(polys) {
		for _, shape := range(shapes) {
			digs := euler.Digits(shape)	// ignore if 3rd digit is zero
			if digs[2] == 0 {
				continue
			}
			unique[shape] = true
		}
	}
	
	// sort keys
	master := sortedKeys(unique)
	
	// brute force
	var solutions [][]int
	for _, x := range(master) {
		sol := []int{x}
		i := 0
		for i < len(master) {
			y := master[i]
			if euler.LSearch(sol, y) {
				i++
				continue
			} else if hasCycle(euler.Last(sol), y) {
				sol = append(sol, y)
				i = 0
				continue
			}
			i++
		}
		if len(sol) != 5 {
			continue
		}
		for _, y := range(master) {
			if hasCycle(euler.Last(sol), y) && hasCycle(y, x) {
				sol = append(sol, y)
				break
			}
		}
		if len(sol) == 6 {
			solutions = append(solutions, sol)
		}
	}
	fmt.Println(solutions)
	// which solution?
	for _, s := range(solutions) {
		if hasProblem61Property(s, polys) {
			fmt.Println(s)
		}
	}
}

// hasProblem61Property returns true if each element of the given
// potential solution has exactly 1 element from each set of polygonal
// terms.
func hasProblem61Property(sol []int, polys [][]int) bool {
	exists := make([]bool, len(polys))
	for _, x := range(sol) {
		for i, poly := range(polys) {
			if euler.BSearch(poly, x) {
				exists[i] = true
			}
		}
	}
	for _, e := range(exists) {
		if !e {
			return false
		}
	}
	return true
}

// findCycles takes a slice of cycles, c, and a pool of terms to pick
// from, a, and recursively locates a chain of cycles for x.
func findCycles(c []int, a []int) []int {
	fmt.Println(c)
	if len(c) == 6 {
		return c
	}
	
	for _, x := range(a) {
		if hasCycle(euler.Last(c), x) {
			c = append(c, x)
			c = findCycles(c, a)
			if len(c) == 6 {
				break
			}
		}
	}
	
	return nil
}

// hasCycle returns true if x's last 2 digits are the same as y's first
// 2 digits.
func hasCycle(x, y int) bool {
	a := euler.Digits(x)
	b := euler.Digits(y)
	if a[2] == b[0] && a[3] == b[1] {
		return true
	}
	return false
}

// makeTriangles returns a slice of all 4-digit triangular numbers.
func makeTriangles() []int {
	var triangles []int
	t := 0
	n := 1
	for n <= 9999 {
		t += n
		n++
		if is4Digits(t) {
			triangles = append(triangles, t)
		}
	}
	return triangles
}

// makeSquares returns a slice of all 4-digit square numbers.
func makeSquares() []int {
	var squares []int
	n := 1
	s := nthSquare(n)
	for s <= 9999 {
		s = nthSquare(n)
		n++
		if is4Digits(s) {
			squares = append(squares, s)
		}
	}
	return squares
}

// makePentagons returns a slice of all 4-digit pentagonal numbers.
func makePentagons() []int {
	var pentagons []int
	n := 1
	p := nthPentagon(n)
	for p <= 9999 {
		p = nthPentagon(n)
		n++
		if is4Digits(p) {
			pentagons = append(pentagons, p)
		}
	}
	return pentagons
}

// makeHexagons returns a slice of all 4-digit hexagonal numbers.
func makeHexagons() []int {
	var hexagons []int
	n := 1
	h := nthHexagon(n)
	for h <= 9999 {
		h = nthHexagon(n)
		n++
		if is4Digits(h) {
			hexagons = append(hexagons, h)
		}
	}
	return hexagons
}

// makeHeptagons returns a slice of all 4-digit heptagonal numbers.
func makeHeptagons() []int {
	var heptagons []int
	n := 1
	h := nthHeptagon(n)
	for h <= 9999 {
		h = nthHeptagon(n)
		n++
		if is4Digits(h) {
			heptagons = append(heptagons, h)
		}
	}
	return heptagons
}

// makeOctagons returns a slice of all 4-digit octagonal numbers.
func makeOctagons() []int {
	var octagons []int
	n := 1
	o := nthOctagon(n)
	for o <= 9999 {
		o = nthOctagon(n)
		n++
		if is4Digits(o) {
			octagons = append(octagons, o)
		}
	}
	return octagons
}

// sortedKeys returns a sorted slice of m's keys.
func sortedKeys(m map[int]bool) []int {
	a := make([]int, len(m))
	i := 0
	for x, _ := range(m) {
		a[i] = x
		i++
	}
	sort.Ints(a)
	return a
}

// is4Digits returns true if x consists of four digits.
func is4Digits(x int) bool {
	return (x>=1000 && x<=9999)
}

// nthTriangle returns the nth triangular number.
func nthTriangle(n int) int {
	return (n*(n+1))/2
}

// nthSquare returns the nth square number.
func nthSquare(n int) int {
	return n*n
}

// nthPentagon returns the nth pentagonal number.
func nthPentagon(n int) int {
	return (n*(3*n-1))/2
}

// nthHexagon returns the nth hexagonal number.
func nthHexagon(n int) int {
	return n*(2*n-1)
}

// nthHeptagon returns the nth heptagonal number.
func nthHeptagon(n int) int {
	return (n*(5*n-3))/2
}

// nthOctagon returns the nth octagonal number.
func nthOctagon(n int) int {
	return n*(3*n-2)
}

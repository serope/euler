// progress
// An overengineered utility for recording Project Euler progress into a
// table in GitHub readme format.
package main

import (
	"os"
	"fmt"
	"sort"
)

var (
	dirs = []string{"c"} // directories where solutions exist
)

func main() {
	// read problems
	problems, err := readProblemsFile("problem_names.json")
	if err!=nil {
		panic(err)
	}
	
	// read solution files
	solutions := make(map[int]*Solution)
	for _, dir := range(dirs) {
		err := readSolutionFiles(dir, solutions)
		if err!=nil {
			panic(err)
		}
	}
	nums := sortedSolutionKeys(solutions)
	
	// read supplement files
	supplements := make(map[int]string)
	for _, dir := range(dirs) {
		err := readSupplementFiles(dir, supplements)
		if err!=nil {
			panic(err)
		}
	}
	
	// check 'bin' dir
	err = goToBin()
	if err!=nil {
		panic(err)
	}
	
	// build all
	for _, num := range(nums) {
		err := solutions[num].build(supplements[num])
		if err!=nil {
			panic(err)
		}
	}
	
	// time all
	for _, num := range(nums) {
		err := solutions[num].computeTimes()
		if err!=nil {
			panic(err)
		}
	}
	
	// end
	pnums := sortedProblemKeys(problems)
	for _, pnum := range(pnums) {
		printRow(problems[pnum], solutions[pnum], pnum)
		fmt.Print("\n")
	}
}

func sortedProblemKeys(m map[int]Problem) []int {
	keys := make([]int, len(m))
	i := 0
	for key, _ := range(m) {
		keys[i] = key
		i++
	}
	sort.Ints(keys)
	return keys
}

func sortedSolutionKeys(m map[int]*Solution) []int {
	keys := make([]int, len(m))
	i := 0
	for key, _ := range(m) {
		keys[i] = key
		i++
	}
	sort.Ints(keys)
	return keys
}

func goToBin() error {
	err := os.Chdir("..")
	if err!=nil {
		return err
	}
	err = os.Chdir("bin")
	if err!=nil {
		str := "Create \"bin\" directory at root first \n"
		return fmt.Errorf("%s \n %s", err.Error(), str)
	}
	return nil
}

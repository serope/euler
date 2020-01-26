// problem.go defines the Problem type.
package main

import (
	"strconv"
	"io/ioutil"
	"encoding/json"
)

type Problem struct {
	name	string
	url		string
}

// readProblemsFile reads a JSON file containing problem names and
// numbers and returns a map of Problem objects.
func readProblemsFile(jsonfile string) (map[int]Problem, error) {
	file, err := ioutil.ReadFile(jsonfile)
	if err!=nil {
		return nil, err
	}
	
	unmarsh := make(map[int]string)
	json.Unmarshal(file, &unmarsh)
	
	problems := make(map[int]Problem)
	for num, name := range(unmarsh) {
		url := "https://projecteuler.net/problem=" + strconv.Itoa(num)
		problems[num] = Problem{name, url}
	}
	return problems, nil
}

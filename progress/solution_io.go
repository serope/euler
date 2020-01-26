// solution_io.go contains functions for reading solution files.
package main

import (
	"strings"
	"strconv"
	"io/ioutil"
)

// readSolutionFiles reads the given directory and adds solution files
// to the given map. A solution file is named ##.x, where ## is a
// 2-digit problem number and x is its file extension (which should also
// be the name of the directory).
func readSolutionFiles(dir string, solutions map[int]*Solution) error {
	files, err := ioutil.ReadDir("../" + dir)
	if err!=nil {
		return err
	}
	for _, file := range(files) {
		name := file.Name()
		if isSolutionFile(name, dir) {
			num, lang := parseSolutionFilename(name)
			s := &Solution{name:name, bin:name[0:2], lang:lang}
			s.setCmd()
			solutions[num] = s
		}
	}
	return nil
}

// isSolutionFile returns true if the given filename is in the form
// "##.x".
func isSolutionFile(name, ext string) bool {
	_, err := strconv.Atoi(name[0:2])
	if err!=nil || !strings.HasSuffix(name, "." + ext){
		return false
	}
	return len(name) == 3 + len(ext)
}

// parseSolutionFilename takes a string like "03.c" and returns 3 and
// "c".
func parseSolutionFilename(name string) (int, string) {
	split := strings.Split(name, ".")
	num, _ := strconv.Atoi(split[0])
	ext := split[1]
	return num, ext
}

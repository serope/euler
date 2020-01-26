// supplement.go handles supplementary files that are provided with some
// problems, e.g. "18_triangles" for problem 18.
package main

import (
	"strings"
	"strconv"
	"io/ioutil"
)

// readSupplementFiles reads the given directory and adds supplement
// files to the given map. Supplement files named "##_abcd" where ## is
// a 2-digit problem number and abcd is arbitrary.
func readSupplementFiles(dir string, supplements map[int]string) error {
	files, err := ioutil.ReadDir("../" + dir)
	if err!=nil {
		return err
	}
	for _, file := range(files) {
		name := file.Name()
		if isSupplementFile(name, dir) {
			num, err := strconv.Atoi(name[0:2])
			if err!=nil {
				return err
			}
			supplements[num] = name
		}
	}
	return nil
}


// isSupplementFile returns true if the given filename is in the form
// "##_abcd".
func isSupplementFile(name, dir string) bool {
	_, err := strconv.Atoi(name[0:2])
	if err!=nil || strings.HasSuffix(name, "." + dir){
		return false
	}
	return name[2] == '_'
}

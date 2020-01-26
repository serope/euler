// time.go contains functions for timing solutions.
package main

import (
	"os/exec"
	"strings"
	"fmt"
)


// executionTime executes the given solution and returns a slice with the
// real time, user time, system time, and CPU usage, in that order.
func executionTime(s *Solution) ([]string, error) {
	cmd := exec.Command("/usr/bin/time",
						"--format",
						"real:%e\nuser:%U\nsys:%S\ncpu:%P",
						"../bin/" + s.bin)
	out, err := cmd.CombinedOutput()
	if err!=nil {
		fmt.Println("executionTime failed on ", s.name)
		fmt.Println(err.Error())
		return nil, err
	}
	return parseTime(string(out)), nil
}

// parseTime takes stderr output from /usr/bin/time (not Bash time) and
// returns a slice with the real time, user time, system time, and CPU
// usage, in that order.
func parseTime(output string) []string {
	out := strings.Split(output, "\n")
	times := make([]string, 4)
	for _, item := range(out) {
		if strings.Contains(item, "real:") {
			times[0] = strings.Replace(item, "real:", "", 1)
		} else if strings.Contains(item, "user:") {
			times[1] = strings.Replace(item, "user:", "", 1)
		} else if strings.Contains(item, "sys:") {
			times[2] = strings.Replace(item, "sys:", "", 1)
		} else if strings.Contains(item, "cpu:") {
			times[3] = strings.Replace(item, "cpu:", "", 1)
		}
	}
	return times
}

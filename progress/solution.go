// solution.go defines the Solution type.
package main

import (
	"fmt"
	"os"
	"os/exec"
)

type Solution struct {
	name	string		// source filename
	bin		string		// compiled bin filename
	lang	string		// programming language (also directory)
	cmd		*exec.Cmd	// build/compile command (see setCmd)
	
	real	string		// time: real
	user	string		// time: user
	sys		string		// time: system/kernel
	cpu		string		// CPU usage
}


// setCmd sets a solution's build command.
func (s *Solution) setCmd() {
	switch s.lang {
		case "c":
			s.cmd = exec.Command("make", s.bin)
		case "go":
			s.cmd = exec.Command("go", "build", s.name)
	}
}


// build builds a solution, moves the resulting binary to /bin and, if
// a supplement file is provided, copies it to /bin as well.
func (s *Solution) build(supplement string) error {
	// chdir
	fmt.Printf("%s \t chdir ", s.name)
	err := os.Chdir("../" + s.lang)
	if err!=nil {
		return err
	}
	
	// build
	fmt.Print("build ")
	err = s.cmd.Run()
	if err!=nil {
		msg := "either failed to compile or no 'bin' directory in root"
		return fmt.Errorf("%s\n%s\n%s\n", err.Error(), s.name, msg)
	}
	
	// move
	fmt.Print("move ")
	mv := exec.Command("mv", s.bin, "../bin")
	err = mv.Run()
	if err!=nil {
		return err
	}
	
	// copy supplement
	if supplement != "" {
		fmt.Print("copy ", supplement)
		cp := exec.Command("cp", supplement, "../bin")
		err := cp.Run()
		if err!=nil {
			return err
		}
	}
	fmt.Print("\n")
	return nil
}


// computeTimes runs a solution and, based on the result, sets the
// resource usage data (real time, user time, system time, and CPU
// usage).
func (s *Solution) computeTimes() error {
	fmt.Printf("%s \t", s.name)
	times, err := executionTime(s)
	if err!=nil {
		return err
	}
	s.real = times[0]
	s.user = times[1]
	s.sys = times[2]
	s.cpu = times[3]
	fmt.Printf("r%s, u%s, s%s, c%s \n", s.real, s.user, s.sys, s.cpu)
	return nil
}

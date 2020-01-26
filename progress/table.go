// table.go contains functions for printing the final output for the
// GitHub readme.
package main

import "fmt"

var (
	username	= "serope"
	reponame	= "euler"
)

// printRow takes a problem, a solution, and their number, and prints the
// appropriate markdown for a GitHub readme table.
func printRow(p Problem, s *Solution, i int) {
	if s == nil {
		fmt.Printf("%d | [%s](%s) | | | | | |", i, p.name, p.url)
	} else {
		link := "https://github.com/%s/%s/blob/master/%s/%s"
		link = fmt.Sprintf(link, username, reponame, s.lang, s.name)
		row := "%d | [%s](%s) | [%s](%s) | %s | %s | %s | %s"
		fmt.Printf(row, i, p.name, p.url, s.name, link, s.real, s.user,
															s.sys, s.cpu)
	}
}

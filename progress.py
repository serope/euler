# Project Euler
# progress.py
# This script builds each solution file, runs it, measures its time and
# memory performance, and prints the results into a GitHub markdown
# table.
#
#! /usr/bin/env python3
import os
import subprocess
import json

# languages/directories and their build commands
commands = {
	'c':	'make XX',
	'go':	'go build XX.go'
}

def main(args):
	print('Hello!')
	solutions = get_solution_files()
	reports = {}
	for s in solutions:
		print(s)
		result = get_performance_report(s)
		reports[s] = result
	
	probnames = get_problem_names('problem_names.json')
	rows = create_github_table(reports, probnames)
	rows = fill_missing(rows, reports, probnames)
	
	print('&#35; | Problem | File | Elapsed | User | Sys | Peak memory (MB)')
	print('----- | --------| ---- | ------- | ---- | --- | ----------------')
	for r in rows:
		print(r)
	
	return 0


def fill_missing(rows: list, reports: dict, problem_names: dict) -> list:
	"""Fill in empty rows for problems that don't have solutions."""
	solved_problems = []
	for r in reports:
		pair = r.split('.')
		num = int(pair[0])
		solved_problems.append(str(num))
	
	for num in problem_names:
		if num not in solved_problems:
			rows.append(create_empty_table_row(num, problem_names[num]))
	
	rows.sort()
	return rows
		

def create_github_table(reports: dict, problem_names: dict) -> list:
	"""
	Return a GitHub markdown progress table as a list of row strings.
	"""
	rows = []
	for r in reports:
		problem_no = int(r.split('.')[0])
		row = create_github_table_row(r, reports[r], problem_names[str(problem_no)])
		rows.append(row)
	return rows


def create_github_table_row(solution_filename: str, report: dict, problem_name: str) -> str:
	"""
	Return a table row for this problem.
	"""
	pair = solution_filename.split('.')
	problem_no = pair[0]
	extension = pair[1]
	problem_url = 'https://projecteuler.net/problem=' + problem_no
	solution_url = 'https://github.com/serope/euler/blob/master/' + extension + '/' + solution_filename
	mem_mb = str(int(report['mem']) / 1000)
	
	s = '{} | [{}]({}) | [{}]({}) | {} | {} | {} | {}'
	elems = [problem_no, problem_name, problem_url, solution_filename, solution_url, report['real'], report['user'], report['sys'], mem_mb]
	for e in elems:
		s = s.replace('{}', e, 1)
	return s


def create_empty_table_row(problem_no: str, problem_name: str) -> str:
	"""
	Return the table row for a problem that doesn't have a solution.
	"""
	problem_url = 'https://projecteuler.net/problem=' + problem_no
	s = '{} | [{}]({}) | | | | | |'
	elems = [problem_no, problem_name, problem_url]
	for e in elems:
		s = s.replace('{}', e, 1)
	return s


def get_problem_names(filename: str) -> dict:
	"""Return a dictionary of each problem's number and name."""
	f = open(filename, 'r')
	j = json.load(f)
	f.close()
	return j


def build_solution(solution_filename: str) -> int:
	"""
	Build the given solution. Return the build command's exit status.
	"""
	pair = solution_filename.split('.')
	cmd = commands[pair[1]].replace('XX', pair[0])
	cmd = cmd.split(' ')
	process = subprocess.run(cmd)
	return process.returncode


def measure_solution(bin_filename: str) -> dict:
	"""
	Run the given bin with GNU time and return its time and memory
	measurements, or None if an error occurs.
	"""
	cmd = ["/usr/bin/time", '-v', './' + bin_filename]
	out = subprocess.DEVNULL
	err = subprocess.PIPE
	process = subprocess.run(cmd, stdout=out, stderr=err)
	if process.returncode != 0:
		return None
	return parse_performance_report(str(process.stderr))


def rm(filename: str) -> int:
	"""Invoke rm to delete a file. Return its exit status."""
	process = subprocess.run(['rm', filename])
	return process.returncode


def get_performance_report(solution_filename: str) -> dict:
	"""
	Build the given solution file, record its performance with GNU time,
	and then delete the bin. Return a dictionary containing the results,
	or None if any error occurs.
	"""
	pair = solution_filename.split('.')				# 04.c -> [04, c]
	os.chdir(pair[1])								# cd
	exit_code = build_solution(solution_filename)	# build
	if exit_code != 0:
		return None
	report = measure_solution(pair[0])				# measure
	exit_code = rm(pair[0])							# delete bin
	if exit_code != 0:
		return None
	os.chdir('..')									# cd
	return report									# end


def get_build_command(solution: str) -> str:
	"""Return the build command for this solution."""
	pair = solution.split('.')
	return commands[pair[1]].replace('XX', pair[0])


def parse_performance_report(gnutime_stderr: str) -> dict:
	"""
	Take the stderr of GNU time and parse it into a dictionary containing
	four items: real time, user time, system/kernel time, and peak memory
	usage.
	"""
	strings = {
		'real':	'Elapsed (wall clock) time (h:mm:ss or m:ss): ',
		'user': 'User time (seconds): ',
		'sys':	'System time (seconds): ',
		'mem':	'Maximum resident set size (kbytes): '
	}
	
	out = {}
	san = sanitize_gnutime_stderr(gnutime_stderr)
	lines = san.split('\n')
	for l in lines:
		for s in strings:
			if strings[s] in l:
				out[s] = l.replace(strings[s], '')
	return out


def sanitize_gnutime_stderr(gnutime_stderr: str) -> str:
	"""Clean GNU time's stderr into a human-readable string."""
	san = gnutime_stderr.replace('\\n', '\n')
	san = san.replace('\\t', '\t')
	san = san.replace('\\', '')
	san = san.replace('\t', '')
	return san


def get_solution_files() -> list:
	"""Return a sorted list of all solution files."""
	solutions = []
	for c in commands:
		os.chdir(c)
		files = os.listdir()
		for f in files:
			if is_solution_file(f, c):
				solutions.append(f)
		os.chdir('..')
	solutions.sort()
	return solutions


def is_solution_file(filename: str, pwd: str) -> bool:
	"""
	Return true if the given filename is in the form xx.y, where xx is
	a two-digit number and y is its extension, the latter of which should
	be the same as the directory in which it resides.
	"""
	pair = filename.split('.')
	if len(pair) is not 2:
		return False
	elif not pair[0].isnumeric():
		return False
	elif not pair[1] == pwd:
		return False
	return True


if __name__ == '__main__':
	import sys
	sys.exit(main(sys.argv))

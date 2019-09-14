#!/usr/bin/env python
# README checklist generator for Project Euler

def main(args):
	# Check if bins exist
	if not os.path.exists('bin'):
		print('Please run \"python compile.py all\" first.')
		return 0
	
	# Change dir
	os.chdir('bin')
	
	# Get list of files
	files = os.listdir('.')
	
	# Filter executables (i.e. files with no extension)
	bins = []
	for x in files:
		if x.find('.')==-1:
			bins.append(x)
	
	# Sort
	bins.sort()
	
	# Record each bin's runtime
	timeLines = []
	for x in bins:
		# Create a timing script for this bin
		createTimeScript(x)
		
		# Execute script
		print(x)
		status = subprocess.call(['bash', 'record.sh'])
		
		# OK?
		if not status==0:
			print("Execution failed\nExit")
			return 0
		
		# Get real, user, and sys times
		times = getRecordedTimes()
		print('real: ' + times[0])
		print('user: ' + times[1])
		print('sys:  ' + times[2])
		print('\n')
		
		# Format for GitHub README.MD
		line = ' ' + times[0] + ' | ' + times[1] + ' | ' + times[2]
		timeLines.append(line)
	
	# Cleanup
	os.remove('record.sh')
	os.remove('record.txt')
	
	# Get checklist.txt
	os.chdir('..')
	text = fileToString('checklist.txt')
	
	# Split text by newlines
	lines = text.split('\n')
	
	# Print timeLines with lines
	i = 0
	for line in lines:
		if line.find('https://github.com/') != -1:
			print(line + timeLines[i] + '\b')
			i += 1
		else:
			print(line)
	
	#End
	date = time.strftime('%Y %b %d (%a) @ %H:%M')
	bye = 'This list was generated on \'' + date + '\'!'
	print(bye)
	return 0





def createTimeScript(x):
	# Create file
	newfile = open('record.sh', 'w')
	
	# Write text to file
	text = '#!/usr/bin/bash' + '\n' + '(time ./' + x + ') > record.txt 2>&1'
	newfile.write(text)
	
	# Close
	newfile.close()





def fileToString(filename):
	f = open(filename, 'r')
	text = f.read()
	f.close()
	return text





def getRecordedTimes():
	# Get text
	text = fileToString('record.txt')
	
	# Split by newlines
	lines = text.split('\n')
	
	# Get last 3 lines
	real = lines[len(lines)-4]
	user = lines[len(lines)-3]
	sys = lines[len(lines)-2]
	
	# Clean
	real = real.replace('real\t', '')
	real = real.replace('0m', '')
	user = user.replace('user\t', '')
	user = user.replace('0m', '')
	sys = sys.replace('sys\t', '')
	sys = sys.replace('0m', '')
	return [real, user, sys]







if __name__ == '__main__':
	import sys
	import os
	import subprocess
	import time
	sys.exit(main(sys.argv))

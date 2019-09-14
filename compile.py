#!/usr/bin/env python
# Compilation script for Project Euler solutions

def main(args):
	if len(args)!=2:
		help()
		return 0
	
	table = {
		'01' : 'gcc 01.c euler.c -o 01',
		'02' : 'gcc 02.c euler.c -o 02',
		'03' : 'gcc 03.c euler.c -o 03',
		'04' : 'gcc 04.c euler.c -o 04',
		'05' : 'gcc 05.c -o 05',
		'06' : 'gcc 06.c -o 06',
		'07' : 'gcc 07.c euler.c -o 07',
		'08' : 'gcc 08.c euler.c -o 08',
		'09' : 'gcc 09.c euler.c -o 09',
		'10' : 'gcc 10.c euler.c -o 10',
		'11' : 'gcc 11.c euler.c -o 11',
		'12' : 'gcc 12.c euler.c -pthread -o 12',
		'13' : 'gcc 13.c euler_bignum.c -o 13',
		'14' : 'gcc 14.c euler.c -o 14',
		'15' : '',
		'16' : 'gcc 16.c euler_bignum.c -o 16',
		'17' : 'gcc 17.c -o 17',
		'18' : 'gcc 18.c euler.c -o 18',
		'19' : 'gcc 19.c -o 19',
		'20' : 'gcc 20.c euler_bignum.c -o 20',
		'21' : 'gcc 21.c euler.c -o 21',
		'22' : 'gcc 22.c -o 22',
		'23' : 'gcc 23.c euler.c -o 23',
		'24' : 'gcc 24.c euler.c -o 24',
		'25' : 'gcc 25.c euler_bignum.c -o 25',
		'26' : '',
		'27' : 'gcc 27.c euler.c -o 27',
		'28' : 'gcc 28.c -o 28',
		'29' : 'gcc 29.c euler_bignum.c -o 29',
		'30' : 'gcc 30.c euler.c -o 30',
		'31' : 'gcc 31.c -o 31',
		'32' : 'gcc 32.c euler.c -o 32',
		'33' : 'gcc 33.c -o 33',
		'34' : 'gcc 34.c euler.c -o 34',
		'35' : 'gcc 35.c euler.c -o 35',
		'36' : 'gcc 36.c euler.c euler_binary.c -o 36',
		'37' : 'gcc 37.c euler.c -o 37',
		'38' : 'gcc 38.c euler.c -o 38',
		'39' : 'gcc 39.c euler.c -o 39',
		'40' : 'gcc 40.c euler.c -o 40',
		'41' : 'gcc 41.c euler.c -o 41',
		'42' : 'gcc 42.c -o 42',
		'43' : 'gcc 43.c -o 43',
		'44' : 'gcc 44.c euler.c -pthread -o 44',
		'45' : 'gcc 45.c -o 45',
		'46' : 'gcc 46.c euler.c -lm -o 46',
		'47' : 'gcc 47.c euler.c -o 47',
		'48' : 'gcc 48.c euler_bignum.c -o 48',
		'49' : 'gcc 49.c euler.c -o 49',
		'50' : 'gcc 50.c euler.c -o 50',
		'51' : 'gcc 51.c euler.c euler_binary.c -o 51',
		'52' : 'gcc 52.c euler.c -o 52',
		'53' : 'gcc 53.c -o 53',
		'54' : 'gcc 54.c euler.c -o 54',
		'55' : 'gcc 55.c euler_bignum.c -o 55',
		'56' : 'gcc 56.c euler_bignum.c -o 56',
		'57' : 'gcc 57.c euler_bignum.c -o 57',
		
		'58' : 'go build 58.go',
		'59' : 'go build 59.go euler.go',
		'60' : 'go build 60.go euler.go',
		'61' : 'go build 61.go euler.go',
		'62' : 'go build 62.go',
		'63' : 'go build 63.go',
		'64' : 'go build 64.go euler.go',
		'65' : 'go build 65.go',
		'66' : 'go build 66.go euler.go',
		'67' : '',
		'68' : 'go build 68.go'
	}
	
	# If 'all'
	if args[1]=='all':
		# Sort table by keys
		keys = []
		for key in table:
			keys.append(key)
		keys.sort()
		
		# Compile all
		for key in keys:
			os.system('python compile.py ' + key)
		return 0
	
	# Does the solution exist?
	if table[args[1]]=='':
		print(args[1] + ':\t:(')
		return 0
	
	# Create bin dir, if necessary
	if not os.path.exists('bin'):
		os.mkdir('bin')
	
	# Change to src dir
	if int(args[1]) < 58:
		os.chdir('c')
	else:
		os.chdir('go')
	
	# Compile
	print(args[1] + ':\t' + table[args[1]])
	status = os.system(table[args[1]])
	
	# OK?
	if not status==0:
		print('Compilation failed\nExit')
		return 0
	
	# Move file to bin dir
	os.system('mv ' + args[1] + ' ../bin')
	
	# Copy any additional files
	files = os.listdir('.')
	for x in files:
		if x.find(args[1] + "_") != -1:
			print("\tcp " + x)
			os.system('cp ' + args[1] + '_* ../bin')
	
	return 0





def help():
	print('Usage: \t compile.py X, where X is: \n')
	print('       \t - a two-digit problem number')
	print('       \t - all, which compiles every file \n')
	print('Ex:    \t compile.py 05')
	print('       \t compile.py all')





if __name__ == '__main__':
	import sys
	import os
	sys.exit(main(sys.argv))


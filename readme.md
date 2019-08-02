# euler_rpi
These are my Project Euler solutions written and timed on a Raspberry Pi 3B. The 3B is quite a weak machine, so run times are roughly 5-10x longer than they would be on a typical desktop PC.

1-57 are in C; the rest are in Go.


## Checklist
&#35; | Problem | File | Compilation | User time
----- | --------| ---- | ----------- | ---------
1 | [Multiples of 3 and 5](https://projecteuler.net/problem=1) | [01.c](https://github.com/serope/euler_rpi/blob/master/c/01.c) | `gcc 01.c euler.c` | 0.001s
2 | [Even Fibonacci numbers](https://projecteuler.net/problem=2) | [02.c](https://github.com/serope/euler_rpi/blob/master/c/02.c) | `gcc 02.c euler.c` | 0.003s
3 | [Largest prime factor](https://projecteuler.net/problem=3) | [03.c](https://github.com/serope/euler_rpi/blob/master/c/03.c) | `gcc 03.c euler.c` | 0.560s
4 | [Largest palindrome product](https://projecteuler.net/problem=4) | [04.c](https://github.com/serope/euler_rpi/blob/master/c/04.c) | `gcc 04.c euler.c` | 0.440s
5 | [Smallest multiple](https://projecteuler.net/problem=5) | [05.c](https://github.com/serope/euler_rpi/blob/master/c/05.c) | `gcc 05.c euler.c` | 0.328s
6 | [Sum square difference](https://projecteuler.net/problem=6) | [06.c](https://github.com/serope/euler_rpi/blob/master/c/06.c) | `gcc 06.c` | 0.003s
7 | [10001st prime](https://projecteuler.net/problem=7) | [07.c](https://github.com/serope/euler_rpi/blob/master/c/07.c) | `gcc 07.c euler.c` | 0.394s
8 | [Largest product in a series](https://projecteuler.net/problem=8) | [08.c](https://github.com/serope/euler_rpi/blob/master/c/08.c) | `gcc 08.c euler.c` | 0.003s
9 | [Special Pythagorean triplet](https://projecteuler.net/problem=9) | [09.c](https://github.com/serope/euler_rpi/blob/master/c/09.c) | `gcc 09.c euler.c` | 3.174s
10 | [Summation of primes](https://projecteuler.net/problem=10) | [10.c](https://github.com/serope/euler_rpi/blob/master/c/10.c) | `gcc 10.c euler.c` | 0.826s
11 | [Largest product in a grid](https://projecteuler.net/problem=11) | [11.c](https://github.com/serope/euler_rpi/blob/master/c/11.c) | `gcc 11.c euler.c` | 0.833s
12 | [Highly divisible triangular number](https://projecteuler.net/problem=12) | [12.c](https://github.com/serope/euler_rpi/blob/master/c/12.c) | `gcc 12.c euler.c` | 10.581s
13 | [Large sum](https://projecteuler.net/problem=13) | [13.c](https://github.com/serope/euler_rpi/blob/master/c/13.c) | `gcc 13.c euler_bignum.c` | 0.001s
14 | [Longest Collatz sequence](https://projecteuler.net/problem=14) | [14.c](https://github.com/serope/euler_rpi/blob/master/c/14.c) | `gcc 14.c euler.c` | 0.423s
15 | [Lattice paths](https://projecteuler.net/problem=15) | | | |
16 | [Power digit sum](https://projecteuler.net/problem=16) | [16.c](https://github.com/serope/euler_rpi/blob/master/c/16.c) | `gcc 16.c euler_bignum.c` | 0.104s
17 | [Number letter counts](https://projecteuler.net/problem=17) | [17.c](https://github.com/serope/euler_rpi/blob/master/c/17.c) | `gcc 17.c` | 0.010s
18 | [Maximum path sum I](https://projecteuler.net/problem=18) | [18.c](https://github.com/serope/euler_rpi/blob/master/c/18.c) | `gcc 18.c euler.c` | 0.014s
19 | [Counting Sundays](https://projecteuler.net/problem=19) | [19.c](https://github.com/serope/euler_rpi/blob/master/c/19.c) | `gcc 19.c` | 0.010s
20 | [Factorial digit sum](https://projecteuler.net/problem=20) | [20.c](https://github.com/serope/euler_rpi/blob/master/c/20.c) | `gcc 20.c euler_bignum.c` | 0.015s
21 | [Amicable numbers](https://projecteuler.net/problem=21) | [21.c](https://github.com/serope/euler_rpi/blob/master/c/21.c) | `gcc 21.c euler.c` | 3.486s
22 | [Names scores](https://projecteuler.net/problem=22) | [22.c](https://github.com/serope/euler_rpi/blob/master/c/22.c) | `gcc 22.c` | 0.053s | 0.031s
23 | [Non-abundant sums](https://projecteuler.net/problem=23) | [23.c](https://github.com/serope/euler_rpi/blob/master/c/23.c) | `gcc 23.c euler.c` | 6.910s
24 | [Lexicographic permutations](https://projecteuler.net/problem=24) | [24.c](https://github.com/serope/euler_rpi/blob/master/c/24.c) | `gcc 24.c euler.c` | 0.005s
25 | [1000-digit Fibonacci number](https://projecteuler.net/problem=25) | [25.c](https://github.com/serope/euler_rpi/blob/master/c/25.c) | `gcc 25.c euler_bignum.c` | 0.412s
26 | [Reciprocal cycles](https://projecteuler.net/problem=26) | | | |
27 | [Quadratic primes](https://projecteuler.net/problem=27) | [27.c](https://github.com/serope/euler_rpi/blob/master/c/27.c) | `gcc 27.c euler.c` | 5.095s
28 | [Number spiral diagonals](https://projecteuler.net/problem=28) | [28.c](https://github.com/serope/euler_rpi/blob/master/c/28.c) | `gcc 28.c` | 0.003s | 0.001s
29 | [Distinct powers](https://projecteuler.net/problem=29) | [29.c](https://github.com/serope/euler_rpi/blob/master/c/29.c) | `gcc 29.c euler_bignum.c` | 19.955s
30 | [Digit fifth powers](https://projecteuler.net/problem=30) | [30.c](https://github.com/serope/euler_rpi/blob/master/c/30.c) | `gcc 30.c euler.c` | 0.279s
31 | [Coin sums](https://projecteuler.net/problem=31) | [31.c](https://github.com/serope/euler_rpi/blob/master/c/31.c) | `gcc 31.c` | 0.455s
32 | [Pandigital products](https://projecteuler.net/problem=32) | [32.c](https://github.com/serope/euler_rpi/blob/master/c/32.c) | `gcc 32.c euler.c` | 3.678s
33 | [Digit cancelling fractions](https://projecteuler.net/problem=33) | [33.c](https://github.com/serope/euler_rpi/blob/master/c/33.c) | `gcc 33.c` | 0.013s
34 | [Digit factorials](https://projecteuler.net/problem=34) | [34.c](https://github.com/serope/euler_rpi/blob/master/c/34.c) | `gcc 34.c euler.c` | 1.688s
35 | [Circular primes](https://projecteuler.net/problem=35) | [35.c](https://github.com/serope/euler_rpi/blob/master/c/35.c) | `gcc 35.c euler.c` | 7.440s
36 | [Double-base palindrome](https://projecteuler.net/problem=36) | [36.c](https://github.com/serope/euler_rpi/blob/master/c/36.c) | `gcc 36.c euler.c euler_binary.c` | 1.177s
37 | [Truncatable primes](https://projecteuler.net/problem=37) | [37.c](https://github.com/serope/euler_rpi/blob/master/c/37.c) | `gcc 37.c euler.c` | 0.665s
38 | [Pandigital multiples](https://projecteuler.net/problem=38) | [38.c](https://github.com/serope/euler_rpi/blob/master/c/38.c) | `gcc 38.c euler.c` | 0.123s
39 | [Integer right triangles](https://projecteuler.net/problem=39) | [39.c](https://github.com/serope/euler_rpi/blob/master/c/39.c) | `gcc 39.c euler.c` | 6.934s
40 | [Champernowne's constant](https://projecteuler.net/problem=40) | [40.c](https://github.com/serope/euler_rpi/blob/master/c/40.c) | `gcc 40.c euler.c` | 0.221s
41 | [Pandigital prime](https://projecteuler.net/problem=41) | [41.c](https://github.com/serope/euler_rpi/blob/master/c/41.c) | `gcc 41.c euler.c` | 4.759s
42 | [Coded triangle numbers](https://projecteuler.net/problem=42) | [42.c](https://github.com/serope/euler_rpi/blob/master/c/42.c) | `gcc 42.c` | 0.008s
43 | [Sub-string divisibility](https://projecteuler.net/problem=43) | [43.c](https://github.com/serope/euler_rpi/blob/master/c/43.c) | `gcc 43.c` | 0.045s
44 | [Pentagon numbers](https://projecteuler.net/problem=44) | [44.c](https://github.com/serope/euler_rpi/blob/master/c/44.c) | `gcc 44.c euler.c` | 1m27.282s :(
45 | [Triangular, pentagonal, and hexagonal](https://projecteuler.net/problem=45) | [45.c](https://github.com/serope/euler_rpi/blob/master/c/45.c) | `gcc 45.c` | 0.329s
46 | [Golbach's other conjecture](https://projecteuler.net/problem=46) | [46.c](https://github.com/serope/euler_rpi/blob/master/c/46.c) | `gcc 46.c euler.c -lm` | 0.179s
47 | [Distinct primes factors](https://projecteuler.net/problem=47) | [47.c](https://github.com/serope/euler_rpi/blob/master/c/47.c) | `gcc 47.c euler.c` | 26.606s
48 | [Self powers](https://projecteuler.net/problem=48) | [48.c](https://github.com/serope/euler_rpi/blob/master/c/48.c) | `gcc 48.c euler_bignum.c` | 6.759s
49 | [Prime permutations](https://projecteuler.net/problem=49) | [49.c](https://github.com/serope/euler_rpi/blob/master/c/49.c) | `gcc 49.c euler.c` | 0.928s
50 | [Consecutive prime sum](https://projecteuler.net/problem=50) | [50.c](https://github.com/serope/euler_rpi/blob/master/c/50.c) | `gcc 50.c euler.c` | 0.883s
51 | [Prime digit replacements](https://projecteuler.net/problem=51) | [51.c](https://github.com/serope/euler_rpi/blob/master/c/51.c) | `gcc 51.c euler.c euler_binary.c` | 11.805s
52 | [Permuted multiples](https://projecteuler.net/problem=52) | [52.c](https://github.com/serope/euler_rpi/blob/master/c/52.c) | `gcc 52.c euler.c` | 0.425s
53 | [Combinatoric selections](https://projecteuler.net/problem=53) | [53.c](https://github.com/serope/euler_rpi/blob/master/c/53.c) | `gcc 53.c` | 0.009s
54 | [Poker hands](https://projecteuler.net/problem=54) | [54.c](https://github.com/serope/euler_rpi/blob/master/c/54.c) | `gcc 54.c euler.c` | 0.039s
55 | [Lychrel numbers](https://projecteuler.net/problem=55) | [55.c](https://github.com/serope/euler_rpi/blob/master/c/55.c) | `gcc 55.c euler.c euler_bignum.c` | 0.232s
56 | [Powerful digit sum](https://projecteuler.net/problem=56) | [56.c](https://github.com/serope/euler_rpi/blob/master/c/56.c) | `gcc 56.c euler.c euler_bignum.c` | 5.027s
57 | [Square root convergents](https://projecteuler.net/problem=57) | [57.c](https://github.com/serope/euler_rpi/blob/master/c/57.c) | `gcc 57.c euler.c euler_bignum.c` | 0.172s
58 | [Spiral primes](https://projecteuler.net/problem=58) | [58.go](https://github.com/serope/euler_rpi/blob/master/go/58.go) | `go build 58.go` | 2.048s
59 | [XOR decryption](https://projecteuler.net/problem=59) | [59.go](https://github.com/serope/euler_rpi/blob/master/go/59.go) | `go build 59.go euler.go` | 33.139s
60 | [Prime pair sets](https://projecteuler.net/problem=60) | [60.go](https://github.com/serope/euler_rpi/blob/master/go/60.go) | `go build 60.go euler.go` | 31.089s
61 | [Cyclical figurate numbers](https://projecteuler.net/problem=61) | [61.go](https://github.com/serope/euler_rpi/blob/master/go/61.go) | `go build 61.go euler.go` | 0.204s
62 | [Cubic permutations](https://projecteuler.net/problem=62) | [62.go](https://github.com/serope/euler_rpi/blob/master/go/62.go) | `go build 62.go` | 3.642s
63 | [Powerful digit counts](https://projecteuler.net/problem=63) | [63.go](https://github.com/serope/euler_rpi/blob/master/go/63.go) | `go build 63.go` | 0.011s
64 | [Odd period square roots](https://projecteuler.net/problem=64) | [64.go](https://github.com/serope/euler_rpi/blob/master/go/64.go) | `go build 64.go euler.go` | 0.079s
65 | [Convergents of *e*](https://projecteuler.net/problem=65) | [65.go](https://github.com/serope/euler_rpi/blob/master/go/65.go) | `go build 65.go` | 0.009s
66 | [Diophantine equation](https://projecteuler.net/problem=66) | [66.go](https://github.com/serope/euler_rpi/blob/master/go/66.go) | `go build 66.go euler.go` | 1.327s
67 | [Maximum path sum II](https://projecteuler.net/problem=67) | | |
68 | [Magic 5-gon ring](https://projecteuler.net/problem=68) | [68.go](https://github.com/serope/euler_rpi/blob/master/go/68.go) | `go build 68.go` | 3.300s

## Libraries
None

## Thanks
* [Project Euler](https://projecteuler.net)
* [Nayuki](https://github.com/nayuki/Project-Euler-solutions/blob/master/Answers.txt) for their ~~cheat~~ reference sheet

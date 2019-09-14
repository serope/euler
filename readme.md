# euler_rpi
These are my Project Euler solutions written and timed on a Raspberry Pi 3B. The 3B is a fairly weak machine, so run times are roughly 5-10x longer than they would be on a typical desktop PC.

The languages used are C (1-57) and Go (58+).

## Compilation
Solutions can be compiled via the `compile.py` script, e.g.

```bash
pi@raspberrypi:~ $ python compile.py 23
23:	gcc 23.c euler.c -o 23
pi@raspberrypi:~ $
```

To generate the list below, run `compile.py all` and then `checklist.py`.

## Checklist
&#35; | Problem | File | Real | User | Sys
----- | --------| ---- | ---- | ---- | ---
1 | [Multiples of 3 and 5](https://projecteuler.net/problem=1) | [01.c](https://github.com/serope/euler_rpi/blob/master/c/01.c) | 0.008s | 0.005s | 0.001s
2 | [Even Fibonacci numbers](https://projecteuler.net/problem=2) | [02.c](https://github.com/serope/euler_rpi/blob/master/c/02.c) | 0.008s | 0.008s | 0.000s
3 | [Largest prime factor](https://projecteuler.net/problem=3) | [03.c](https://github.com/serope/euler_rpi/blob/master/c/03.c) | 1.075s | 1.073s | 0.002s
4 | [Largest palindrome product](https://projecteuler.net/problem=4) | [04.c](https://github.com/serope/euler_rpi/blob/master/c/04.c) | 0.906s | 0.901s | 0.000s
5 | [Smallest multiple](https://projecteuler.net/problem=5) | [05.c](https://github.com/serope/euler_rpi/blob/master/c/05.c) | 0.662s | 0.656s | 0.000s
6 | [Sum square difference](https://projecteuler.net/problem=6) | [06.c](https://github.com/serope/euler_rpi/blob/master/c/06.c) | 0.006s | 0.001s | 0.005s
7 | [10001st prime](https://projecteuler.net/problem=7) | [07.c](https://github.com/serope/euler_rpi/blob/master/c/07.c) | 0.570s | 0.529s | 0.040s
8 | [Largest product in a series](https://projecteuler.net/problem=8) | [08.c](https://github.com/serope/euler_rpi/blob/master/c/08.c) | 0.004s | 0.004s | 0.000s
9 | [Special Pythagorean triplet](https://projecteuler.net/problem=9) | [09.c](https://github.com/serope/euler_rpi/blob/master/c/09.c) | 3.192s | 3.182s | 0.010s
10 | [Summation of primes](https://projecteuler.net/problem=10) | [10.c](https://github.com/serope/euler_rpi/blob/master/c/10.c) | 1.244s | 1.170s | 0.071s
11 | [Largest product in a grid](https://projecteuler.net/problem=11) | [11.c](https://github.com/serope/euler_rpi/blob/master/c/11.c) | 0.006s | 0.005s | 0.001s
12 | [Highly divisible triangular number](https://projecteuler.net/problem=12) | [12.c](https://github.com/serope/euler_rpi/blob/master/c/12.c) | 21.767s | 1m16.143s | 0.002s
13 | [Large sum](https://projecteuler.net/problem=13) | [13.c](https://github.com/serope/euler_rpi/blob/master/c/13.c) | 0.006s | 0.006s | 0.000s
14 | [Longest Collatz sequence](https://projecteuler.net/problem=14) | [14.c](https://github.com/serope/euler_rpi/blob/master/c/14.c) | 0.428s | 0.404s | 0.020s
15 | [Lattice paths](https://projecteuler.net/problem=15) | | | |
16 | [Power digit sum](https://projecteuler.net/problem=16) | [16.c](https://github.com/serope/euler_rpi/blob/master/c/16.c) | 0.054s | 0.045s | 0.009s
17 | [Number letter counts](https://projecteuler.net/problem=17) | [17.c](https://github.com/serope/euler_rpi/blob/master/c/17.c) | 0.021s | 0.000s | 0.018s
18 | [Maximum path sum I](https://projecteuler.net/problem=18) | [18.c](https://github.com/serope/euler_rpi/blob/master/c/18.c) | 0.015s | 0.013s | 0.002s
19 | [Counting Sundays](https://projecteuler.net/problem=19) | [19.c](https://github.com/serope/euler_rpi/blob/master/c/19.c) | 0.022s | 0.002s | 0.017s
20 | [Factorial digit sum](https://projecteuler.net/problem=20) | [20.c](https://github.com/serope/euler_rpi/blob/master/c/20.c) | 0.020s | 0.011s | 0.009s
21 | [Amicable numbers](https://projecteuler.net/problem=21) | [21.c](https://github.com/serope/euler_rpi/blob/master/c/21.c) | 4.984s | 4.964s | 0.010s
22 | [Names scores](https://projecteuler.net/problem=22) | [22.c](https://github.com/serope/euler_rpi/blob/master/c/22.c) | 0.041s | 0.028s | 0.010s
23 | [Non-abundant sums](https://projecteuler.net/problem=23) | [23.c](https://github.com/serope/euler_rpi/blob/master/c/23.c) | 6.897s | 6.896s | 0.000s
24 | [Lexicographic permutations](https://projecteuler.net/problem=24) | [24.c](https://github.com/serope/euler_rpi/blob/master/c/24.c) | 0.003s | 0.004s | 0.000s
25 | [1000-digit Fibonacci number](https://projecteuler.net/problem=25) | [25.c](https://github.com/serope/euler_rpi/blob/master/c/25.c) | 0.384s | 0.385s | 0.000s
26 | [Reciprocal cycles](https://projecteuler.net/problem=26) | | | |
27 | [Quadratic primes](https://projecteuler.net/problem=27) | [27.c](https://github.com/serope/euler_rpi/blob/master/c/27.c) | 5.024s | 5.018s | 0.001s
28 | [Number spiral diagonals](https://projecteuler.net/problem=28) | [28.c](https://github.com/serope/euler_rpi/blob/master/c/28.c) | 0.003s | 0.004s | 0.000s
29 | [Distinct powers](https://projecteuler.net/problem=29) | [29.c](https://github.com/serope/euler_rpi/blob/master/c/29.c) | 20.173s | 20.141s | 0.020s
30 | [Digit fifth powers](https://projecteuler.net/problem=30) | [30.c](https://github.com/serope/euler_rpi/blob/master/c/30.c) | 0.230s | 0.230s | 0.000s
31 | [Coin sums](https://projecteuler.net/problem=31) | [31.c](https://github.com/serope/euler_rpi/blob/master/c/31.c) | 0.463s | 0.460s | 0.000s
32 | [Pandigital products](https://projecteuler.net/problem=32) | [32.c](https://github.com/serope/euler_rpi/blob/master/c/32.c) | 5.311s | 5.310s | 0.001s
33 | [Digit cancelling fractions](https://projecteuler.net/problem=33) | [33.c](https://github.com/serope/euler_rpi/blob/master/c/33.c) | 0.014s | 0.014s | 0.000s
34 | [Digit factorials](https://projecteuler.net/problem=34) | [34.c](https://github.com/serope/euler_rpi/blob/master/c/34.c) | 1.687s | 1.682s | 0.000s
35 | [Circular primes](https://projecteuler.net/problem=35) | [35.c](https://github.com/serope/euler_rpi/blob/master/c/35.c) | 7.386s | 7.361s | 0.020s
36 | [Double-base palindrome](https://projecteuler.net/problem=36) | [36.c](https://github.com/serope/euler_rpi/blob/master/c/36.c) | 1.137s | 1.135s | 0.000s
37 | [Truncatable primes](https://projecteuler.net/problem=37) | [37.c](https://github.com/serope/euler_rpi/blob/master/c/37.c) | 0.678s | 0.648s | 0.030s
38 | [Pandigital multiples](https://projecteuler.net/problem=38) | [38.c](https://github.com/serope/euler_rpi/blob/master/c/38.c) | 0.091s | 0.091s | 0.000s
39 | [Integer right triangles](https://projecteuler.net/problem=39) | [39.c](https://github.com/serope/euler_rpi/blob/master/c/39.c) | 6.955s | 6.937s | 0.010s
40 | [Champernowne's constant](https://projecteuler.net/problem=40) | [40.c](https://github.com/serope/euler_rpi/blob/master/c/40.c) | 0.223s | 0.211s | 0.010s
41 | [Pandigital prime](https://projecteuler.net/problem=41) | [41.c](https://github.com/serope/euler_rpi/blob/master/c/41.c) | 4.697s | 4.695s | 0.000s
42 | [Coded triangle numbers](https://projecteuler.net/problem=42) | [42.c](https://github.com/serope/euler_rpi/blob/master/c/42.c) | 0.008s | 0.008s | 0.000s
43 | [Sub-string divisibility](https://projecteuler.net/problem=43) | [43.c](https://github.com/serope/euler_rpi/blob/master/c/43.c) | 0.025s | 0.016s | 0.009s
44 | [Pentagon numbers](https://projecteuler.net/problem=44) | [44.c](https://github.com/serope/euler_rpi/blob/master/c/44.c) | 8.323s | 19.715s | 0.000s
45 | [Triangular, pentagonal, and hexagonal](https://projecteuler.net/problem=45) | [45.c](https://github.com/serope/euler_rpi/blob/master/c/45.c) | 0.565s | 0.555s | 0.010s
46 | [Golbach's other conjecture](https://projecteuler.net/problem=46) | [46.c](https://github.com/serope/euler_rpi/blob/master/c/46.c) | 0.265s | 0.252s | 0.010s
47 | [Distinct primes factors](https://projecteuler.net/problem=47) | [47.c](https://github.com/serope/euler_rpi/blob/master/c/47.c) | 27.672s | 27.626s | 0.040s
48 | [Self powers](https://projecteuler.net/problem=48) | [48.c](https://github.com/serope/euler_rpi/blob/master/c/48.c) | 10.073s | 10.072s | 0.000s
49 | [Prime permutations](https://projecteuler.net/problem=49) | [49.c](https://github.com/serope/euler_rpi/blob/master/c/49.c) | 0.909s | 0.844s | 0.060s
50 | [Consecutive prime sum](https://projecteuler.net/problem=50) | [50.c](https://github.com/serope/euler_rpi/blob/master/c/50.c) | 1.514s | 1.501s | 0.010s
51 | [Prime digit replacements](https://projecteuler.net/problem=51) | [51.c](https://github.com/serope/euler_rpi/blob/master/c/51.c) | 12.826s | 12.481s | 0.340s
52 | [Permuted multiples](https://projecteuler.net/problem=52) | [52.c](https://github.com/serope/euler_rpi/blob/master/c/52.c) | 0.393s | 0.373s | 0.020s
53 | [Combinatoric selections](https://projecteuler.net/problem=53) | [53.c](https://github.com/serope/euler_rpi/blob/master/c/53.c) | 0.005s | 0.001s | 0.004s
54 | [Poker hands](https://projecteuler.net/problem=54) | [54.c](https://github.com/serope/euler_rpi/blob/master/c/54.c) | 0.061s | 0.058s | 0.000s
55 | [Lychrel numbers](https://projecteuler.net/problem=55) | [55.c](https://github.com/serope/euler_rpi/blob/master/c/55.c) | 0.357s | 0.347s | 0.010s
56 | [Powerful digit sum](https://projecteuler.net/problem=56) | [56.c](https://github.com/serope/euler_rpi/blob/master/c/56.c) | 6.355s | 6.351s | 0.001s
57 | [Square root convergents](https://projecteuler.net/problem=57) | [57.c](https://github.com/serope/euler_rpi/blob/master/c/57.c) | 0.172s | 0.170s | 0.001s
58 | [Spiral primes](https://projecteuler.net/problem=58) | [58.go](https://github.com/serope/euler_rpi/blob/master/go/58.go) | 3.837s | 3.856s | 0.051s
59 | [XOR decryption](https://projecteuler.net/problem=59) | [59.go](https://github.com/serope/euler_rpi/blob/master/go/59.go) | 21.748s | 1m24.206s | 0.473s
60 | [Prime pair sets](https://projecteuler.net/problem=60) | [60.go](https://github.com/serope/euler_rpi/blob/master/go/60.go) | 50.597s | 51.583s | 0.230s
61 | [Cyclical figurate numbers](https://projecteuler.net/problem=61) | [61.go](https://github.com/serope/euler_rpi/blob/master/go/61.go) | 0.184s | 0.167s | 0.018s
62 | [Cubic permutations](https://projecteuler.net/problem=62) | [62.go](https://github.com/serope/euler_rpi/blob/master/go/62.go) | 5.308s | 5.298s | 0.020s
63 | [Powerful digit counts](https://projecteuler.net/problem=63) | [63.go](https://github.com/serope/euler_rpi/blob/master/go/63.go) | 0.025s | 0.028s | 0.000s
64 | [Odd period square roots](https://projecteuler.net/problem=64) | [64.go](https://github.com/serope/euler_rpi/blob/master/go/64.go) | 0.148s | 0.128s | 0.023s
65 | [Convergents of *e*](https://projecteuler.net/problem=65) | [65.go](https://github.com/serope/euler_rpi/blob/master/go/65.go) | 0.027s | 0.026s | 0.000s
66 | [Diophantine equation](https://projecteuler.net/problem=66) | [66.go](https://github.com/serope/euler_rpi/blob/master/go/66.go) | 2.508s | 2.516s | 0.040s
67 | [Maximum path sum II](https://projecteuler.net/problem=67) | | | |
68 | [Magic 5-gon ring](https://projecteuler.net/problem=68) | [68.go](https://github.com/serope/euler_rpi/blob/master/go/68.go) | 5.976s | 6.143s | 0.050s


This list was generated on `2019 Sep 13 (Fri) @ 21:16`!

## Libraries
None

## Thanks
* [Project Euler](https://projecteuler.net)
* [Nayuki](https://github.com/nayuki/Project-Euler-solutions/blob/master/Answers.txt) for their ~~cheat~~ reference sheet

# euler_rpi_c
These are some attempts at solving [Project Euler](https://projecteuler.net) puzzles in C on a Raspberry Pi (though they can be compiled on anything). They aren't elegant, fast, or well-organized, but they work, and their code is somewhat readable. Listed below are some example run times on a Pi 3 Model B when executed with the `time` command, with and without optimization.

## Checklist

Problem | File | Compilation | User time | User time (`-Ofast`)
--------| ---- | ----------- | --------- | --------------------
[Problem 1](https://projecteuler.net/problem=1) | 01.c | `gcc 01.c euler.c -o 01` | 0.001s | 0.001s
[Problem 2](https://projecteuler.net/problem=2) | 02.c | `gcc 02.c euler.c -o 02` | 0.003s | 0.003s
[Problem 3](https://projecteuler.net/problem=3) | 03.c | `gcc 03.c euler.c -o 03` | 0.560s | 0.321s
[Problem 4](https://projecteuler.net/problem=4) | 04.c | `gcc 04.c euler.c -o 04` | 0.440s | 0.369s
[Problem 5](https://projecteuler.net/problem=5) | 05.c | `gcc 05.c euler.c -o 05` | 0.328s | 0.200s
[Problem 6](https://projecteuler.net/problem=6) | 06.c | `gcc 06.c -o 06` | 0.003s | 0.003s
[Problem 7](https://projecteuler.net/problem=7) | 07.c | `gcc 07.c euler.c -o 07` | 0.394s | 0.321s
[Problem 8](https://projecteuler.net/problem=8) | 08.c | `gcc 08.c euler.c -o 08` | 0.003s | 0.003s
[Problem 9](https://projecteuler.net/problem=9) | 09.c | `gcc 09.c euler.c -o 09` | 3.174s | 1.354s
[Problem 10](https://projecteuler.net/problem=10) | 10.c | `gcc 10.c euler.c -o 10` | 0.826s | 0.655s
[Problem 11](https://projecteuler.net/problem=11) | 11.c | `gcc 11.c euler.c -o 11` | 0.833s | 0.826s
[Problem 12](https://projecteuler.net/problem=12) | 12.c | `gcc 12.c euler.c -o 12` | 10.581s :( | 2.335s
[Problem 13](https://projecteuler.net/problem=13) | 13.c | `gcc 13.c euler_bignum.c -o 13` | 0.001s | 0.001s
[Problem 14](https://projecteuler.net/problem=14) | 14.c | `gcc 14.c euler.c -o 14` | 0.423s | 0.287s
[Problem 15](https://projecteuler.net/problem=15) | | | |
[Problem 16](https://projecteuler.net/problem=16) | 16.c | `gcc 16.c euler_bignum.c -o 16` | 0.104s | 0.033s
[Problem 17](https://projecteuler.net/problem=17) | 17.c | `gcc 17.c -o 17` | 0.010s | 0.001s
[Problem 18](https://projecteuler.net/problem=18) | 18.c | `gcc 18.c euler.c -o 18` | 0.014s | 0.010s
[Problem 19](https://projecteuler.net/problem=19) | 19.c | `gcc 19.c -o 19` | 0.010s | 0.010s
[Problem 20](https://projecteuler.net/problem=20) | 20.c | `gcc 20.c euler_bignum.c -o 20` | 0.015s | 0.008s
[Problem 21](https://projecteuler.net/problem=21) | 21.c | `gcc 21.c euler.c -o 21` | 3.486s | 1.657s
[Problem 22](https://projecteuler.net/problem=22) | 22.c | `gcc 22.c -o 22` | 0.053s | 0.031s
[Problem 23](https://projecteuler.net/problem=23) | 23.c | `gcc 23.c euler.c -o 23` | 6.910s | 2.663s
[Problem 24](https://projecteuler.net/problem=24) | 24.c | `gcc 24.c euler.c -o 24` | 0.005s | 0.003s
[Problem 25](https://projecteuler.net/problem=25) | 25.c | `gcc 25.c euler_bignum.c -o 25` | 0.412s | 0.157s
[Problem 26](https://projecteuler.net/problem=26) | | | |
[Problem 27](https://projecteuler.net/problem=27) | 27.c | `gcc 27.c euler.c -o 27` | 5.095s | 4.491s
[Problem 28](https://projecteuler.net/problem=28) | 28.c | `gcc 28.c -o 28` | 0.003s | 0.001s
[Problem 29](https://projecteuler.net/problem=29) | 29.c | `gcc 29.c euler_bignum.c -o 29` | 19.955s :( | 6.750s
[Problem 30](https://projecteuler.net/problem=30) | 30.c | `gcc 30.c euler.c -o 30` | 26.795s :( | 15.277s :(
[Problem 31](https://projecteuler.net/problem=31) | 31.c | `gcc 31.c -o 31` | 0.455s | 0.053s
[Problem 32](https://projecteuler.net/problem=32) | 32.c | `gcc 32.c euler.c -o 32` | 3.678s | 1.853s
[Problem 33](https://projecteuler.net/problem=33) | 33.c | `gcc 33.c -o 33` | 0.013s | 0.013s
[Problem 34](https://projecteuler.net/problem=34) | 34.c | `gcc 34.c euler.c -o 34` | 1.688s | 1.014s
[Problem 35](https://projecteuler.net/problem=35) | 35.c | `gcc 35.c euler.c -o 35` | 7.440s | 6.765s
[Problem 36](https://projecteuler.net/problem=36) | 36.c | `gcc 36.c euler.c euler_binary.c -o 36` | 1.177s | 0.840s
[Problem 37](https://projecteuler.net/problem=37) | 37.c | `gcc 37.c euler.c -o 37` | 0.665s | 0.506s
[Problem 38](https://projecteuler.net/problem=38) | 38.c | `gcc 38.c euler.c -o 38` | 0.123s | 0.059s
[Problem 39](https://projecteuler.net/problem=39) | 39.c | `gcc 39.c euler.c -o 39` | 6.934s | 1.381s
[Problem 40](https://projecteuler.net/problem=40) | 40.c | `gcc 40.c euler.c -o 40` | 0.221s | 0.190s
[Problem 41](https://projecteuler.net/problem=41) | 41.c | `gcc 41.c euler.c -o 41` | 4.759s | 2.693s
[Problem 42](https://projecteuler.net/problem=42) | 42.c | `gcc 42.c -o 42` | 0.008s | 0.007s
[Problem 43](https://projecteuler.net/problem=43) | 43.c | `gcc 43.c euler.c -o 43` | 42.613s :( | 21.330s :(
[Problem 44](https://projecteuler.net/problem=44) | 44.c | `gcc 44.c euler.c -o 44` | 1m27.282s :( | 1m18.982s :(
[Problem 45](https://projecteuler.net/problem=45) | 45.c | `gcc 45.c euler.c -o 45` | 22.544s :( | 5.526s
[Problem 46](https://projecteuler.net/problem=46) | 46.c | `gcc 46.c euler.c -o 46 -lm` | 0.179s | 0.038s
[Problem 47](https://projecteuler.net/problem=47) | 47.c | `gcc 47.c euler.c -o 47` | 26.606s :( | 14.750s :(
[Problem 48](https://projecteuler.net/problem=48) | 48.c | `gcc 48.c euler_bignum.c -o 48` | 6.759s | 3.431s
[Problem 49](https://projecteuler.net/problem=49) | 49.c | `gcc 49.c euler.c -o 49` | 0.928s | 0.759s
[Problem 50](https://projecteuler.net/problem=50) | 50.c | `gcc 50.c euler.c -o 50` | 0.883s | 0.489s
[Problem 51](https://projecteuler.net/problem=51) | 51.c | `gcc 51.c euler.c eueler_binary.c -o 51` | 11.805s :( | 7.539s
[Problem 52](https://projecteuler.net/problem=52) | 52.c | `gcc 52.c euler.c -o 52` | 0.425s | 0.360s
[Problem 53](https://projecteuler.net/problem=53) | 53.c | `gcc 53.c -o 53` | 0.009s | 0.001s
[Problem 54](https://projecteuler.net/problem=54) | 54.c | `gcc 54.c euler.c -o 54` | 0.039s | 0.021s
[Problem 55](https://projecteuler.net/problem=55) | 55.c | `gcc 55.c euler.c euler_bignum.c -o 55` | 0.232s | 0.180s
[Problem 56](https://projecteuler.net/problem=56) | 56.c | `gcc 56.c euler.c euler_bignum.c -o 56` | 5.027s | 1.717s
[Problem 57](https://projecteuler.net/problem=57) | 57.c | `gcc 57.c euler.c euler_bignum.c -o 57` | 0.172s | 0.071s

## Libraries
None

## Credits
* [Project Euler](https://projecteuler.net)
* [Project Nayuki](https://github.com/nayuki/Project-Euler-solutions/blob/master/Answers.txt) for his ~~cheat~~ reference sheet

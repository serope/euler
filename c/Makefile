# Project Euler
# Makefile for C solutions
# TODO: Fix circular dependencies (e.g. euler.h and array.h)
CC			= gcc
LDFLAGS		= -pthread -lm
EULER_FILES	= array.c big.c binary.c euler.c factor.c pandigital.c prime.c -lm strings.c vector.c

01:
	$(CC) $@.c -o $@

02:
	$(CC) $@.c vector.c -o $@

03:
	$(CC) $@.c array.c euler.c prime.c -lm -o $@

04:
	$(CC) $@.c array.c euler.c -o $@

05:
	$(CC) $@.c -o $@
	
06:
	$(CC) $@.c -o $@

07:
	$(CC) $@.c array.c euler.c prime.c -lm -o $@

08:
	$(CC) $@.c array.c euler.c strings.c vector.c -o $@

09:
	$(CC) $@.c array.c euler.c -o $@

10:
	$(CC) $@.c array.c euler.c prime.c -lm -o $@

11:
	$(CC) $@.c array.c euler.c strings.c vector.c -o $@

12:
	$(CC) $@.c array.c euler.c factor.c -pthread -o $@

13:
	$(CC) $@.c array.c big.c euler.c strings.c vector.c -o $@

14:
	$(CC) $@.c -o $@

15:
	$(CC) $@.c -o $@

16:
	$(CC) $@.c array.c big.c euler.c -o $@

17:
	$(CC) $@.c array.c euler.c -o $@

18:
	$(CC) $@.c array.c euler.c strings.c vector.c -o $@

19:
	$(CC) $@.c -o $@

20:
	$(CC) $@.c array.c big.c euler.c -o $@

21:
	$(CC) $@.c array.c euler.c factor.c -o $@

22:
	$(CC) $@.c strings.c vector.c -o $@

23:
	$(CC) $@.c array.c euler.c factor.c -o $@

24:
	$(CC) $@.c array.c euler.c pandigital.c -o $@

25:
	$(CC) $@.c array.c big.c euler.c -o $@

27:
	$(CC) $@.c array.c euler.c prime.c -lm -o $@

28:
	$(CC) $@.c -o $@

29:
	$(CC) $@.c array.c big.c euler.c -o $@

30:
	$(CC) $@.c array.c euler.c -o $@

31:
	$(CC) $@.c -o $@

32:
	$(CC) $@.c array.c euler.c pandigital.c -o $@

33:
	$(CC) $@.c -o $@

34:
	$(CC) $@.c array.c euler.c -o $@

35:
	$(CC) $@.c array.c euler.c prime.c -lm -o $@

36:
	$(CC) $@.c array.c euler.c binary.c -o $@

37:
	$(CC) $@.c array.c euler.c prime.c -lm -o $@

38:
	$(CC) $@.c array.c euler.c pandigital.c -o $@

39:
	$(CC) $@.c array.c euler.c -o $@

40:
	$(CC) $@.c array.c euler.c -o $@

41:
	$(CC) $@.c array.c euler.c pandigital.c prime.c -lm -o $@

42:
	$(CC) $@.c array.c euler.c strings.c vector.c -o $@	

43:
	$(CC) $@.c array.c euler.c pandigital.c -o $@

44:
	$(CC) $@.c array.c euler.c -pthread -o $@

45:
	$(CC) $@.c array.c euler.c -o $@

46:
	$(CC) $@.c array.c euler.c -lm -o $@

47:
	$(CC) $@.c array.c euler.c -o $@

48:
	$(CC) $@.c array.c big.c euler.c -o $@

49:
	$(CC) $@.c array.c euler.c prime.c -lm -o $@

50:
	$(CC) $@.c array.c euler.c prime.c -lm -o $@

%:
	$(CC) $@.c $(EULER_FILES) $(LDFLAGS) -o $@

/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 53
 **********************************************************************/
#include <stdio.h>
#include <stdint.h>

int64_t combo(int n, int r);

int main() {
	int distinct = 0;
	
	for (int n=1; n<=100; n++) {
		
		int under = 0;
		
		for (int r=1; r<=n; r++) {
			/***********************************************************
			 * 1. Calculate the combination
			 **********************************************************/
			int64_t c = combo(n,r);
			printf("combo(%d,%d) \t %lld \n", n, r, c);
			
			
			/***********************************************************
			 * 2. If the combination is under 1M, increment 'under'
			 **********************************************************/
			if (c<1000000) {
				under++;
				continue;
			}
			
			
			/***********************************************************
			 * 3. Otherwise, if the combination is 1M or over, then
			 *    the amount of further combinations which evaluate to
			 *    1M or over can be determined
			 **********************************************************/
			distinct += n-(under*2 + 1);
			break;
		}
	}
	
	printf("%d \n", distinct);
}





int64_t combo(int n, int r) {
	//1. Return if a special case occurs
	if (n==r)
		return 1;
	else if (n==r+1)
		return n;
	else if (r>n)
		return -1;
	
	
	//2. Find which term in the denominator, either r or (n-r),
	//   is closer to n, and assign it as 'halt'
	int halt;
	if ( (n-r) > r )
		halt = n-r;
	else
		halt = r;

	
	//3. Evaluate the factorial in the numerator, starting at n and
	//   going down, but halt at 'halt'
	int64_t numerator = 1;
	for (int f=n; f>halt; f--)
		numerator *= f;
	
	
	//4. Evaluate the denominator based on how 'halt' was assigned
	//   in step 2
	int64_t denominator = 1;
	if (halt==n-r)
		for (int f=r; f>1; f--)
			denominator *= f;
	
	else
		for (int f=(n-r); f>1; f--)
			denominator *= f;
	
	//5. Return
	return numerator/denominator;
}

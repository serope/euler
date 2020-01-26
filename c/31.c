/*
 * Project Euler
 * 31.c
 * TODO: Rewrite this using dynamic programming
 */
#include <stdio.h>

int main() {
	/*******************************************************************
	 * Check every possible combination of coins
	 * If a combination equals 200 pence (2 pounds), increase the count
	 * If a combination exceeds 200 pence, skip it
	 ******************************************************************/
	int combinations = 0;
	int sum;
	
	for (int one_pence=0; one_pence<=200; one_pence+=1) {
		for (int two_pence=0; two_pence<=200; two_pence+=2) {
			sum = one_pence+two_pence;
			if (sum>200)
				break;
			else if (sum==200) {
				combinations++;
				break;
			}
			
			for (int five_pence=0; five_pence<=200; five_pence+=5) {
				sum = one_pence+two_pence+five_pence;
				if (sum>200)
					break;
				else if (sum==200) {
					combinations++;
					break;
				}
				
				for (int ten_pence=0; ten_pence<=200; ten_pence+=10) {
					sum = one_pence+two_pence+five_pence+ten_pence;
					if (sum>200)
						break;
					else if (sum==200) {
						combinations++;
						break;
					}
						
					for (int twenty_pence=0; twenty_pence<=200; twenty_pence+=20) {
						sum = one_pence+two_pence+five_pence+ten_pence+twenty_pence;
						if (sum>200)
							break;
						else if (sum==200) {
							combinations++;
							break;
						}
						
						for (int fifty_pence=0; fifty_pence<=200; fifty_pence+=50) {
						sum = one_pence+two_pence+five_pence+ten_pence+twenty_pence+fifty_pence;
						if (sum>200)
							break;
						else if (sum==200) {
							combinations++;
							break;
						}
							
							for (int one_pound=0; one_pound<=200; one_pound+=100) {
								sum = one_pence+two_pence+five_pence+ten_pence+twenty_pence+fifty_pence+one_pound;
								if (sum>200)
									break;
								else if (sum==200) {
									combinations++;
									break;
								}
									
								for (int two_pound=0; two_pound<=200; two_pound+=200) {
									sum = one_pence+two_pence+five_pence+ten_pence+twenty_pence+fifty_pence+one_pound+two_pound;
									if (sum>200)
										break;
									else if (sum==200) {
										combinations++;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	printf("combinations:  %d \n", combinations);
	return 0;
}

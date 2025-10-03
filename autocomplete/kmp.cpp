#include <iostream>
#include <cstring>

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
	int i=1;
	int j=0;
	lps[0] = -1;
	while(i < M) {
		if (pat[i] == pat[j]) {
			lps[i] = j;
			while (j>=0 && pat[i]!=pat[j]) {
				j = lps[j];
			}
		}
		else {
			lps[i] = lps[j];
		}
		i++;
		j++;
	}
	lps[M] = j;
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
	int m=0;
	while (pat[m] != '\n') m++;
	int lps[m+1];
	computeLPSArray(pat, m, lps);
	int i=0;
	int j=0;
	int t=0;
	while (txt[t] != '\n') t++;
	while (i < t) {
		if (txt[i] == pat[j]) {
			i++;
			j++;
			if (j == m) {
				printf("Found pattern at index %d \n", i-j);
				j = lps[j];
			}
		}
		else {
			j = lps[j];
			if (j<0) {
				j++;
				i++;
			}
		}
	}

}

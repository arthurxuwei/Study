#include <stdio.h>

void printPermutation(int n, int* A, int cur)
{
	int i,j;
	if(cur == n)
	{
		for(i = 0; i < n; i++) printf("%d ", A[i]);
		printf("\n");
	}
	else for(i = 1; i <= n; i++)
	{
		int ok = 1;
		for(j = 0; j < cur; j++)
			if(A[j] == i) ok = 0;
		if(ok) 
		{
			A[cur] = i;
			printPermutation(n, A, cur+1);
		}
	}
}

int main(int argc, char** argv) {
	int A[5];
	printPermutation(5, A, 0);
}

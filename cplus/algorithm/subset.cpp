#include <stdio.h>
void printSubset(int n, int *A, int cur)
{
	for(int i = 0; i < cur; i++) printf("%d ", A[i]);
	printf("\n");
	int s = cur ? A[cur-1] + 1 : 0;
	for(int i = s; i < n; i++)
	{
		A[cur] = i;
		printSubset(n, A, cur+1);
	}
}

int main(int argc, char** argv)
{
	int A[5];
	printSubset(5, A, 0);
}

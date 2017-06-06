#include <iostream>
using namespace std;

void permutation(char *pStr, char *pBegin) {
	if(*pBegin == '\0'){
		cout << pStr << endl;
	} else for (char *p = pBegin; *p != '\0'; p++) {
		char temp = *p;
		*p = *pBegin;
		*pBegin = temp;

		permutation(pStr, pBegin+1);

		temp = *p;
		*p = *pBegin;
		*pBegin = temp;

	}
}
main() {
	char a[] = "abcde";
	permutation(a, a);
}

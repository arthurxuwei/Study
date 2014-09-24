#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

void (*pFunc)(int);
void (*(*pFunc2)(int))();
//void (*f)();  //redefine
//int f; //redifine
void f(char *x){
    x++;
    *x='a';
}

inline char hdigit(int n) {
	return "0123456789abcdef"[n&0xf];
}

inline char selector(int n) {
	return "abcdefghijklmnopqrstuvwxyz"[n];
}

int main(int argc, char** argv) {
    int *a[2][3];
    printf("size is: %lu\n", sizeof(a));
	int **b[2][3];
    printf("size is: %lu\n", sizeof(b));
    
    char str[sizeof("hello")];
    std::strcpy(str, "hello");
    f(str);
    std::cout << str << std::endl;

    std::cout << hdigit(5) << std::endl;

    std::cout << hdigit(14) << std::endl;

    std::cout << selector(0) << std::endl;

    std::cout << selector(5) << std::endl;

	printf("size of int: %lu\n", sizeof(int));

	printf("size of pointer: %lu\n", sizeof(int*));

	//int t = 1 << 31; largest neg-int
	int t = ~(1 << 31); //largest int

    printf("left shift: %d\n",t);
	printf("%x\n", t);	
	
	int arr[] = {6,7,8,9,10};
	int *ptr = arr;
	(*ptr++) += 123;
	printf("%d, %d\n", *ptr, *(++ptr));
	for(int i=0; i<5; i++) {
		std::cout << arr[i] << " ";
	}
	return 0;
}

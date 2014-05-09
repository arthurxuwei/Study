#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

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
    
    char str[sizeof("hello")];
    std::strcpy(str, "hello");
    f(str);
    std::cout << str << std::endl;

    std::cout << hdigit(5) << std::endl;

    std::cout << hdigit(14) << std::endl;

    std::cout << selector(0) << std::endl;

    std::cout << selector(5) << std::endl;
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

void f(char *x){
    x++;
    *x='a';
}

int main(int argc, char** argv) {
    int *a[2][3];
    printf("size is: %lu\n", sizeof(a));
    
    char str[sizeof("hello")];
    std::strcpy(str, "hello");
    f(str);
    std::cout << str << std::endl;
    return 0;
}

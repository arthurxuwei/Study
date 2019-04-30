#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv) {
    long tmp = sysconf(_SC_NPROCESSORS_ONLN);
    printf("online cpu num: %ld\n", tmp);
    return 0;
}

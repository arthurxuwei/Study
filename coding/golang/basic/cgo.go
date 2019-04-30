package main
/*
#include <unistd.h>
*/
import "C"

import (
    "fmt"
)


func main() {
	i, err := C.sysconf(C._SC_NPROCESSORS_ONLN)
	// According to POSIX - errno is undefined after successful
	// sysconf, and can be non-zero in several cases, so look for
	// error in returned value not in errno.
	// (https://sourceware.org/bugzilla/show_bug.cgi?id=21536)
	if i == -1 {
        fmt.Println("err: %s", err)
	}
    fmt.Printf("Online CPU num: %d\n", i)
}

package main

import (
	"fmt"
	"net"
	"time"
)

func main() {
	fmt.Println("The time is ", time.Now())
	fmt.Println(net.Dial("tcp", "baidu.com:8080"))
}
package main

import "fmt"

func main() {
	defer func() {
		fmt.Println("c")
		if err:=recover(); err!=nil {
			fmt.Println(err)
		}
		fmt.Println("d")
	}()
	f()
}

func f() {
	fmt.Println("a")
	panic(55)
	fmt.Println("b")
	fmt.Println("f")
}

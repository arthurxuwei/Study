package main

import (
	"fmt"
)

type (
	interfaceA[T any] interface {
		Get() T
		Set(a T)
	}
	StructA struct {
		inner string
	}
	GenericA[T any] struct {
		inner T
	}
)

func (A *StructA) Get() string {
	return A.inner
}

func (A *StructA) Set(a string) {
	A.inner = a
}

func (A *GenericA[T]) Get() T {
	return A.inner
}

func (A *GenericA[T]) Set(a T) {
	A.inner = a
}

// test vim-go
func main() {
	fmt.Printf("hello,world\n")
	var i interfaceA[string] = &StructA{inner: "test"}
	fmt.Println(i.Get())
	i.Set("bb")
	fmt.Println(i.Get())
	var j interfaceA[string] = &GenericA[string]{inner: "generic"}
	fmt.Println(j.Get())
	j.Set("3")
	fmt.Println(j.Get())
}

package main

import "fmt"

func main() {
	var whatever [5]struct{}

	for i := range whatever {					//print 0 1 2 3 4
		fmt.Println(i)
	}
	
	for i := range whatever {					//print 4 3 2 1 0
		defer func() {fmt.Println(i)}()
	}

	for i := range whatever {					//print 4 4 4 4 4
		defer func(n int) {fmt.Println(n)}(i)
	}
}

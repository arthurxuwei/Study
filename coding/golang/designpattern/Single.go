package main

import (
	"fmt"
	"sync"
)

type Single struct {
}

var singleInstance *Single
var once sync.Once

func GetInstance() *Single  {
	once.Do(func() {
		singleInstance = &Single{}
	})
	return singleInstance
}

func GenInstance(wg *sync.WaitGroup)  {
	defer wg.Done()
	instance := GetInstance()
	fmt.Printf("instance: %p\n", instance)
}

func main()  {
	var wg sync.WaitGroup
	for i := 0; i < 250; i++  {
		wg.Add(1)
		go GenInstance(&wg)
	}
	wg.Wait()
	fmt.Println("Done")
}

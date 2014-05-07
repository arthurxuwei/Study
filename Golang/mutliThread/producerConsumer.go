package main

import (
	"log"
	"math/rand"
	"runtime"
	"sync"
	"time"
)

func consumer() {
	defer consumer_wg.Done()

	for item := range resultingChannel {
		log.Println("Consuming: ", item)
	}
}

func producer() {
	defer producer_wg.Done()

	success := rand.Float32() > 0.5
	if success {
		log.Println("Producing...")
		resultingChannel <- rand.Int()
	}
}

var resultingChannel = make(chan int)
var producer_wg sync.WaitGroup
var consumer_wg sync.WaitGroup

func main() {
	rand.Seed(time.Now().Unix())

	for c := 0; c < runtime.NumCPU(); c++ {
		producer_wg.Add(1)
		go producer()
	}
	for c := 0; c < runtime.NumCPU(); c++ {
		consumer_wg.Add(1)
		go consumer()
	}

	producer_wg.Wait()

	close(resultingChannel)

	consumer_wg.Wait()
}

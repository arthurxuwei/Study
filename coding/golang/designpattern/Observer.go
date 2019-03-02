package main

import (
	"fmt"
	"math/rand"
)

type Observer interface {
	update() int
}

type Number interface {
	getNumber() int
}

type DigitObserver struct {
	generator Number
}

func (self *DigitObserver) update() int {
	return self.generator.getNumber()
}

type NumberGenerator struct {
	observers []Observer
}

func (n *NumberGenerator) AddObserver(observer Observer) {
	n.observers = append(n.observers, observer)
}

func (n *NumberGenerator) NotifyObserver() []int {
	var result []int
	for _, observer := range n.observers {
		result = append(result, observer.update())
	}
	return result
}

type RandomNumberGenerator struct {
	*NumberGenerator
}

func NewRandomNumberGenerator() *RandomNumberGenerator {
	return &RandomNumberGenerator{&NumberGenerator{}}
}

func (r *RandomNumberGenerator) getNumber() int {
	return rand.Intn(50)
}

func (r *RandomNumberGenerator) Execute() []int {
	fmt.Println("executing")
	return r.NotifyObserver()
}

func main()  {
	random := NewRandomNumberGenerator()
	o1 := &DigitObserver{random}
	o2 := &DigitObserver{random}
	random.AddObserver(o1)
	random.AddObserver(o2)
	fmt.Println(random.Execute())
}
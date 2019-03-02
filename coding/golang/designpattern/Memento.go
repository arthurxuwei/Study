package main

import "fmt"

type Memento struct {
	Money int
}

type Game struct {
	Money int
}

func (g *Game) CreateMemento() *Memento {
	return &Memento{g.Money}
}

func (g *Game) RestoreMemento(memento *Memento) {
	g.Money = memento.Money
}

func main() {
	game := &Game{100}
	memento := game.CreateMemento()
	game.Money = 0
	game.RestoreMemento(memento)
	fmt.Println(game.Money)
}
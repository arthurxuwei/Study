package main

import (
	"fmt"
	"math/rand"
)

const(
	GUU = iota
	CHO
	PAA
)

type Hand struct {
	HandValue int
}

var Hands []*Hand

func init()  {
	Hands = []*Hand{
		&Hand{GUU},
		&Hand{CHO},
		&Hand{PAA},
	}
}

func getHand(handValue int) *Hand {
	return Hands[handValue]
}

func (h *Hand) Fight(head *Hand) int {
	if h == head {
		return 0
	} else if (h.HandValue + 1) % 3 == h.HandValue {
		return 1
	} else {
		return -1
	}
}

func (h *Hand) IsStrongerThan(hand *Hand) bool {
	return h.Fight(hand) == 1
}

func (h *Hand) IsWeakerThan(hand *Hand) bool {
	return h.Fight(hand) == -1
}

type Strategy interface {
	NextHand() *Hand
	Study(win bool)
}

type WinningStrategy struct {
	Seed int64
	Won bool
	PrevHand *Hand
}

func (w *WinningStrategy) NextHand() *Hand {
	if !w.Won {
		w.PrevHand = getHand(rand.Intn(3))
	}
	return w.PrevHand
}

func (w *WinningStrategy) Study(win bool) {
	w.Won = win
}

type Player struct {
	Name string
	Strategy Strategy
	WinCount, LoseCount, GameCount int
}

func (p *Player) NextHand() *Hand {
	return p.Strategy.NextHand()
}

func (p *Player) Win() {
	p.WinCount++
	p.GameCount++
}

func (p *Player) Lose() {
	p.LoseCount++
	p.GameCount++
}

func (p *Player) Even() {
	p.GameCount++
}

func main() {
	player1 := Player{Name: "A", Strategy:&WinningStrategy{Seed:10}}
	player2 := Player{Name: "B", Strategy:&WinningStrategy{Seed:20}}
	for i := 1; i < 50 ; i++ {
		hand1 := player1.NextHand()
		hand2 := player2.NextHand()
		if hand1.IsStrongerThan(hand2) {
			player1.Win()
			player2.Lose()
		} else if hand1.IsWeakerThan(hand2) {
			player1.Lose()
			player2.Win()
		} else {
			player1.Even()
			player2.Even()
		}
		fmt.Printf("player1: %v, player2:%v\n", player1, player2)
	}

}

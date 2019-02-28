package main

import "fmt"

type Widget interface {
	Draw()
}

type TextField struct {
	Width int
	Height int
}

func (t *TextField) Draw()  {
	fmt.Printf("TextField: %v, %v \n", t.Width, t.Height)
}


type BorderDecorator struct {
	Widget
	BorderSize int
}

type ScrollDecorator struct {
	Widget
	ScrollSize int
}

func (b *BorderDecorator) Draw() {
	fmt.Printf("BorderDecorator: %d\n", b.BorderSize)
	b.Widget.Draw()
}

func (s *ScrollDecorator) Draw() {
	fmt.Printf("ScrollDecorator: %d\n", s.ScrollSize)
	s.Widget.Draw()
}

func main()  {
	d := &ScrollDecorator{ScrollSize:2, Widget: &BorderDecorator{Widget: &TextField{Width:1, Height:2}, BorderSize:10}}
	d.Draw()
}



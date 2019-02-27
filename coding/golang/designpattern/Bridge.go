package main

import (
	"fmt"
)

type BridgePoint struct {
	X float64
	Y float64
}

type BridgeSize struct {
	Width float64
	Height float64
}

type BridgeViewport struct {
	Location BridgePoint
	Size     BridgeSize
}

type Drawer interface {
	DrawEllipseInRect(viewport BridgeViewport)
}

type OpenGL struct {}

func (gl *OpenGL) DrawEllipseInRect(viewport BridgeViewport) {
	fmt.Printf("OpenGL is drawing ellipse in rect %v", viewport)
}

type Direct2D struct {}

func (d2d *Direct2D) DrawEllipseInRect(viewport BridgeViewport) {
	fmt.Printf("Direct2D is drawing ellipse in rect %v", viewport)
}

type CircleWithDrawer struct {
	DrawingContext Drawer
	Center BridgePoint
	Radius float64
}

func (circle *CircleWithDrawer) Draw()  {
	v := BridgeViewport{
		Location: BridgePoint{
			X: circle.Center.X - circle.Radius,
			Y: circle.Center.Y - circle.Radius,
		},
		Size: BridgeSize{
			Width:  2 * circle.Radius,
			Height: 2 * circle.Radius,
		},
	}
	circle.DrawingContext.DrawEllipseInRect(v)
}

func main()  {
	circle := CircleWithDrawer{
		Center: BridgePoint{X:100, Y:100},
		Radius: 50,
	}

	circle.DrawingContext = &OpenGL{}
	circle.Draw()
	fmt.Println()
	circle.DrawingContext = &Direct2D{}
	circle.Draw()
}



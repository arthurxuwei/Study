package main

import (
	"fmt"
	"math"
)

type Shape interface {
	Draw()
}

type Point struct {
	X float64
	Y float64
}

type Size struct {
	Width float64
	Height float64
}

type Viewport struct {
	Location Point
	Size Size
}

type Document struct {
	ShapeFactories []ShapeFactory
}

func (doc *Document) Draw() {
	viewport := Viewport{Location: Point{X: 0, Y: 0},  Size:Size{ Width: 640, Height: 480}}
	for _, factory := range doc.ShapeFactories {
		shape := factory.Create(viewport)
		shape.Draw()
	}

}

type ShapeFactory interface {
	Create(viewport Viewport) Shape
}

type Circle struct {
	Location Point
	Radius float64
}

func (c *Circle) Draw() {
	fmt.Printf("Draw circle, Location: %+v, Radius: %+v\n", c.Location, c.Radius)
}
type CircleFactory struct{}

func (factory *CircleFactory) Create(viewport Viewport) Shape {
	return &Circle{Location: viewport.Location, Radius: math.Min(viewport.Size.Width, viewport.Size.Height)}
}

type Rectangle struct {
	Location Point
	Size Size
}

func (rect *Rectangle) Draw() {
	fmt.Printf("Draw rect, Location: %+v, Size: %+v\n", rect.Location, rect.Size)
}

type RactangeleFactory struct {}

func (factory *RactangeleFactory) Create(viewport Viewport) Shape {
	return &Rectangle{Location: viewport.Location, Size: viewport.Size}
}

func main()  {
	doc := &Document{ShapeFactories: []ShapeFactory{&CircleFactory{}, &RactangeleFactory{}}}
	doc.Draw()
}
package main

import "fmt"

type TemplatePrinter interface {
	Open() string
	Print() string
	Close() string
}

type AbstractDisplay struct {}

func (a *AbstractDisplay) Display(printer TemplatePrinter) string {
	result := printer.Open()
	for i := 0; i < 5; i++ {
		result += printer.Print()
	}
	result += printer.Close()
	return result
}

type CharDisplay struct {
	*AbstractDisplay
	Char rune
}

func (c *CharDisplay) Open() string {
	return "<<"
}

func (c *CharDisplay) Print() string {
	return string(c.Char)
}

func (c *CharDisplay) Close() string {
	return ">>"
}

type StringDisplay struct {
	*AbstractDisplay
	Str string
}

func (s *StringDisplay) Open() string {
	return "----"
}

func (s *StringDisplay) Print() string {
	return "| " + s.Str + " |"
}

func (s *StringDisplay) Close() string {
	return "----"
}

func main() {
	displayChar := &CharDisplay{Char: 'A'}
	fmt.Println(displayChar.Display(displayChar))
	displayStr := &StringDisplay{Str:"ABCDE"}
	fmt.Println(displayStr.Display(displayStr))
}

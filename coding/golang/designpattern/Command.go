package main

import (
	"fmt"
)

type Command interface {
	Execute() string
}

type MacroCommand struct {
	Commands []Command
}

func (m *MacroCommand) Execute() string {
	var result string
	for _, command := range m.Commands {
		result += command.Execute()
	}
	return result
}

func (m *MacroCommand) Append(command Command)  {
	m.Commands = append(m.Commands, command)
}

func (m *MacroCommand) Undo() {
	if len(m.Commands) != 0 {
		m.Commands = m.Commands[:len(m.Commands) - 1]
	}
}

func (m *MacroCommand) Clear() {
	m.Commands = []Command{}
}

type Position struct {
	X int
	Y int
}

type DrawCommand struct {
	Position *Position
}

func (d *DrawCommand) Execute() string {
	return fmt.Sprintf("%v\n", d.Position)
}

type ProcessCommand struct {
	processor int
}

func (p *ProcessCommand) Execute() string {
	return fmt.Sprintf("%d\n", p.processor)
}

func main()  {
	macro := MacroCommand{}
	macro.Append(&DrawCommand{&Position{1, 1}})
	macro.Append(&DrawCommand{&Position{2, 2}})
	macro.Append(&ProcessCommand{processor:2})
	fmt.Println(macro.Execute())
}
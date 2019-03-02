package main

import (
	"fmt"
	"strings"
)

type Context struct {
	Text         string
	Tokens       []string
	CurrentToken string
}

func NewContext(text string) *Context {
	ctx := &Context{Text: text, Tokens:strings.Fields(text)}
	ctx.NextToken()
	return ctx
}

func (c *Context) NextToken() string {
	if len(c.Tokens) == 0 {
		c.CurrentToken = ""
	} else {
		c.CurrentToken = c.Tokens[0]
		c.Tokens = c.Tokens[1:]
	}
	return c.CurrentToken
}

func (c *Context) SkipToken(token string) {
	c.NextToken()
}

type Node interface {
	Parse(ctx *Context)
	ToString() string
}

type PrimitiveCommandNode struct {
	name string
}

func (p *PrimitiveCommandNode) Parse(ctx *Context) {
	p.name = ctx.CurrentToken
	ctx.SkipToken(p.name)
}

func (p *PrimitiveCommandNode) ToString() string {
	return p.name + " "
}

type CommandNode struct {
	node Node
}

func (c *CommandNode) Parse(ctx *Context) {
	c.node = &PrimitiveCommandNode{}
	c.node.Parse(ctx)
}

func (c *CommandNode) ToString() string {
	return c.node.ToString()
}

type CommandListNode struct {
	list []Node
}

func (c *CommandListNode) Parse(ctx *Context) {
	for {
		if ctx.CurrentToken == "end" {
			break
		} else {
			cn := &CommandNode{}
			cn.Parse(ctx)
			c.list = append(c.list, cn)
		}
	}	
}

func (c *CommandListNode) ToString() string {
	var str string
	for _, l := range c.list{
		str += l.ToString()
	}
	return str
}

type ProgramNode struct {
	commandListNode Node
}

func (c *ProgramNode) Parse(ctx *Context)  {
	ctx.SkipToken("program")
	c.commandListNode = &CommandListNode{}
	c.commandListNode.Parse(ctx)
}

func (c *ProgramNode) ToString() string {
	return "program: " + c.commandListNode.ToString()
}

func main() {
	program := "program go right end"

	node := ProgramNode{}
	context := NewContext(program)
	node.Parse(context)
	fmt.Println(node.ToString())
}
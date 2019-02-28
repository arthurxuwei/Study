package main

import (
	"fmt"
	"strconv"
)

type BigChar struct {
	charName string
	fontData string
}

func (b *BigChar) loadFontData()  {
	num, _ := strconv.Atoi(b.charName)
	var str string
	for i :=0; i< num;i++{
		str += "-"
	}
	b.fontData = str
}

func NewBigChar(charName string) *BigChar {
	char := &BigChar{charName: charName}
	char.loadFontData()
	return char
}

func (b *BigChar) Print() string {
	return b.fontData
}

type BigCharFactory struct {
	pool map[string]*BigChar
}

var instance *BigCharFactory

func GetBigCharFactory() *BigCharFactory {
	if instance == nil {
		instance = &BigCharFactory{}
	}
	return instance
}

func (b *BigCharFactory) GetBigChar(charName string) *BigChar {
	if b.pool == nil {
		b.pool = make(map[string]*BigChar)
	}
	if _, ok := b.pool[charName]; !ok {
		b.pool[charName] = NewBigChar(charName)
	}
	return b.pool[charName]
}

type BigString struct {
	BigChars []*BigChar
}

func NewBigString(str string) *BigString {
	bigStr := &BigString{}
	factory := GetBigCharFactory()
	for _, s := range str {
		bigStr.BigChars = append(bigStr.BigChars, factory.GetBigChar(string(s)))
	}
	return bigStr
}

func (b *BigString) Print() string {
	var result string
	for _, s := range b.BigChars {
		result += s.Print() + "\n"
	}
	return result
}

func main()  {
	bigStr := NewBigString("121")
	fmt.Printf("result: %s", bigStr.Print())
}

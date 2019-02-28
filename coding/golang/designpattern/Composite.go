package main

import "fmt"

type MenuDesc struct {
	name        string
	description string
}

func (m *MenuDesc) Name() string {
	return m.name
}

func (m *MenuDesc) Description() string {
	return m.description
}

type MenuItem struct {
	MenuDesc
	price float32
}

func NewMenuItem(name, description string, price float32) *MenuItem {
	return &MenuItem{
		MenuDesc: MenuDesc{
			name:        name,
			description: description,
		},
		price: price,
	}
}

func (m *MenuItem) Price() float32 {
	return m.price
}

func (m *MenuItem) Print() {
	fmt.Printf("  %s, ￥%.2f\n", m.name, m.price)
	fmt.Printf("    -- %s\n", m.description)
}

type MenuComponent interface {
	Price() float32
	Print()
}

type Menu struct {
	MenuDesc
	children []MenuComponent
}

func NewMenu(name, description string) *Menu {
	return &Menu{
		MenuDesc: MenuDesc{
			name:        name,
			description: description,
		},
	}
}

func (m *Menu) Add(c MenuComponent) {
	m.children = append(m.children, c)
}

func (m *Menu) Remove(idx int) {
	m.children = append(m.children[:idx], m.children[idx+1:]...)
}

func (m *Menu) Child(idx int) MenuComponent {
	return m.children[idx]
}

func (m *Menu) Price() (price float32) {
	for _, v := range m.children {
		price += v.Price()
	}
	return
}

func (m *Menu) Print() {
	fmt.Printf("%s, %s, ￥%.2f\n", m.name, m.description, m.Price())
	fmt.Println("------------------------")
	for _, v := range m.children {
		v.Print()
	}
	fmt.Println()
}

func main() {
	menu1 := NewMenu("1", "Level 2")
	menu1.Add(NewMenuItem("1-1", "Level 2", 11.5))
	menu1.Add(NewMenuItem("1-2", "Level 2", 5.0))
	menu1.Add(NewMenuItem("1-3", "Level 2", 6.5))

	menu2 := NewMenu("2", "Level 2")
	menu2.Add(NewMenuItem("2-1", "Level 2", 15.0))
	menu2.Add(NewMenuItem("2-2", "Level 2", 11.0))
	menu2.Add(NewMenuItem("2-3", "Level 2", 4.5))

	all := NewMenu("One", "Level one")
	all.Add(menu1)
	all.Add(menu2)

	all.Print()
}




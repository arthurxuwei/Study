package main

import "fmt"

type Iterator interface {
	HasNext() bool
	Next() interface{}
}

type Aggregate interface {
	Iterator() Iterator
}

type Book struct {
	name string
}

type BookShelf struct {
	Books []*Book
}

func (b *BookShelf) Add(book *Book)  {
	b.Books = append(b.Books, book)
}

func (b *BookShelf) Iterator() Iterator {
	return &BookShelfIterator{BookShelf: b}
}

type BookShelfIterator struct {
	BookShelf *BookShelf
	last      int
}

func (b *BookShelfIterator) HasNext() bool {
	if b.last >= len(b.BookShelf.Books) {
		return false
	}
	return true
}

func (b *BookShelfIterator) Next() interface{} {
	book := b.BookShelf.Books[b.last]
	b.last++
	return book
}

func main()  {
	bookShelf := &BookShelf{}
	bookShelf.Add(&Book{"A"})
	bookShelf.Add(&Book{"B"})
	bookShelf.Add(&Book{"C"})
	for i := bookShelf.Iterator(); i.HasNext(); {
		fmt.Println(i.Next())
	}
}


package main

import "fmt"

type Element interface {
	Accept(visitor Visitor) string
}

type Entry interface {
	Element
	getSize() int
	Add(entry Entry)
}

type DefaultEntry struct {
	Entry
	Name string
}

type File struct {
	*DefaultEntry
	Size int
}

type Visitor interface {
	VisitFile(File *File) string
	VisitDir(directory *Directory) string
}

func (f *File) getSize() int {
	return f.Size
}

func (f *File) Add(entry Entry) {
}

func (f *File) Accept(visitor Visitor) string {
	return visitor.VisitFile(f)
}

type Directory struct {
	*DefaultEntry
	Dir []Entry
}

func (d *Directory) getSize() int {
	size := 0
	for _,dir := range d.Dir {
		size += dir.getSize()
	}
	return size
}

func (d *Directory) Add(entry Entry) {
	d.Dir = append(d.Dir, entry)
}

func (d *Directory) Accept(visitor Visitor) string {
	return visitor.VisitDir(d)
}

type ListVisitor struct {
	CurDir string
}

func (l *ListVisitor) VisitFile(file *File) string {
	return fmt.Sprintf("%s/%s(%d)", l.CurDir, file.Name, file.Size)
}

func (l *ListVisitor) VisitDir(directory *Directory) string {
	saveDir := l.CurDir
	list := fmt.Sprintf("%s/%s(%d)", l.CurDir, directory.Name, directory.getSize())
	l.CurDir += "/" + directory.Name
	for _, dir := range directory.Dir {
		list += dir.Accept(l)
	}
	l.CurDir = saveDir
	return list
}

func NewFile(name string, size int) *File {
	return &File{DefaultEntry: &DefaultEntry{Name: name}, Size: size}
}

func NewDirectory(name string) *Directory {
	return &Directory{DefaultEntry: &DefaultEntry{Name: name}}
}

func main()  {
	rootDir := NewDirectory("root")
	usrDir := NewDirectory("usr")
	fileA := NewFile("A", 1)

	rootDir.Add(usrDir)
	rootDir.Add(fileA)

	fileB := NewFile("B", 2)
	usrDir.Add(fileB)
	fmt.Print(rootDir.Accept(&ListVisitor{}))
}



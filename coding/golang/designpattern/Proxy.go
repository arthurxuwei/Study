package main

import "fmt"

type Printalbe interface {
	SetPrinterName(name string)
	GetPrinterName() string
	Print(str string) string
}

type Printer struct {
	name string
}

func (p *Printer) SetPrinterName(name string)  {
	p.name = name
}

func (p *Printer) GetPrinterName() string {
	return p.name
}

func (p *Printer) Print(str string) string {
	return p.name + ":" + str
}

type PrinterProxy struct {
	Name string
	real *Printer
}

func (p *PrinterProxy) SetPrinterName(name string)  {
	if p.real != nil {
		p.real.SetPrinterName(name)
	}
	p.Name = name
}

func (p *PrinterProxy) GetPrinterName() string {
	return p.Name
}

func (p *PrinterProxy) Print(str string) string {
	p.realize()
	return p.real.Print(str)
}

func (p *PrinterProxy) realize() {
	if p.real == nil {
		p.real = &Printer{p.Name}
	}
}

func main()  {
	proxy := PrinterProxy{Name: "A"}
	name := proxy.GetPrinterName()
	fmt.Println(name)
	proxy.SetPrinterName("B")
	name = proxy.GetPrinterName()
	fmt.Println(name)
	result := proxy.Print("C")
	fmt.Println(result)
}
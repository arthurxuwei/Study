package main

import "fmt"

type Trouble struct {
	Number int
}

type Support interface {
	Resolve(trouble Trouble) bool
	Handle(support Support, trouble Trouble) string
}

type DefaultSupport struct {
	Support
	Name string
	Next Support
}

func (d *DefaultSupport) Handle(support Support, trouble Trouble) string {
	if support.Resolve(trouble) {
		return d.Done(trouble)
	} else if d.Next != nil {
		return d.Next.Handle(d.Next, trouble)
	} else {
		return d.Fail(trouble)
	}
}

func (d *DefaultSupport) Done(trouble Trouble) string {
	return fmt.Sprintf("trouble: %d is resolved by %s", trouble.Number, d.Name)
}

func (d *DefaultSupport) Fail(trouble Trouble) string {
	return fmt.Sprintf("trouble: %d cannot be resolved by %s", trouble.Number, d.Name)
}

type NoSupport struct {
	*DefaultSupport
}

func (n *NoSupport) Resolve(trouble Trouble) bool {
	return false
}

func NewNoSupport(name string) *NoSupport {
	return &NoSupport{&DefaultSupport{Name: name}}
}

type LimitSupport struct {
	*DefaultSupport
	Limit int
}

func (l *LimitSupport) Resolve(trouble Trouble) bool {
	if trouble.Number < l.Limit {
		return true
	} else {
		return false
	}
}

func NewLimitSupport(name string, limit int) *LimitSupport {
	return &LimitSupport{&DefaultSupport{Name: name}, limit}
}

func main()  {
	a := NewNoSupport("A")
	b := NewLimitSupport("B", 2)
	c := NewLimitSupport("C", 3)
	a.Next = b
	b.Next = c

	fmt.Println(a.Handle(a, Trouble{1}))
	fmt.Println(a.Handle(a, Trouble{2}))
	fmt.Println(a.Handle(a, Trouble{3}))
}

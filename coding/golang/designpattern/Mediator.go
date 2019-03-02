package main

import "fmt"

type Mediator interface {
	createColleagues()
	colleagueChanged()
}

type Colleague interface {
	setColleagueEnabled(enabled bool)
}

type Button struct {
	Enabled bool
	Mediator Mediator
}

func (b *Button) setColleagueEnabled(enabled bool) {
	b.Enabled = enabled
}

type RadioButton struct {
	Button
	Checked bool
}

func (r *RadioButton) setColleagueEnabled(enabled bool) {
	r.Enabled = enabled
}

func (r *RadioButton) Check(checked bool) {
	r.Checked = checked
	r.Mediator.colleagueChanged()
}

type LoginForm struct {
	RadioButton RadioButton
	Button      Button
}

func (l *LoginForm) createColleagues() {
	l.RadioButton = RadioButton{}
	l.Button = Button{}
	l.RadioButton.Mediator = l
	l.Button.Mediator = l
}

func (l *LoginForm) colleagueChanged() {
	if !l.RadioButton.Checked {
		l.Button.setColleagueEnabled(false)
	} else {
		l.Button.setColleagueEnabled(true)
	}

}

func NewLoginFrom() *LoginForm {
	form := &LoginForm{}
	form.createColleagues()
	return form
}

func main() {
	loginForm := NewLoginFrom()
	fmt.Println(loginForm.Button.Enabled)
	loginForm.RadioButton.Check(true)
	fmt.Println(loginForm.Button.Enabled)
}

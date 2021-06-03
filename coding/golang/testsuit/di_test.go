package main

import (
	"bytes"
	"fmt"
	"io"
	"os"
	"testing"
)

func TestGreet(t *testing.T) {
	buffer := bytes.Buffer{}
	Greet(&buffer, "Chris")

	got := buffer.String()
	want := "Hello, Chris"
	if got != want {
		t.Errorf("got '%s' want '%s'", got, want)
	}

	Greet(os.Stdout, "Arthur")
}

func Greet(writer io.Writer, name string) {
	fmt.Fprintf(writer,"Hello, %s", name)
}

// Copyright 2011 Google Inc. All rights reserved.
// Use of this source code is governed by the Apache 2.0
// license that can be found in the LICENSE file.

package helloworld

import (
	"html/template"
	"net/http"
)

func init() {
	http.HandleFunc("/", handle)
}

func renderTemplate(w http.ResponseWriter, content string) {

	var templates = template.Must(template.ParseFiles("views/main.html"))
	templates.New("pageContent").ParseFiles("views/pageContent.html")

	err := templates.Execute(w, content)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func handle(w http.ResponseWriter, r *http.Request) {
	renderTemplate(w, "hello,world!")
}

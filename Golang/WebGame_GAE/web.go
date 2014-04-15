package webgame

import (
	"html/template"
	"net/http"
	"time"
)

func init() {
	http.HandleFunc("/", handle)
}

func renderTemplate(w http.ResponseWriter, content string) {

	var templates = template.Must(template.ParseFiles("views/main.html"))
	templates.New("pageHeader").ParseFiles("views/pageHeader.html")
	templates.New("pageContent").ParseFiles("views/pageContent.html")
	templates.New("pageFooter").ParseFiles("views/pageFooter.html")

	err := templates.Execute(w, content)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func handle(w http.ResponseWriter, r *http.Request) {
	renderTemplate(w, time.Now().Format(time.ANSIC))
}

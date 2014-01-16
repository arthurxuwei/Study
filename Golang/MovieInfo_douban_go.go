package main

import (
    "fmt"
    "net/http"
	"regexp"
	"bytes"
)


func hq_url(gjz string) {
	so_url := "http://movie.douban.com/subject_search?search_text="
	resp, err := http.Get(so_url+gjz)
	if err != nil {fmt.Println(err)}
	buf := new(bytes.Buffer)
	buf.ReadFrom(resp.Body)
	var valid = regexp.MustCompile(`<a class="nbg" href=(.*?) onclick`)
	r := valid.FindAll(buf.Bytes(), -1)
//	n := len(r[0])
//	fmt.Println(string(r[0][:n]))
	valid = regexp.MustCompile(`http://(.*?) `)
	t := r[0]
	r1 := valid.Find(t)
//	fmt.Println(string(r1[:len(r1)]))
	r_url := string(r1[:len(r1)-1])
	resp, err = http.Get(r_url)
	if err != nil {fmt.Println(err)}
	buf = new(bytes.Buffer)
	buf.ReadFrom(resp.Body)
//	fmt.Println(buf.String())
	valid = regexp.MustCompile(`<span property="v:summary" class="">(.*?)</span>`)
	r2 := valid.Find(buf.Bytes())
	fmt.Println(string(r2[:len(r2)]))
}

func main() {
	var gjz string
    _, err := fmt.Scanf("%s", &gjz)
	if err != nil {fmt.Println(err)}
    hq_url(gjz)
}
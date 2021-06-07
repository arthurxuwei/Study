package main

import (
	"encoding/json"
	"fmt"
	"log"
	"strings"
)
import   "github.com/elastic/go-elasticsearch/v8"

func main() {
	var (
		r map[string]interface{}
	)
	cfg := elasticsearch.Config{
		Addresses: []string{
			"http://localhost:9200",
		},
		// ...
	}

	es, err := elasticsearch.NewClient(cfg)
	if err != nil {
		fmt.Printf("Error creating the client: %s", err)
	}
	res, err := es.Info()
	if err != nil {
		fmt.Printf("Error get info: %s", err)
	}
	defer res.Body.Close()
	if res.IsError() {
		fmt.Println(err)
	}
	if err := json.NewDecoder(res.Body).Decode(&r); err != nil {
		log.Fatalf("Error parsing the response body: %s", err)
	}

	log.Printf("Client: %s", elasticsearch.Version)
	log.Printf("Server: %s", r["version"].(map[string]interface{})["number"])
	log.Println(strings.Repeat("~", 37))
}

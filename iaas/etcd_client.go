package main

import (
	"fmt"
	"github.com/coreos/go-etcd/etcd"
)

func main() {
	machines := []string{"http://172.17.8.101:4001"}
	client := etcd.NewClient(machines)

	if _, err := client.Set("/foo", "bar", 0); err != nil {
		fmt.Println(err)
	}
	fmt.Println("done")
	value, err := client.Get("/foo", false, false)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println("key: " + value.Node.Key)
		fmt.Println("value: " + value.Node.Value)
	}

}

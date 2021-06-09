package main

import (
	"context"
	"fmt"
	clientV3 "go.etcd.io/etcd/client/v3"
	"time"
)

func main() {
	client, err := clientV3.New(clientV3.Config{
		Endpoints: []string{"http://172.17.8.101:4001"},
	})
	if err != nil {
		// handle error!
		return
	}
	defer client.Close()
	ctx, cancel := context.WithTimeout(context.Background(), 3 * time.Second)
	resp, err := client.Put(ctx, "test", "1")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Printf("done, %v\n", resp)
	value, err := client.Get(ctx, "test")
	cancel()
	if err != nil {
		fmt.Println(err)
	}
	fmt.Printf("done, %v\n", value)

}

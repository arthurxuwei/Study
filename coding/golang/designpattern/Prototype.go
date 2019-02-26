package main

import "fmt"

type Config struct {
	workDir string
	user string
}

func NewConfig(user string, workDir string) Config {
	return Config{user:user, workDir:workDir}
}

func (c Config) WithWorkDir(dir string) Config {
	c.workDir = dir
	return c
}

func (c Config) WithUser(user string) Config {
	c.user = user
	return c
}


func main()  {
	config := NewConfig("guest", "/home/guest")
	rootConfig := config.WithUser("root").WithWorkDir("/root")
	fmt.Printf("guest: %s #type: %T &=%p\nroot: %s #type: %T &=%p\n", config, config, &config, rootConfig, rootConfig, &rootConfig)
}
package main

import "fmt"

type GirlFriend struct {
	nationality string
	language string
}

type AbstractFactory interface {
	CreateMyLove() GirlFriend
}

type JapanGirlFriendFactory struct {

}

type KoreanGirlFriendFactory struct {

}

func (a JapanGirlFriendFactory) CreateMyLove() GirlFriend {
	return GirlFriend{"Japan", "Japanese"}
}

func (a KoreanGirlFriendFactory) CreateMyLove() GirlFriend {
	return GirlFriend{"Korean", "Korean"}
}

func getGirlFriend(typeGf string) GirlFriend {
	var gffact AbstractFactory
	switch typeGf {
	case "Japan":
		gffact = JapanGirlFriendFactory{}
	case "Korean":
		gffact = KoreanGirlFriendFactory{}
	}
	return gffact.CreateMyLove()
}

func main() {
	a := getGirlFriend("Japan")
	b := getGirlFriend("Korean")
	fmt.Println(a)
	fmt.Println(b)
}
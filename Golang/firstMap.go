package main
import "fmt"
type Vertex struct {
	Lat, Long float64
}

var m = map[string]Vertex {
	"Xu": {
		12,321,
	},
	"123": {
		123,4321,
	},
}

func main() {
//	m = make(map[string]Vertex)
	m["Arthur"] = Vertex{
		111,111,
	}
	
	fmt.Println(m["Arthur"])
	fmt.Println(m)

	n := make(map[string]int)
	n["Answer"] = 42
	
	fmt.Println(n["Answer"])
	fmt.Println(n)
	
	delete(n, "Answer")
	fmt.Println(n["Answer"])
	fmt.Println(n)
	
	v, ok := n["Answer"]
	fmt.Println(v, ok)
}
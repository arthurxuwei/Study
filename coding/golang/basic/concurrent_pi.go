package main
import ("fmt"
		"math"
		)

func main(){
	fmt.Println("Start...")
	fmt.Println(pi(100))
	fmt.Println("End...")
}

func pi(n int) float64{
	ch := make(chan float64)
	for k := 0; k <= n; k++ {
		fmt.Println(k)
		go term(ch, float64(k))
	}
	f := 0.0
	for k := 0; k<= n; k++ {
		f += <- ch
	}
	return f
}

func term(ch chan float64, k float64) {
	ch <- 4 * math.Pow(-1, k) / (2*k + 1)
}
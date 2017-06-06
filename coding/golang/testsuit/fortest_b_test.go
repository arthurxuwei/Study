package intpkg

import(
	"testing"
)

func Benchmark_TheAddIntsFunction(b *testing.B) {
	for i := 0; i < b.N; i++ {
		Add2Ints(4, 5)
	}
}

func Benchmark_TimeConsumingFunction(b *testing.B) {
	b.StopTimer()
	//do any time consuming initialization functions here ... 
	b.StartTimer()
	for i := 0; i < b.N; i++ {
		Add2Ints(4, 5)
	}
}

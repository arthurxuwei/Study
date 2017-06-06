package intpkg

import(
	"testing"
)

func Test_Add2Ints_1(t *testing.T) {
	if (Add2Ints(3, 4) != 7){
		t.Error("Add2Ints did not work as expected.")
	} else {
		t.Log("one test passed.")
	}
}

func Test_Add2Ints_2(t *testing.T) {
//	t.Error("Show Error.")
}
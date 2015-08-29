package main
import(
	"fmt"
	"github.com/coreos/go-etcd/etcd"
)

func main() {
	machines := []string{"http://172.17.8.101:2375"}
	client := etch.NewClient(machines)
	
	if _, err :=client.Set("/foo", "bar", 0); err != null{
		fmt.println(err)
	}
}
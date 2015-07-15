package main

import (
	"fmt"
	"github.com/op/go-nanomsg"
)

func main() {
	var num = 0
	socket, err := nanomsg.NewPullSocket()
	if err != nil {
		fmt.Println("error comes")
		return
	}
	socket.Bind("ipc:///tmp/testipc2.ipc")
	for {
		tmpbuf, err2 := socket.Recv(0)
		if err2 != nil {
			fmt.Println("error comes")
			return
		}
		num++
		fmt.Println("get the msg with: %d", len(tmpbuf))
		fmt.Println("%d received", num)
	}
}

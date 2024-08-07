package main

import "fmt"

func c(i int) int {
	// Self-increasement is a statement, rather an opertor. It
	// must be in its own line.
	i++

	// And this is invalid.
	//j := i++

	// This is invalid in Go.
	//++i

	//fmt.Println("%v %v", j, k)

	return i
}

func main() {
	fmt.Println("return:", c(9))
}

package main

import "fmt"

// named return value
func b() (i int) {
	defer func() {
		i++
		fmt.Println("defer2:", i)
	}()
	defer func() {
		i++
		fmt.Println("defer1:", i)
	}()
	return i //或者直接写成return
}

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
	fmt.Println("return:", b())
}

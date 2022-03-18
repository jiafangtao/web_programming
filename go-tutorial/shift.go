package main

import "fmt"

func main() {

    // Left shift
    var i int = 1
    var j int = i << 1
    var k int = j << 1
    fmt.Printf("i = %d, j = %d, k = %d\n", i, j, k)

    var kb int = 1024
    var halfkb int = kb >> 1
    fmt.Printf("kb: %d, half: %d\n", kb, halfkb)
}

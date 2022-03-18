package main

import "fmt"

func main() {
    var i int = 1024
    var j int = 4096
    var k int = 8192
    var pi = &i
    var pj = &j
    var pk = &k
    fmt.Println("Address of i is", pi)
    fmt.Println("Address of j is", pj)
    fmt.Println("Address of k is", pk)
}

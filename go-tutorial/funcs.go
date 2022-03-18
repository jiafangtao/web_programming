package main

import "fmt"

func sayHello() {
    fmt.Println("Hello Go")
}

func sayHelloTo(name string) {
    fmt.Println("Hello", name)
}

func greetTo(greeting, name string) {
    fmt.Println(greeting, name)
}

func main() {
    sayHello()

    sayHelloTo("Kitty")

    greetTo("Morning", "Bruce")

    // The function can be also called even it's defined after the "main".
    someLateFunc()
}

func someLateFunc() {
    fmt.Println("calling some late func")
}

fn main() {
    println!("Sample code from Chapter 15.");

    c15_1();

    c15_7();


    c15_8();
}

fn c15_1() {
    let b = Box::new(5);
    println!("b = {}", b);

    // Another syntax is like this
    println!("b = {b}");
}

fn c15_7() {
    let x = 5;
    let y = Box::new(x);

    assert_eq!(5, x);
    assert_eq!(5, *y);

    println!("x == *y == 5");
}

fn c15_8() {
    let x = MyBox::new(100);
    assert_eq!(100, *x);

    println!("x={:?}", *x);

    let y = UInt32Box::new(101);
    println!("y={:?}", *y);
}


use std::ops::Deref;
use std::fmt::Display;


struct MyBox<T: Display>(T);

impl<T: Display> MyBox<T> {

    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}

impl<T: Display> Deref for MyBox<T> {

    type Target = T; // this is required by the trait definition

    fn deref(&self) -> &T {
        &self.0
    }
}

impl<T: Display> Drop for MyBox<T> {
    fn drop(&mut self) {
        println!("calling drop of MyBox<T> with value {}", self.0);
    }
}

type UInt32Box = MyBox<u32>;

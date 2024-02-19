fn main() {
    println!("Sample code from Chapter 15.");

    c15_1();
}

fn c15_1() {
    let b = Box::new(5);
    println!("b = {}", b);

    // Another syntax is like this
    println!("b = {b}");
}

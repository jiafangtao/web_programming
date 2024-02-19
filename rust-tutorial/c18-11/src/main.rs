fn main() {

    let x = Some(5);
    let y = 10;
    match x {
        Some(50) => println!("Got 50"),
        Some(y) => println!("Matched, y = {y}"),
        _ => println!("Default case, x = {:?}", x),
    }
    println!("at the end: x = {:?}, y = {y}", x);

    println!("\ndemo - pattern matching for multiple values");
    multi_match();

    println!("\nListing 18-13");
    ch18_13();
}

/// Demonstrate the usage of range in Rust
fn multi_match() {
    let x = 5;
    match x {
        1..=5 => println!("one through five"),
        _ => println!("something else"),
    }
}

struct Point {
    x: i32,
    y: i32
}

/// Destruct struct values
fn ch18_13() {
    let p = Point {x: 100, y: 90};
    let Point {x, y} = p;

    assert_eq!(x, 100);
    assert_eq!(y, 90);

    println!("x = {x}, y = {y}");
}
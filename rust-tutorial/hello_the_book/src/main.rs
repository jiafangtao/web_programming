fn main() {
    println!("Hello, world!");
    test_if_let_syntax();
}

fn test_if_let_syntax() {
    let config_max = Some(3u8);
    match config_max {
        Some(max) => println!("the max is configured to {}", max),
        _ => (),
    }
}

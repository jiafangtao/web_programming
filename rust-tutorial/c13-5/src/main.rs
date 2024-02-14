fn main() {
    let mut list = vec![1, 2, 3];

    println!("Before defining closure: {:?}", list);
    
    let mut borrows_mutably = || list.push(7);

    //println!("This should NOT compile. Before running closure: {:?}", list);

    borrows_mutably();
    
    println!("After calling closure: {:?}", list);
}

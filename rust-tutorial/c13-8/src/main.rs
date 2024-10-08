#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}
fn main() {
    let mut list = [
        Rectangle {
            width: 10,
            height: 1,
        },
        Rectangle {
            width: 3,
            height: 5,
        },
        Rectangle {
            width: 7,
            height: 12,
        },
    ];
    let mut sort_operations = vec![];
    //let value = String::from("by key called");
    
    println!("============ sorting by width ==============");
    list.sort_by_key(|r| {
        //sort_operations.push(value); // this doesn't compile.
        sort_operations.push("some liternal should work here");
        r.width
    });
    println!("{:#?}", list);

    println!("============ sorting by height ==============");

    list.sort_by_key(|r| r.height);
    println!("{:#?}", list);
}

use std::sync::mpsc;
use std::thread;
use std::time::Duration;

fn main() {
    println!("Welcome to chapter 16. Fearless Concurrency!");

    c16_8();
    println!("=========================================");
    
    c16_10();
}

fn c16_8() {
    let (tx, rx) = mpsc::channel();

    thread::spawn(move || {
        println!("running in worker thread ...");
        for i in 1..10 {
            println!("round #{i}");
            tx.send(i).unwrap();
        }
    });

    loop {
        // After the tx finishes its work, rx will get an error like
        // "receiving on a closed channel". That's the right time for
        // us to quit the loop.
        let received = rx.recv().unwrap_or_else(|err| {
            println!("Failed to receive in main thread: {err}");
            println!("End the loop now.");
            -1
        });
        if received == -1 {
            break;
        } else {
            println!("main thread got: {}", received);
        }
    }

    println!("main thread ended");
}

fn c16_10() {
    let (tx, rx) = mpsc::channel();

    thread::spawn(move || {
        println!("running in worker thread ...");
        for i in 1..10 {
            println!("round #{i}");
            tx.send(i).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    // This is a more elegant way to get all 
    // messages in a channel than liting c16_8.
    for received in rx {
        println!("main thread got {}", received);
    }

    println!("main thread ended");
}

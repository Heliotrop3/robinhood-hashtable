use clap::Parser; // CLI
use std::sync::{Arc, Mutex};
use std::thread;

// TODO: This looks clunky - there's probably a cleaner way.
/* User-defined files */
use crate::chopstick::Chopstick;
use crate::philosopher::Philosopher;
use crate::philosopher::PhilosopherState;

mod chopstick;
mod philosopher;

/* End of User-defined files */

#[derive(Parser)]
struct Cli {
    /// Number of threads to spin up
    philosopher_count: u32,
}

fn main() {
    let args = Cli::parse(); // Throws error if non-integer value provided

    println!(
        "Number of Philosophers at table: {}",
        args.philosopher_count
    );

    // Really defeats the whole point of the program - there should always be 2+ Philosophers
    if args.philosopher_count == 1 {
        println!("Error: Only 1 Philosopher was invited and they're a depressed existential nihilist - they should not dine alone.");
        return;
    }

    // Vector rather than array because an array requires a compile-time constant
    let mut philosophers = Vec::new();
    let mut silverware = Vec::new();

    // Place the silverware
    for n in 0..args.philosopher_count {
        /*
            I need a better understanding of the Rust memory ownership

            Specifically, I'm not sure if the issue is with the array I'm creating
            or how I'm trying to use Arc::new(). The base idea is we store the Phils
            in an array and when they want to eat they index into the silverware vector.
            The issue is the current implementation does not in fact allow us to index
            into the vector. The compiler is informative but implementing the thing(s)
            it's saying it needs doesn't seem like the right solution. Rather then the
            issue appears to be

            - Incorrect instantion of the Vector: Wrong placement of Arc call?
            - Incorrect\Incomplete understanding of passing variables into closures
        */
        let mut guard = Arc::new(Mutex::new(Chopstick {
            name: "Chopstick ".to_string() + &n.to_string(),
        }));
        silverware.push(guard);
    }
    println!("Number of chopsticks: {}\n", silverware.len());

    
    // Seat the Philosophers
    for n in 0..args.philosopher_count {
        let mut p: Philosopher = Philosopher::new(&("Philosopher ".to_owned() + &n.to_string()), n);

        // * Existential Philosopher noises *
        let handle = thread::spawn(move || loop {
            
            match p.state {
                PhilosopherState::Thinking => p.think(),
                PhilosopherState::Eating => { p.eat(); }
            }
        });

        philosophers.push(handle)
    }

    loop {} // spin
}

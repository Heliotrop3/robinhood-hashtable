use std::time::Duration;

use rand::Rng; // Get random number for think/eat duration
use std::thread; // thread.sleep()
                 // use std::time::Duration; // from_seconds()

pub enum PhilosopherState {
    Thinking, // Default status
    Eating,
}

pub struct Philosopher {
    pub name: String,
    pub state: PhilosopherState,

    /// Index of where they are seated
    pub seat_number: u32,
}

impl Philosopher {
    pub fn new(name: &str, seat_number: u32) -> Philosopher {
        Philosopher {
            name: name.to_string(),
            seat_number: seat_number,
            state: PhilosopherState::Thinking,
        }
    }

    pub fn think(&mut self) {
        // Lower and upper bounds could be parametized
        let seconds_to_think = rand::thread_rng().gen_range(5..=15);

        println!("{} is thinking for {} seconds", self.name, seconds_to_think);
        thread::sleep(Duration::from_secs(seconds_to_think));

        self.state = PhilosopherState::Eating;
        return;
    }

    pub fn eat(&mut self) {
        println!("{} tried eating but this is NOT IMPLEMENTED", self.name);
        self.state = PhilosopherState::Thinking;
    }
}

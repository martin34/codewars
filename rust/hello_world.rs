use std::sync::atomic::{AtomicU32, Ordering};

struct Person
{
    id : u32,
    name : String,
}

impl Person
{
    fn new(name : String) -> Person
    {
        static NEXT_ID : AtomicU32 = AtomicU32::new(0);
        let id = NEXT_ID.fetch_add(1, Ordering::Relaxed);
        Person{id:id, name:name}
    }
}

impl ToString for Person
{
    fn to_string(&self) -> String
    {
        return format!("a person named {} with id {}", self.name, self.id);
    }
}

fn main() {
    println!("Hello World!");
    let a_number = 13;
    let another_number = 5;
    println!("{} + {} = {}", a_number, another_number, (a_number + another_number));

    let hans = <Person>::new("Hans".to_string());
    let xaver = <Person>::new("Xaver".to_string());
    print!("{}", hans.to_string());
    println!(" and {}", xaver.to_string());
}


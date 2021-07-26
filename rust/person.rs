use std::sync::atomic::{AtomicU32, Ordering};

pub struct Person
{
    id : u32,
    name : String,
}

impl Person
{
    pub fn new(name : String) -> Person
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

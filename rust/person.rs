use std::sync::atomic::{AtomicU32, Ordering};

#[derive(PartialEq)]
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

    pub fn get_name(&self) -> String
    {
        self.name.clone()
    }

    pub fn get_id(&self) -> u32
    {
        self.id
    }
}

impl ToString for Person
{
    fn to_string(&self) -> String
    {
        return format!("a person named {} with id {}", self.name, self.id);
    }
}

impl Clone for Person
{
    fn clone(&self) -> Person
    {
        Person::new(self.get_name())
    }
}

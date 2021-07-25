struct Person
{
    id : u32,
    name : String,
}

impl Person
{
    fn new(name : String) -> Person
    {
        unsafe{
        static mut NEXT_ID : u32 = 0;
        NEXT_ID += 1;
        Person{id:NEXT_ID, name:name}
        }
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


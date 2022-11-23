
extern crate person;

use person::Person;

extern "C" {
    pub fn Get8FromCpp() -> u8;
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

    unsafe {
    println!("Get number form cpp: {}", Get8FromCpp());
    }

}


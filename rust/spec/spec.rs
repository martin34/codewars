extern crate person;


#[cfg(test)]
mod tests {

use person::Person;

    #[test]
    fn test_person_to_string() {
        let person = <Person>::new("Hans".to_string());
        assert!(person.to_string().contains("a person named Hans with id"));
    }

    #[test]
    fn test_person_to_string_two() {
        let person = <Person>::new("Xaver".to_string());
        assert!(person.to_string().contains("a person named Xaver with id"));
    }
}

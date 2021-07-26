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

    #[test]
    fn test_multiple_persons_check_id(){
        let hans = <Person>::new("Hans".to_string());
        let xaver = <Person>::new("Xaver".to_string());
        assert_ne!(hans.get_id(), xaver.get_id());
    }

    #[test]
    fn test_multiple_persons(){
        let hans = <Person>::new("Hans".to_string());
        let xaver = <Person>::new("Xaver".to_string());
        let persons = vec![hans, xaver];
        for person in persons{
            if person.get_name() == "Hans"{
                assert!(person.to_string().contains("a person named Hans with id"));
            }
            else{
                assert!(person.to_string().contains("a person named Xaver with id"));
            }
        }
    }
}

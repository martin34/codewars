extern crate person;

#[cfg(test)]
mod tests {

    use person::Person;
    use std::rc::Rc;

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
    fn test_multiple_persons_check_id() {
        let hans = <Person>::new("Hans".to_string());
        let xaver = <Person>::new("Xaver".to_string());
        assert_ne!(hans.get_id(), xaver.get_id());
    }

    #[test]
    fn test_multiple_persons() {
        let hans = <Person>::new("Hans".to_string());
        let xaver = <Person>::new("Xaver".to_string());
        let persons = vec![hans, xaver];
        for person in persons {
            if person.get_name() == "Hans" {
                assert!(person.to_string().contains("a person named Hans with id"));
            } else {
                assert!(person.to_string().contains("a person named Xaver with id"));
            }
        }
    }

    #[test]
    fn test_clone_person() {
        let hans = <Person>::new("Hans".to_string());
        let clone = hans.clone();
        assert_eq!(hans.get_name(), clone.get_name());
        assert_ne!(hans.get_id(), clone.get_id());
    }

    #[test]
    fn test_trait_container() {
        let hans = <Person>::new("Hans".to_string());
        let pointer: Rc<dyn ToString> = Rc::new(hans);
        assert!(pointer.to_string().contains("a person named Hans with id"));
    }
}

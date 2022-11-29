extern crate pocker_lib;

#[cfg(test)]
mod tests {

    use pocker_lib::Card;
    use pocker_lib::Face;
    use pocker_lib::Suit;
    use std::str::FromStr;

    use parameterized::parameterized;

    #[test]
    fn test_card_from_values() {
        let _card = Card {
            suit: Suit::Heart,
            face: Face::Ace,
        };
    }
    #[test]
    fn test_card_equals() {
        let lhs = Card {
            suit: Suit::Heart,
            face: Face::Ace,
        };
        let rhs = Card {
            suit: Suit::Heart,
            face: Face::Ace,
        };
        assert_eq!(lhs, rhs);
    }
    #[test]
    fn test_from_string_with_invalid_char_for_suit() {
        let lhs = Card::from_str("AX");
        assert!(lhs.is_err());
    }
    #[parameterized(s = {String::from("AH"),
                         String::from("AP"), 
                         String::from("AT"), 
                         String::from("AC")}, 
                    card = {Card{suit: Suit::Heart, face: Face::Ace},
                            Card{suit: Suit::Pike, face: Face::Ace},
                            Card{suit: Suit::Tile, face: Face::Ace},
                            Card{suit: Suit::Clover,face: Face::Ace}}
                    )]
    fn test_from_string(s: String, card: Card) {
        assert_eq!(Card::from_str(&s[..]).unwrap(), card)
    }
}

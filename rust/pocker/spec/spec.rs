extern crate pocker_lib;


#[cfg(test)]
mod tests {

use pocker_lib::Card;
use pocker_lib::Suit;
use pocker_lib::Face;
use std::str::FromStr;

    #[test]
    fn test_card_from_values() {
        let _card = Card{suit: Suit::Heart, face: Face::Ace};
    }
    #[test]
    fn test_card_equals() {
        let lhs = Card{suit: Suit::Heart, face: Face::Ace};
        let rhs = Card{suit: Suit::Heart, face: Face::Ace};
        assert_eq!(lhs, rhs);
    }
    #[test]
    fn test_from_string_AH() {
        let lhs = Card::from_str("AH");
        let expect = Card{suit: Suit::Heart, face: Face::Ace};
        assert_eq!(lhs.unwrap(), expect);
    }
    #[test]
    fn test_from_string_AP() {
        let lhs = Card::from_str("AP");
        let expect = Card{suit: Suit::Pike, face: Face::Ace};
        assert_eq!(lhs.unwrap(), expect);
    }
    #[test]
    fn test_from_string_AT() {
        let lhs = Card::from_str("AT");
        let expect = Card{suit: Suit::Tile, face: Face::Ace};
        assert_eq!(lhs.unwrap(), expect);
    }
    #[test]
    fn test_from_string_AC() {
        let lhs = Card::from_str("AC");
        let expect = Card{suit: Suit::Clover, face: Face::Ace};
        assert_eq!(lhs.unwrap(), expect);
    }
    #[test]
    fn test_from_string_AX() {
        let lhs = Card::from_str("AX");
        assert!(lhs.is_err());
    }
}

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

    struct ParserTestParams {
        input: String,
        output: Card,
    }
    #[parameterized(
        p = {
            ParserTestParams{input: String::from("AH"), output: Card{suit: Suit::Heart, face: Face::Ace}},
            ParserTestParams{input: String::from("AP"), output: Card{suit: Suit::Pike, face: Face::Ace}},
            ParserTestParams{input: String::from("AT"), output: Card{suit: Suit::Tile, face: Face::Ace}},
            ParserTestParams{input: String::from("AC"), output: Card{suit: Suit::Clover, face: Face::Ace}},
        })]
    fn test_from_string_with_varying_suit(p: ParserTestParams) {
        assert_eq!(Card::from_str(&p.input[..]).unwrap(), p.output)
    }

    #[parameterized(
        p = {
            ParserTestParams{input: String::from("2H"), output: Card{suit: Suit::Heart, face: Face::Two}},
            ParserTestParams{input: String::from("3H"), output: Card{suit: Suit::Heart, face: Face::Three}},
            ParserTestParams{input: String::from("4H"), output: Card{suit: Suit::Heart, face: Face::Four}},
            ParserTestParams{input: String::from("5H"), output: Card{suit: Suit::Heart, face: Face::Five}},
            ParserTestParams{input: String::from("6H"), output: Card{suit: Suit::Heart, face: Face::Six}},
            ParserTestParams{input: String::from("7H"), output: Card{suit: Suit::Heart, face: Face::Seven}},
            ParserTestParams{input: String::from("8H"), output: Card{suit: Suit::Heart, face: Face::Eight}},
            ParserTestParams{input: String::from("9H"), output: Card{suit: Suit::Heart, face: Face::Nine}},
            ParserTestParams{input: String::from("TH"), output: Card{suit: Suit::Heart, face: Face::Ten}},
            ParserTestParams{input: String::from("JH"), output: Card{suit: Suit::Heart, face: Face::Jack}},
            ParserTestParams{input: String::from("QH"), output: Card{suit: Suit::Heart, face: Face::Queen}},
            ParserTestParams{input: String::from("KH"), output: Card{suit: Suit::Heart, face: Face::King}},
            ParserTestParams{input: String::from("AH"), output: Card{suit: Suit::Heart, face: Face::Ace}},
        })]
    fn test_from_string_with_varying_face(p: ParserTestParams) {
        assert_eq!(Card::from_str(&p.input[..]).unwrap(), p.output)
    }

    #[test]
    fn test_from_string_with_to_many_characters() {
        let lhs = Card::from_str("AHAH");
        assert!(lhs.is_err());
    }
}

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

    #[rustfmt::skip]
    #[test]
    fn test_trivial_order() {
        assert!(Card{suit: Suit::Heart, face: Face::Two} < Card{suit: Suit::Heart, face: Face::Three});
        assert!(Card{suit: Suit::Heart, face: Face::Three} < Card{suit: Suit::Heart, face: Face::Four});
        assert!(Card{suit: Suit::Heart, face: Face::Four} < Card{suit: Suit::Heart, face: Face::Five});
        assert!(Card{suit: Suit::Heart, face: Face::Five} < Card{suit: Suit::Heart, face: Face::Six});
        assert!(Card{suit: Suit::Heart, face: Face::Six} < Card{suit: Suit::Heart, face: Face::Seven});
        assert!(Card{suit: Suit::Heart, face: Face::Seven} < Card{suit: Suit::Heart, face: Face::Eight});
        assert!(Card{suit: Suit::Heart, face: Face::Eight} < Card{suit: Suit::Heart, face: Face::Nine});
        assert!(Card{suit: Suit::Heart, face: Face::Nine} < Card{suit: Suit::Heart, face: Face::Ten});
        assert!(Card{suit: Suit::Heart, face: Face::Ten} < Card{suit: Suit::Heart, face: Face::Jack});
        assert!(Card{suit: Suit::Heart, face: Face::Jack} < Card{suit: Suit::Heart, face: Face::Queen});
        assert!(Card{suit: Suit::Heart, face: Face::Queen} < Card{suit: Suit::Heart, face: Face::King});
        assert!(Card{suit: Suit::Heart, face: Face::King} < Card{suit: Suit::Heart, face: Face::Ace});

        assert!(Card{suit: Suit::Pike, face: Face::King} < Card{suit: Suit::Heart, face: Face::Ace});
    }

    #[rustfmt::skip]
    #[test]
    fn test_trivial_eq() {
        assert!(Card{suit: Suit::Heart, face: Face::Two} != Card{suit: Suit::Heart, face: Face::Three});
        assert!(Card{suit: Suit::Heart, face: Face::Three} != Card{suit: Suit::Heart, face: Face::Four});
        assert!(Card{suit: Suit::Heart, face: Face::Queen} == Card{suit: Suit::Heart, face: Face::Queen});
        assert!(Card{suit: Suit::Heart, face: Face::Ace} == Card{suit: Suit::Heart, face: Face::Ace});
    }
}

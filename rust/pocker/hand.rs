use itertools::Itertools;
use std::cmp::Ordering;
use std::fmt;
use std::str::FromStr;

#[derive(Debug, Clone)]
pub struct PockerCardParseError;

impl fmt::Display for PockerCardParseError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Could not parse Suit")
    }
}

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub enum Suit {
    Heart,
    Tile,
    Clover,
    Pike,
}

impl FromStr for Suit {
    type Err = PockerCardParseError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "H" => Ok(Suit::Heart),
            "S" => Ok(Suit::Pike),
            "P" => Ok(Suit::Pike),
            "D" => Ok(Suit::Tile),
            "T" => Ok(Suit::Tile),
            "C" => Ok(Suit::Clover),
            _ => Err(PockerCardParseError),
        }
    }
}

#[derive(Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Clone, Copy)]
pub enum Face {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
}

impl Face {
    fn next(&self) -> Option<Face> {
        match self {
            Face::Two => Some(Face::Three),
            Face::Three => Some(Face::Four),
            Face::Four => Some(Face::Five),
            Face::Five => Some(Face::Six),
            Face::Six => Some(Face::Seven),
            Face::Seven => Some(Face::Eight),
            Face::Eight => Some(Face::Nine),
            Face::Nine => Some(Face::Ten),
            Face::Ten => Some(Face::Jack),
            Face::Jack => Some(Face::Queen),
            Face::Queen => Some(Face::King),
            Face::King => Some(Face::Ace),
            Face::Ace => None,
        }
    }
}

impl FromStr for Face {
    type Err = PockerCardParseError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "2" => Ok(Face::Two),
            "3" => Ok(Face::Three),
            "4" => Ok(Face::Four),
            "5" => Ok(Face::Five),
            "6" => Ok(Face::Six),
            "7" => Ok(Face::Seven),
            "8" => Ok(Face::Eight),
            "9" => Ok(Face::Nine),
            "T" => Ok(Face::Ten),
            "J" => Ok(Face::Jack),
            "Q" => Ok(Face::Queen),
            "K" => Ok(Face::King),
            "A" => Ok(Face::Ace),
            _ => Err(PockerCardParseError),
        }
    }
}

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub struct Card {
    pub suit: Suit,
    pub face: Face,
}

impl Ord for Card {
    fn cmp(&self, other: &Self) -> Ordering {
        self.face.cmp(&other.face)
    }
}

impl PartialOrd for Card {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl FromStr for Card {
    type Err = PockerCardParseError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let (face_string, suit_string) = s.split_at(1);
        let suit = suit_string.parse::<Suit>()?;
        let face = face_string.parse::<Face>()?;

        Ok(Card {
            suit: suit,
            face: face,
        })
    }
}

#[derive(Debug)]
pub struct Hand {
    cards: [Card; 5],
}
impl Hand {
    pub fn new(one: Card, two: Card, three: Card, four: Card, five: Card) -> Self {
        let mut cards = [one, two, three, four, five];
        cards.sort();
        Self { cards: cards }
    }
}

impl PartialEq for Hand {
    fn eq(&self, other: &Self) -> bool {
        self.cards == other.cards
    }
}

fn is_straight(hand: &Hand) -> bool {
    let mut is_straight = true;
    for i in 0..4 {
        match hand.cards[i].face.next() {
            Some(value) => is_straight |= value == hand.cards[i + 1].face,
            None => is_straight |= false,
        };
    }
    is_straight
}

struct FullHouse {
    face_with_count: [(Face, i8); 2],
}
fn create_full_house(hand: &Hand) -> Option<FullHouse> {
    let face_values = hand.cards.map(|card| card.face);
    let face_with_count = face_values.iter().unique().map(|unique_value| {
        (
            *unique_value,
            face_values
                .iter()
                .filter(|value| *value == unique_value)
                .count() as i8,
        )
    });

    let vec = face_with_count.collect_vec();
    if vec.len() == 2 && (vec[0].1 == 2 || vec[0].1 == 3) && (vec[1].1 == 3 || vec[1].1 == 2) {
        let mut face_with_count_array = [vec[0], vec[1]];
        face_with_count_array.sort_by(|lhs, rhs| lhs.0.partial_cmp(&rhs.0).unwrap());
        Some(FullHouse {
            face_with_count: face_with_count_array,
        })
    } else {
        None
    }
}

impl PartialOrd for Hand {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        let flush_lhs = self.cards.iter().all(|x| x.suit == self.cards[0].suit);
        let flush_rhs = other.cards.iter().all(|x| x.suit == other.cards[0].suit);
        if !create_full_house(self).is_none() && create_full_house(other).is_none() {
            return Some(Ordering::Greater);
        } else if !create_full_house(other).is_none() && create_full_house(self).is_none() {
            return Some(Ordering::Less);
        } else if !create_full_house(other).is_none() && !create_full_house(self).is_none() {
            let lhs = create_full_house(self).unwrap();
            let rhs = create_full_house(other).unwrap();
            if lhs.face_with_count[1]
                .0
                .partial_cmp(&rhs.face_with_count[1].0)
                .unwrap()
                != Ordering::Equal
            {
                return lhs.face_with_count[1]
                    .0
                    .partial_cmp(&rhs.face_with_count[1].0);
            } else {
                return lhs.face_with_count[0]
                    .0
                    .partial_cmp(&rhs.face_with_count[0].0);
            }
        } else if is_straight(self) && !is_straight(other) {
            return Some(Ordering::Greater);
        } else if is_straight(other) && !is_straight(self) {
            return Some(Ordering::Less);
        } else if flush_lhs && !flush_rhs {
            return Some(Ordering::Greater);
        } else if flush_rhs && !flush_lhs {
            return Some(Ordering::Less);
        }
        Some(self.cards.cmp(&other.cards))
    }
}

impl FromStr for Hand {
    type Err = PockerCardParseError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let one = Card::from_str(&s[0..2])?;
        let two = Card::from_str(&s[3..5])?;
        let three = Card::from_str(&s[6..8])?;
        let four = Card::from_str(&s[9..11])?;
        let five = Card::from_str(&s[12..14])?;
        Ok(Hand::new(one, two, three, four, five))
    }
}

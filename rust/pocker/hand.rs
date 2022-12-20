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
            Face::Ace => Some(Face::Two),
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
        println!("Before: {:?}", hand.cards[i].face);
        match hand.cards[i].face.next() {
            Some(value) => {
                let tmp = value == hand.cards[i + 1].face;
                println!("Tmp: {} {:?} {:?}", tmp, value, hand.cards[i + 1].face);
                is_straight = is_straight && tmp;
            }
            None => {
                is_straight = is_straight && false;
            }
        };
    }
    is_straight
}

#[derive(PartialEq, Eq, PartialOrd)]
enum Rank {
    HighCard,
    OnePair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
}

#[derive(PartialEq, Eq, PartialOrd)]
struct Score {
    rank: Rank,
    face_values_decreasing_order: Vec<Face>,
}

fn create_highest_score(hand: &Hand) -> Score {
    let is_flush = hand.cards.iter().all(|x| x.suit == hand.cards[0].suit);
    let is_straight = is_straight(hand);

    let face_values_decreasing_order = hand.cards.map(|card| card.face);

    if is_flush && is_straight {
        return Score {
            rank: Rank::StraightFlush,
            face_values_decreasing_order: face_values_decreasing_order.to_vec(),
        };
    }

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

    let mut vec = face_with_count.collect_vec();
    vec.sort_by(|lhs, rhs| rhs.1.partial_cmp(&lhs.1).unwrap());

    if (vec.len() == 2) && (vec[0].1 == 4) {
        return Score {
            rank: Rank::FourOfAKind,
            face_values_decreasing_order: [vec[0].0, vec[1].0].to_vec(),
        };
    }
    if (vec.len() == 2) && (vec[0].1 == 3) && (vec[1].1 == 2) {
        return Score {
            rank: Rank::FullHouse,
            face_values_decreasing_order: [vec[0].0, vec[1].0].to_vec(),
        };
    }

    if is_straight {
        return Score {
            rank: Rank::Straight,
            face_values_decreasing_order: face_values_decreasing_order.to_vec(),
        };
    }

    if is_flush {
        println!("Created Flush");
        return Score {
            rank: Rank::Flush,
            face_values_decreasing_order: face_values_decreasing_order.to_vec(),
        };
    }
    return Score {
        rank: Rank::HighCard,
        face_values_decreasing_order: face_values_decreasing_order.to_vec(),
    };
}

impl PartialOrd for Hand {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        let self_score = create_highest_score(self);
        let other_score = create_highest_score(other);

        println!("FooBar");
        self_score.partial_cmp(&other_score)
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

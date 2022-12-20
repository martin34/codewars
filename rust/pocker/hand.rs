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

fn create_straight(hand: &Hand) -> Option<[Face; 5]> {
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
    if is_straight {
        Some(hand.cards.map(|card| card.face))
    } else {
        None
    }
}

#[derive(PartialEq, Eq)]
enum Score {
    HighCard,
    OnePair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse {
        face_with_count: [(Face, i8); 2],
    },
    FourOfAKind,
    StraightFlush {
        face_values_decreasing_order: [Face; 5],
    },
}

fn create_highest_score(hand: &Hand) -> Score {
    let is_flush = hand.cards.iter().all(|x| x.suit == hand.cards[0].suit);
    let straight = create_straight(hand);
    if is_flush {
        if let Some(face_values) = straight {
            return Score::StraightFlush {
                face_values_decreasing_order: face_values,
            };
        }
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
    vec.sort_by(|lhs, rhs| lhs.1.partial_cmp(&rhs.1).unwrap());

    if vec.len() == 2 && (vec[0].1 == 4 || vec[1].1 == 4) {
        return Score::FourOfAKind;
    }
    if vec.len() == 2 && (vec[0].1 == 2 || vec[0].1 == 3) && (vec[1].1 == 3 || vec[1].1 == 2) {
        let face_with_count_array = [vec[0], vec[1]];
        return Score::FullHouse {
            face_with_count: face_with_count_array,
        };
    }

    if let Some(face_values) = straight {
        println!("Created Straight");
        return Score::Straight;
    }

    if is_flush {
        println!("Created Flush");
        return Score::Flush;
    }
    println!("Created HighCard");
    return Score::HighCard;
}

fn create_numeric_score(score: &Score) -> i8 {
    match score {
        Score::HighCard => 0,
        Score::OnePair => 1,
        Score::TwoPairs => 2,
        Score::ThreeOfAKind => 3,
        Score::Straight => 4,
        Score::Flush => 5,
        Score::FullHouse { .. } => 6,
        Score::FourOfAKind => 7,
        Score::StraightFlush { .. } => 8,
    }
}

impl PartialOrd for Score {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        let ns = create_numeric_score(self);
        let ons = create_numeric_score(other);
        let nsc = ns.partial_cmp(&ons);
        if nsc != Some(Ordering::Equal) {
            println!("Simple {} {}", ns, ons);
            return nsc;
        }

        if let Score::StraightFlush {
            face_values_decreasing_order,
        } = self
        {
            let self_face_values_decreasing_order = face_values_decreasing_order;
            if let Score::StraightFlush {
                face_values_decreasing_order,
            } = other
            {
                return Some(self_face_values_decreasing_order.cmp(&face_values_decreasing_order));
            }
        }

        println!("Blub");
        match self {
            Score::FullHouse { face_with_count } => {
                let self_face_with_count = face_with_count;
                println!("Found 1 full house");
                match other {
                    Score::FullHouse { face_with_count } => {
                        println!("Found 2 full house");
                        let other_face_with_count = face_with_count;
                        let high_card_ordering =
                            self_face_with_count[0].0.cmp(&other_face_with_count[0].0);
                        if high_card_ordering == Ordering::Equal {
                            return Some(high_card_ordering);
                        }
                        return Some(self_face_with_count[1].0.cmp(&other_face_with_count[1].0));
                    }
                    _ => Some(Ordering::Greater),
                }
            }
            _ => None,
        }
    }
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

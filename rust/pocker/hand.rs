use std::fmt;
use std::str::FromStr;
use std::cmp::Ordering;

#[derive(Debug, Clone)]
pub struct PockerCardParseError;

impl fmt::Display for PockerCardParseError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Could not parse Suit")
    }
}

#[derive(Debug, PartialEq, Eq)]
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

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord)]
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

#[derive(Debug, PartialEq, Eq)]
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
pub struct Hand{
    pub cards: [Card; 5]
}

impl PartialEq for Hand {
    fn eq(&self, other: &Self) -> bool {
        self.cards == other.cards
    }
}

impl PartialOrd for Hand {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        let flush_lhs = self.cards.iter().all(|x| x.suit == self.cards[0].suit);
        let flush_rhs = other.cards.iter().all(|x| x.suit == other.cards[0].suit);
        if flush_lhs && !flush_rhs
        {
            return Some(Ordering::Greater)
        }
        else if flush_rhs && !flush_lhs
        {
            return Some(Ordering::Less)
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
        Ok(Hand{cards: [one, two, three, four, five]})
    }
}

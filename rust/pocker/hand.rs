use std::str::FromStr;
use std::fmt;

#[derive(Debug, Clone)]
pub struct PockerCardParseError;

impl fmt::Display for PockerCardParseError{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Could not parse Suit")
    }
}

#[derive(Debug)]
#[derive(PartialEq)]
pub enum Suit{
    Heart, Tile, Clover, Pike
}


impl FromStr for Suit {
    type Err = PockerCardParseError;

    fn from_str(s: &str) -> Result<Self, Self::Err>{
        match s{
            "H" => Ok(Suit::Heart),
            "P" => Ok(Suit::Pike),
            "T" => Ok(Suit::Tile),
            "C" => Ok(Suit::Clover),
            _ => Err(PockerCardParseError),
        }
    }
}

#[derive(Debug)]
#[derive(PartialEq)]
pub enum Face{
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
  Ace
}

#[derive(Debug)]
#[derive(PartialEq)]
pub struct Card
{
    pub suit : Suit,
    pub face : Face,
}

impl FromStr for Card {
    type Err = PockerCardParseError;

    fn from_str(s: &str) -> Result<Self, Self::Err>{
        let (face_string, suit_string) = s.split_at(1);
        let suit = suit_string.parse::<Suit>()?;

        Ok(Card{suit: suit, face: Face::Ace})
    }
}

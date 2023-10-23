#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"
using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
        "Two",   // TWO
        "Three", // THREE
        "Four",  // FOUR
        "Five",  // FIVE
        "Six",   // SIX
        "Seven", // SEVEN
        "Eight", // EIGHT
        "Nine",  // NINE
        "Ten",   // TEN
        "Jack",  // JACK
        "Queen", // QUEEN
        "King",  // KING
        "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
    for (int r = TWO; r <= ACE; ++r) {
        if (str == RANK_NAMES[r]) {
            return static_cast<Rank>(r);
        }
    }
    assert(false); // Input string didn't match any rank
    return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream &operator<<(std::ostream &os, Rank rank) {
    os << RANK_NAMES[rank];
    return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream &operator>>(std::istream &is, Rank &rank) {
    string str;
    if (is >> str) {
        rank = string_to_rank(str);
    }
    return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
        "Spades",   // SPADES
        "Hearts",   // HEARTS
        "Clubs",    // CLUBS
        "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        if (str == SUIT_NAMES[s]) {
            return static_cast<Suit>(s);
        }
    }
    assert(false); // Input string didn't match any suit
    return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream &operator<<(std::ostream &os, Suit suit) {
    os << SUIT_NAMES[suit];
    return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream &operator>>(std::istream &is, Suit &suit) {
    string str;
    if (is >> str) {
        suit = string_to_suit(str);
    }
    return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

Card::Card() : Card(TWO, SPADES) {}

Card::Card(Rank rank_in, Suit suit_in) {
    this->rank = rank_in;
    this->suit = suit_in;
}

Rank Card::get_rank() const {
    return rank;
}

Suit Card::get_suit() const {
    return suit;
}

// TODO a little extra testing (done)
Suit Card::get_suit(Suit trump) const {
    return is_left_bower(trump) ? trump : suit;
}

bool Card::is_face_or_ace() const {
    return rank > TEN;
}

bool Card::is_right_bower(Suit trump) const {
    return suit == trump && rank == JACK;
}

bool Card::is_left_bower(Suit trump) const {
    return suit == Suit_next(trump) && rank == JACK;
}

bool Card::is_trump(Suit trump) const {
    return get_suit(trump) == trump;
}

std::istream &operator>>(istream &is, Card &card) {
    is >> card.rank;
    std::string of_check;
    is >> of_check;
    assert(of_check == "of");
    is >> card.suit;
    return is;
}

std::ostream &operator<<(ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

static int get_value(const Card &card) {
    return card.get_rank() * 4 + card.get_suit();
}

bool operator<(const Card &lhs, const Card &rhs) {
    return get_value(lhs) < get_value(rhs);
}

bool operator<=(const Card &lhs, const Card &rhs) {
    return get_value(lhs) <= get_value(rhs);
}

bool operator>(const Card &lhs, const Card &rhs) {
    return get_value(lhs) > get_value(rhs);
}

bool operator>=(const Card &lhs, const Card &rhs) {
    return get_value(lhs) >= get_value(rhs);
}

bool operator==(const Card &lhs, const Card &rhs) {
    return get_value(lhs) == get_value(rhs);
}

bool operator!=(const Card &lhs, const Card &rhs) {
    return get_value(lhs) != get_value(rhs);
}

Suit Suit_next(Suit suit) {
    return static_cast<Suit>((suit + 2) % 4);
}

static int get_adjusted_value(const Card &card, const Suit &trump, const Suit
&led) {
    return card.is_right_bower(trump)
           ? 79
           : card.is_left_bower(trump)
             ? 78
             : card.is_trump(trump)
               ? 65 + card.get_rank()
               : card.get_suit() == led
                 ? 52 + card.get_rank()
                 : get_value(card);
}

static int get_adjusted_value(const Card &card, const Suit &trump) {
    return get_adjusted_value(card, trump, trump);
}

bool Card_less(const Card &a, const Card &b, Suit trump) {
    return get_adjusted_value(a, trump) < get_adjusted_value(b, trump);
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump) {
    return get_adjusted_value(a, trump, led_card.get_suit()) <
           get_adjusted_value(b, trump, led_card.get_suit());
}

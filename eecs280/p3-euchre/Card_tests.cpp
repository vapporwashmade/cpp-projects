#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here

TEST(test_face_ace) {
    Card face(JACK, DIAMONDS);
    Card ace(ACE, SPADES);
    ASSERT_TRUE(face.is_face_or_ace())
    ASSERT_TRUE(ace.is_face_or_ace())
    ASSERT_FALSE(Card(TEN, CLUBS).is_face_or_ace())
}

TEST(test_bower) {
    Card jspades(JACK, SPADES);
    Card jdiamonds(JACK, DIAMONDS);

    // j of spade
    ASSERT_EQUAL(jspades.is_right_bower(SPADES), true)
    ASSERT_EQUAL(jspades.is_left_bower(SPADES), false)
    ASSERT_EQUAL(jspades.is_trump(SPADES), true)

    ASSERT_EQUAL(jspades.is_right_bower(CLUBS), false)
    ASSERT_EQUAL(jspades.is_left_bower(CLUBS), true)
    ASSERT_EQUAL(jspades.is_trump(CLUBS), true)
    ASSERT_EQUAL(jspades.get_suit(), SPADES)

    ASSERT_EQUAL(jspades.is_right_bower(DIAMONDS), false)
    ASSERT_EQUAL(jspades.is_left_bower(DIAMONDS), false)
    ASSERT_EQUAL(jspades.is_trump(DIAMONDS), false)

    // j of diamond
    ASSERT_EQUAL(jdiamonds.is_right_bower(DIAMONDS), true)
    ASSERT_EQUAL(jdiamonds.is_left_bower(DIAMONDS), false)
    ASSERT_EQUAL(jdiamonds.is_trump(DIAMONDS), true)

    ASSERT_EQUAL(jdiamonds.is_right_bower(HEARTS), false)
    ASSERT_EQUAL(jdiamonds.is_left_bower(HEARTS), true)
    ASSERT_EQUAL(jdiamonds.is_trump(HEARTS), true)
    ASSERT_EQUAL(jdiamonds.get_suit(), DIAMONDS)

    ASSERT_EQUAL(jdiamonds.is_right_bower(CLUBS), false)
    ASSERT_EQUAL(jdiamonds.is_left_bower(CLUBS), false)
    ASSERT_EQUAL(jdiamonds.is_trump(CLUBS), false)
}

TEST(test_basic_trump) {
    Card c(ACE, DIAMONDS);
    ASSERT_TRUE(c.is_trump(DIAMONDS))
    ASSERT_FALSE(c.is_trump(SPADES))
    ASSERT_FALSE(c.is_trump(CLUBS))
    ASSERT_FALSE(c.is_trump(HEARTS))
}

TEST(test_getsuit_trump) {
    Card bower(JACK, CLUBS);
    Card c(KING, DIAMONDS);

    // first test other color suit, then same suit, then next suit
    // if it is not a bower, should be its own suit for all three
    // if it is a bower, should be its own suit for 1 and 2, but trump for 3
    ASSERT_EQUAL(c.get_suit(SPADES), DIAMONDS)
    ASSERT_EQUAL(c.get_suit(DIAMONDS), DIAMONDS)
    ASSERT_EQUAL(c.get_suit(HEARTS), DIAMONDS)

    ASSERT_EQUAL(bower.get_suit(HEARTS), CLUBS)
    ASSERT_EQUAL(bower.get_suit(CLUBS), CLUBS)
    ASSERT_EQUAL(bower.get_suit(SPADES), SPADES)
}

TEST(test_suit_next) {
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS)
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS)
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES)
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS)
}

TEST(test_basic_relational_operators) {
    Card j1(JACK, DIAMONDS);
    Card j2(JACK, SPADES);

    ASSERT_FALSE(j1 < j2)
    ASSERT_TRUE(j1 > j2)
    ASSERT_FALSE(j1 <= j2)
    ASSERT_TRUE(j1 >= j2)
}

TEST(test_basic_equality_operators) {
    Card j1(JACK, CLUBS);
    Card j2(JACK, HEARTS);

    Card sp1(TWO, SPADES);
    Card sp2(THREE, SPADES);

    ASSERT_FALSE(j1 == j2)
    ASSERT_TRUE(j1 != j2)

    ASSERT_FALSE(sp1 == sp2)
    ASSERT_TRUE(sp1 != sp2)

    // for completion
    ASSERT_TRUE(j1 == j1)
    ASSERT_TRUE(j2 == j2)
    ASSERT_FALSE(j1 != j1)
    ASSERT_FALSE(j2 != j2)

    ASSERT_TRUE(sp1 == sp1)
    ASSERT_TRUE(sp2 == sp2)
    ASSERT_FALSE(sp1 != sp1)
    ASSERT_FALSE(sp2 != sp2)
}

TEST(test_ostream_operator) {
    ostringstream out;

    out << Card();
    ASSERT_EQUAL(out.str(), "Two of Spades")
    out.str("");
    out.clear();

    out << Card(JACK, DIAMONDS);
    ASSERT_EQUAL(out.str(), "Jack of Diamonds")
    out.str("");
    out.clear();

    out << Card(JACK, HEARTS);
    ASSERT_EQUAL(out.str(), "Jack of Hearts")
    out.str("");
    out.clear();

    out << Card(ACE, CLUBS);
    ASSERT_EQUAL(out.str(), "Ace of Clubs")
}

TEST(test_card_less) {
    Card b1(JACK, CLUBS);
    Card b2(JACK, SPADES);
    Card t1(ACE, SPADES);
    Card t2(TWO, SPADES);
    Card l2(TWO, HEARTS);
    Card l1(ACE, DIAMONDS);

    ASSERT_EQUAL(Card_less(t1, b1, SPADES), true)
    ASSERT_EQUAL(Card_less(t1, b2, SPADES), true)
    ASSERT_EQUAL(Card_less(b2, b1, SPADES), false)
    ASSERT_TRUE(Card_less(l1, t2, SPADES))

    ASSERT_TRUE(Card_less(l1, l2, l2, SPADES))
    ASSERT_FALSE(Card_less(t2, l2, l2, SPADES))
}

TEST(test_card_less_2) {
    Card c2(JACK, DIAMONDS);
    Card c3(ACE, HEARTS);
    Suit trump = HEARTS;

    ASSERT_TRUE(Card_less(c3, c2, c2, trump))
    ASSERT_TRUE(Card_less(c3, c2, c3, trump))
}

TEST_MAIN()

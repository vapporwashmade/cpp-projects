#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player *alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

TEST(test_single_card) {
    Player *p = Player_factory("foo", "Simple");

    p->add_card(Card(NINE, DIAMONDS));
    Card c = p->lead_card(CLUBS);
    ASSERT_EQUAL(c, Card(NINE, DIAMONDS))

    p->add_card(Card(JACK, HEARTS));
    c = p->lead_card(HEARTS);
    ASSERT_EQUAL(c, Card(JACK, HEARTS))

    p->add_card(Card(ACE, SPADES));
    c = p->play_card(Card(), SPADES);
    ASSERT_EQUAL(c, Card(ACE, SPADES))

    p->add_card(Card(TEN, CLUBS));
    c = p->play_card(Card(), DIAMONDS);
    ASSERT_EQUAL(c, Card(TEN, CLUBS))

    delete p;
}

TEST(test_make_trump_r1_nd) {
    Player *p = Player_factory("foo", "Simple");

    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(JACK, DIAMONDS));
    p->add_card(Card(JACK, CLUBS));

    Suit trump;
    ASSERT_EQUAL(p->make_trump(Card(KING, SPADES), false, 1, trump), false);

    ASSERT_EQUAL(p->make_trump(Card(ACE, CLUBS), false, 1, trump), false);

    ASSERT_EQUAL(p->make_trump(Card(TEN, HEARTS), false, 1, trump), true);
    ASSERT_EQUAL(trump, HEARTS)

    ASSERT_EQUAL(p->make_trump(Card(QUEEN, DIAMONDS), false, 1, trump), false);
    ASSERT_EQUAL(trump, HEARTS)
    delete p;
}

TEST(test_make_trump_r1_d) {
    Player *p = Player_factory("bar", "Simple");

    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(JACK, SPADES));

    Suit trump;
    ASSERT_EQUAL(p->make_trump(Card(KING, SPADES), true, 1, trump), true);
    ASSERT_EQUAL(trump, SPADES)

    ASSERT_EQUAL(p->make_trump(Card(ACE, CLUBS), true, 1, trump), false);
    ASSERT_EQUAL(trump, SPADES)

    ASSERT_EQUAL(p->make_trump(Card(TEN, HEARTS), true, 1, trump), false);
    ASSERT_EQUAL(trump, SPADES)

    ASSERT_EQUAL(p->make_trump(Card(QUEEN, DIAMONDS), true, 1, trump), false);
    ASSERT_EQUAL(trump, SPADES)
    delete p;
}

TEST(test_make_trump_r2_nd) {
    Player *p = Player_factory("foo", "Simple");

    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(JACK, DIAMONDS));
    p->add_card(Card(JACK, CLUBS));

    Suit trump;
    ASSERT_EQUAL(p->make_trump(Card(KING, SPADES), false, 2, trump), true);
    ASSERT_EQUAL(trump, CLUBS)

    ASSERT_EQUAL(p->make_trump(Card(ACE, CLUBS), false, 2, trump), true);
    ASSERT_EQUAL(trump, SPADES)

    ASSERT_EQUAL(p->make_trump(Card(TEN, HEARTS), false, 2, trump), true);
    ASSERT_EQUAL(trump, DIAMONDS)

    ASSERT_EQUAL(p->make_trump(Card(QUEEN, DIAMONDS), false, 2, trump), true);
    ASSERT_EQUAL(trump, HEARTS)

    delete p;
    Player *p2 = Player_factory("bar", "Simple");

    p2->add_card(Card(ACE, HEARTS));
    p2->add_card(Card(NINE, HEARTS));
    p2->add_card(Card(TEN, SPADES));
    p2->add_card(Card(JACK, DIAMONDS));
    p2->add_card(Card(KING, CLUBS));

    ASSERT_EQUAL(p2->make_trump(Card(QUEEN, CLUBS), false, 2, trump), false)
    ASSERT_EQUAL(trump, HEARTS)

    ASSERT_EQUAL(p2->make_trump(Card(ACE, SPADES), false, 2, trump), true)
    ASSERT_EQUAL(trump, CLUBS)

    delete p2;
}

TEST(test_make_trump_r2_d) {
    Player *p = Player_factory("bar", "Simple");

    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(JACK, SPADES));

    Suit trump;
    ASSERT_EQUAL(p->make_trump(Card(KING, SPADES), true, 2, trump), true);
    ASSERT_EQUAL(trump, CLUBS)

    ASSERT_EQUAL(p->make_trump(Card(ACE, CLUBS), true, 2, trump), true);
    ASSERT_EQUAL(trump, SPADES)

    ASSERT_EQUAL(p->make_trump(Card(TEN, HEARTS), true, 2, trump), true);
    ASSERT_EQUAL(trump, DIAMONDS)

    ASSERT_EQUAL(p->make_trump(Card(QUEEN, DIAMONDS), true, 2, trump), true);
    ASSERT_EQUAL(trump, HEARTS)

    delete p;
}

TEST(test_add_discard_1) {
    Player *p = Player_factory("bar", "Simple");

    p->add_card(Card(ACE, DIAMONDS));
    p->add_card(Card(QUEEN, DIAMONDS));
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(KING, DIAMONDS));

    p->add_and_discard(Card(NINE, DIAMONDS));

    ASSERT_EQUAL(p->play_card(Card(JACK, DIAMONDS), CLUBS), Card(ACE,
                                                                 DIAMONDS));

    delete p;
}

TEST(test_add_discard_2) {
    Player *p = Player_factory("foo", "Simple");

    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(JACK, CLUBS));
    p->add_card(Card(ACE, DIAMONDS));

    p->add_and_discard(Card(TEN, SPADES));
    ASSERT_EQUAL(p->play_card(Card(TEN, HEARTS), SPADES), Card(ACE, DIAMONDS))

    delete p;
}

TEST(test_lead_card_1) {
    Player *p = Player_factory("foo", "Simple");

    p->add_card(Card(QUEEN, SPADES));
    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(JACK, CLUBS));
    p->add_card(Card(ACE, SPADES));

    ASSERT_EQUAL(p->lead_card(SPADES), Card(JACK, CLUBS))

    delete p;
}

TEST(test_lead_card_2) {
    Player *p = Player_factory("bar", "Simple");

    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(JACK, SPADES));
    p->add_card(Card(NINE, DIAMONDS));

    p->add_and_discard(Card(TEN, SPADES));
    ASSERT_EQUAL(p->lead_card(CLUBS), Card(TEN, HEARTS))

    delete p;
}

TEST(test_confirm_card_removal) {
    Player *p = Player_factory("bar", "Simple");

    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(JACK, SPADES));
    p->add_card(Card(NINE, DIAMONDS));

    ASSERT_NOT_EQUAL(p->lead_card(CLUBS), p->lead_card(CLUBS))
    ASSERT_NOT_EQUAL(p->play_card(Card(TEN, SPADES), SPADES),
                     p->play_card(Card(QUEEN, DIAMONDS), HEARTS))

    delete p;
}

TEST(test_play_card) {
    Player *p = Player_factory("bar", "Simple");

    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(JACK, SPADES));
    p->add_card(Card(NINE, DIAMONDS));

    ASSERT_EQUAL(p->play_card(Card(QUEEN, CLUBS), CLUBS), Card(JACK, SPADES));

    delete p;
}

TEST(test_play_card_2) {
    Player *p = Player_factory("foo", "Simple");

    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(KING, HEARTS));
    p->add_card(Card(JACK, SPADES));
    p->add_card(Card(ACE, DIAMONDS));

    ASSERT_EQUAL(p->play_card(Card(QUEEN, CLUBS), CLUBS), Card(JACK, SPADES));

    delete p;
}

TEST(test_play_card_3) {
    Player *p = Player_factory("bar", "Simple");

    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(KING, HEARTS));
    p->add_card(Card(JACK, HEARTS));
    p->add_card(Card(QUEEN, HEARTS));

    ASSERT_EQUAL(p->play_card(Card(TEN, HEARTS), HEARTS), Card(JACK, HEARTS));

    delete p;
}

TEST_MAIN()

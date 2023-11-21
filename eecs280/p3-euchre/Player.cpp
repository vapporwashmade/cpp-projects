//
// Created by apoorv on 10/10/2023.
//

#include <cassert>
#include <algorithm>
#include "Player.hpp"

class SimplePlayer : public Player {
public:
    SimplePlayer(const std::string &name) {
        this->name = name;
    }

//TODO add only if failed mutation testing
    const std::string &get_name() const override {
        return name;
    }

    void add_card(const Card &c) override {
        hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer, int round,
                    Suit &order_up_suit) const override {
        if (round == 1) {
            int high_card_count = 0;
            for (int i = 0; i < hand.size(); ++i) {
                if (hand[i].is_face_or_ace() && hand[i].is_trump
                        (upcard.get_suit())) {
                    ++high_card_count;
                }
            }
            if (high_card_count >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            return false;
        }
        Suit potential_trump = Suit_next(upcard.get_suit());
        if (is_dealer) {
            order_up_suit = potential_trump;
            return true;
        }
        bool faceCard = false;
        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i].is_face_or_ace() &&
                hand[i].is_trump(potential_trump)) {
                faceCard = true;
            }
        }
        if (faceCard) {
            order_up_suit = potential_trump;
            return true;
        }
        return false;
    }

    void add_and_discard(const Card &upcard) override {
        add_card(upcard);
        int min_i = 0;
        for (int i = 1; i < hand.size(); ++i) {
            if (Card_less(hand[i], hand[min_i], upcard.get_suit())) {
                min_i = i;
            }
        }
        hand.erase(hand.begin() + min_i);
    }

    // TODO test further (beware of private tests)
    // TODO test forgetting to remove card for both lead and play card
    Card lead_card(Suit trump) override {
        int highest_nontrump_i = -1;
        int highest_trump_i = -1;
        bool all_trump = true;
        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i].is_trump(trump)) {
                if (highest_trump_i < 0) {
                    highest_trump_i = i;
                } else if (Card_less(hand[highest_trump_i], hand[i], trump)) {
                    highest_trump_i = i;
                }
            } else {
                if (highest_nontrump_i < 0) {
                    all_trump = false;
                    highest_nontrump_i = i;
                } else if (hand[highest_nontrump_i] < hand[i]) {
                    highest_nontrump_i = i;
                }
            }
        }
        return all_trump ? remove(highest_trump_i) : remove(highest_nontrump_i);
    }

    // TODO test further (beware of private tests)
    Card play_card(const Card &led_card, Suit trump) override {
        int highest_led_i = -1;
        int lowest_card_i = -1;
        bool has_led_suit = false;
        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i].get_suit(trump) == led_card.get_suit(trump)) {
                if (highest_led_i < 0) {
                    has_led_suit = true;
                    highest_led_i = i;
                } else if (Card_less(hand[highest_led_i], hand[i], trump)) {
                    highest_led_i = i;
                }
            } else {
                if (lowest_card_i < 0) {
                    lowest_card_i = i;
                } else if (Card_less(hand[i], hand[lowest_card_i], trump)) {
                    lowest_card_i = i;
                }
            }
        }
        return has_led_suit ? remove(highest_led_i) : remove(lowest_card_i);
    }

private:
    std::string name;
    std::vector<Card> hand;

    Card remove(int index) {
        Card removed = hand[index];
        hand.erase(hand.begin() + index);
        return removed;
    }
};

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string &name) {
        this->name = name;
    }

    const std::string &get_name() const override {
        return name;
    }

    void add_card(const Card &c) override {
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }

    bool make_trump(const Card &upcard, bool is_dealer, int round,
                    Suit &order_up_suit) const override {
        print_hand(std::cout);
        prompt(std::cout);

        std::string decision;
        std::cin >> decision;

        if (decision == "pass") {
            return false;
        }
        order_up_suit = string_to_suit(decision);
        return true;
    }

    void add_and_discard(const Card &upcard) override {
        ask_discard(std::cout);
        int discard_i;
        std::cin >> discard_i;

        if (discard_i < -1 || discard_i >= hand.size()) {
            assert(false);
        }
        if (discard_i == -1) {
            return;
        }
        hand.erase(hand.begin() + discard_i);
        add_card(upcard);
    }

    // TODO test forgetting to remove card for both lead and play card
    Card lead_card(Suit trump) override {
        print_hand(std::cout);
        std::cout << "Human player " << name << ", please select a card:\n";
        int card_i;
        std::cin >> card_i;

        assert(0 <= card_i && card_i < hand.size());

        return remove(card_i);
    }

    Card play_card(const Card &led_card, Suit trump) override {
        return lead_card(trump);
    }

private:
    std::string name;
    std::vector<Card> hand;

    void print_hand(std::ostream &os) const {
        for (int i = 0; i < hand.size(); ++i) {
            os << "Human player " << name << "'s hand: "
               << "[" << i << "] " << hand[i] << '\n';
        }
    }

    void prompt(std::ostream &os) const {
        os << "Human player " << name
           << ", please enter a suit, or \"pass\":\n";
    }

    void ask_discard(std::ostream &os) const {
        print_hand(os);
        os << "Discard upcard: [-1]\n";
        os << "Human player " << name << ", please select a card to discard:\n";
    }

    Card remove(int index) {
        Card removed = hand[index];
        hand.erase(hand.begin() + index);
        return removed;
    }
};

Player *Player_factory(const std::string &name, const std::string &strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }
    if (strategy == "Human") {
        return new HumanPlayer(name);
    }
    assert(false);
    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}
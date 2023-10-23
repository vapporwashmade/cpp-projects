//
// Created by apoorv on 10/2/2023.
//
#include "Pack.hpp"

Pack::Pack() {
    for (int i = 0; i <= DIAMONDS; ++i) {
        for (int j = 0; j <= ACE - NINE; ++j) {
            this->cards.at(6 * i + j) = Card{static_cast<Rank>(j + 7),
                                             static_cast<Suit>(i)};
        }
    }
    this->next = 0;
}

Pack::Pack(std::istream &pack_input) {
    for (int i = 0; i < PACK_SIZE; ++i) {
        pack_input >> this->cards.at(i);
    }
    next = 0;
}

Card Pack::deal_one() {
    next++;
    return cards[next - 1];
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    int order[PACK_SIZE]{};
    for (int i = 0; i < PACK_SIZE; ++i) {
        order[i] = i;
    }
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < PACK_SIZE; ++j) {
            order[j] = ((2 * (order[j] + 1)) % 25) - 1;
        }
    }
    std::array<Card, PACK_SIZE> newOrder;
    for (int i = 0; i < PACK_SIZE; ++i) {
        newOrder[order[i]] = cards[i];
    }
    cards = newOrder;
    reset();
}

bool Pack::empty() const {
    return next >= PACK_SIZE;
}

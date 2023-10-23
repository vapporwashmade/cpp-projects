#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cstring>
#include "Player.hpp"
#include "Pack.hpp"

static void argerror();

class Game {
public:
    Game(std::istream &pack_stream, const std::string &shuffling, int points,
         const std::string &name1, const std::string &type1,
         const std::string &name2, const std::string &type2,
         const std::string &name3, const std::string &type3,
         const std::string &name4, const std::string &type4);

    void play();

private:
    std::vector<Player *> players;
    Pack pack;

    Card upcard;
    const bool do_shuffle;
    const bool pts_to_win;
    int dealer = 0;
    int team1pts = 0;
    int team2pts = 0;

    void shuffle();

    void deal();

    void hand(int hand);

    void score(const int &ordered_up_tricks, int &ou_pts, int &non_ou_pts,
               const int &ou_team);

    int make_trump(Suit &trump);

    int trick(int leader, Suit trump);
};

int main(int argc, char **argv) {
    // argument checks
    if (argc != 12) {
        argerror();
        return 1;
    }
    int pts = std::stoi(argv[3]);
    if (0 >= pts || pts > 100) {
        argerror();
        return 1;
    }
    if (std::strcmp(argv[2], "shuffle") != 0 &&
        std::strcmp(argv[2], "noshuffle") != 0) {
        argerror();
        return 1;
    }
    for (int i = 5; i < argc; i += 2) {
        if (std::strcmp(argv[i], "Simple") != 0 &&
            std::strcmp(argv[i], "Human") != 0) {
            argerror();
            return 1;
        }
    }

    // checking pack file
    std::ifstream pack{argv[1]};

    if (!pack.is_open()) {
        std::cout << "Error opening " << argv[1] << '\n';
        return 1;
    }

    std::cout << argv[0] << ".exe ";
    for (int i = 1; i < argc; ++i) {
        std::cout << argv[i] << ' ';
    }
    std::cout << std::endl;
    Game g = Game(pack, argv[2], pts, argv[4], argv[5], argv[6], argv[7],
                  argv[8], argv[9], argv[10], argv[11]);

    g.play();
    return 0;
}

static void argerror() {
    std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
              << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
              << "NAME4 TYPE4" << std::endl;
}

Game::Game(std::istream &pack_stream, const std::string &shuffling, int points,
           const std::string &name1, const std::string &type1,
           const std::string &name2, const std::string &type2,
           const std::string &name3, const std::string &type3,
           const std::string &name4, const std::string &type4)
        : do_shuffle(shuffling == "shuffle"), pts_to_win(points) {
    this->pack = Pack(pack_stream);

    players.push_back(Player_factory(name1, type1));
    players.push_back(Player_factory(name2, type2));
    players.push_back(Player_factory(name3, type3));
    players.push_back(Player_factory(name4, type4));
}

void Game::play() {
    int handcount = 0;
    while (team1pts < pts_to_win && team2pts < pts_to_win) {
        hand(handcount);
        handcount++;
    }
    if (team1pts >= pts_to_win) {
        std::cout << *players[0] << " and " << *players[2] << " win!\n";
    } else {
        std::cout << *players[1] << " and " << *players[3] << " win!\n";
    }
    // delete players
    for (auto &player: players) {
        delete player;
    }
}

//TODO finish implementing
void Game::hand(int hand) {
    std::cout << "Hand " << hand << '\n';
    //setup table
    shuffle();
    deal();
    //making trump
    Suit trump = SPADES;
    int ou_team = make_trump(trump);
    std::cout << '\n';
    // taking tricks
    int leader = (dealer + 1) % 4;
    int ou_team_tricks = 0;
    for (int i = 0; i < 5; ++i) {
        leader = trick(leader, trump);
        std::cout << '\n';
        if (leader % 2 == ou_team) {
            ou_team_tricks++;
        }
    }
    // scoring
    score(ou_team_tricks, team1pts, team2pts, ou_team);
    std::cout << *players[0] << " and " << *players[2] << " have " << team1pts
              << " points\n";
    std::cout << *players[1] << " and " << *players[3] << " have " << team2pts
              << " points\n";
    std::cout << '\n';

    // increment dealer (no need to mod because
    // wherever dealer is used it is modded by the same number, 4)
    ++dealer;
}

void Game::shuffle() {
    if (do_shuffle) {
        pack.shuffle();
        return;
    }
    pack.reset();
}

void Game::deal() {
    std::cout << *players[dealer] << " deals\n";
    // first four batches
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3 - (i % 2); ++j) {
            players[(dealer + i + 1) % 4]->add_card(pack.deal_one());
        }
    }
    // next four batches
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2 + (i % 2); ++j) {
            players[(dealer + i + 1) % 4]->add_card(pack.deal_one());
        }
    }
    // set upcard
    this->upcard = pack.deal_one();
    std::cout << upcard << " turned up\n";
}

int Game::make_trump(Suit &trump) {
    // round 1
    for (int i = 0; i < players.size(); ++i) {
        int curr = (dealer + i + 1) % 4;
        if (players[curr]->make_trump(upcard, i == 3, 1, trump)) {
            players[dealer % 4]->add_and_discard(upcard);
            std::cout << *players[curr] << " orders up " << trump << '\n';
            return (curr) % 2;
        }
        std::cout << *players[curr] << " passes\n";
    }
    // round 2
    for (int i = 0; i < players.size(); ++i) {
        int curr = (dealer + i + 1) % 4;
        if (players[curr]->make_trump(upcard, i == 3, 2, trump)) {
            std::cout << *players[curr] << " orders up " << trump << '\n';
            return (curr) % 2;
        }
        std::cout << *players[curr] << " passes\n";
    }
    assert(false);
}

//TODO finish implementing
int Game::trick(int leader, Suit trump) {
    int highest = leader;
    const Card &led = players[leader]->lead_card(trump);
    Card high = led;
    std::cout << led << " led by " << *players[leader] << '\n';
    for (int i = 1; i < 4; ++i) {
        const Card &played = players[(leader + i) % 4]->play_card(led, trump);
        std::cout << played << " played by " << *players[(leader + i) % 4]
                  << '\n';
        if (Card_less(high, played, led, trump)) {
            high = played;
            highest = (leader + i) % 4;
        }
    }
    std::cout << *players[highest] << " takes the trick\n";
    return highest;
}

//TODO finish implementing
void Game::score(const int &ordered_up_tricks, int &ou_pts, int &non_ou_pts,
                 const int &ou_team) {
    if (ordered_up_tricks >= 5) {
        ou_pts += 2;
        std::cout << *players[ou_team] << " and " << *players[ou_team + 2]
                  << " win the hand\n";
        std::cout << "march!\n";
        return;
    }
    if (ordered_up_tricks >= 3) {
        ou_pts++;
        std::cout << *players[ou_team] << " and " << *players[ou_team + 2]
                  << " win the hand\n";
        return;
    }
    non_ou_pts += 2;
    std::cout << *players[1 - ou_team] << " and " << *players[3 - ou_team]
              << " win the hand\n";
    std::cout << "euchred!\n";
}
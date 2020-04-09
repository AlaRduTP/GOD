#ifndef GAME_H
#define GAME_H

#include "zone.h"
#include "drone.h"
#include "iter.h"

/* -/- game.h -/- */

#include <ostream>

using namespace std;

class Player {
public:
    friend class Game;

    Player(int, int, int);
    Player() {};
    ~Player();

    const int id {-1};              // player ID
    Iter<Drone> drones;             // iterator of drones

    bool isControl(const Zone &) const;
    Drone & drone(int) const;       // get the drone
private:
    const int _nd {0};              // number of drones
    const int _nz {0};              // number of zones
    Drone * _ori_drones;            // drones owned by the player
    Drone ** _drones;               // pointer to drones owned by the player, used to swap
};

class Game {
public:
    Game(int, int, int, int);
    ~Game();

    const int me;                   // my player ID
    const int np;                   // number of players
    const int nd;                   // number of drones
    const int nz;                   // number of zones
    Iter<Player> players;           // iterator of players
    Iter<Zone> zones;               // iterator of zones

    Player & Me() const;            // get my player
    Player & player(int) const;     // get the player
    Player & Controller(const Zone &) const;
    Zone & zone(int) const;         // get the zone
    Zone & Trace(const Drone &) const;
    Iter<Drone> drones(const Player &, const Zone &) const;
    int Control(const Zone &) const;// the least number of drones to take or keep control of ceratin zone
    void UpdateZones();             // update who is controlling the zones
    void SocialDistancing() const;  // keep social distance
    void Output() const;            // output the destination points to be reached of my drones.
    void StayHome() const;

    template<typename T, typename U>
    static void Sort(Iter<T> & it, const U & point) {
        GOD::sort(it.begin(), it.end(), [&](const T & a, const T & b) {
            return a - point < b - point;
        });
    }

    template<typename T>
    static void Sort(Iter<T> & it, bool (* cmp)(const T &, const T &)) {
        GOD::sort(it.begin(), it.end(), cmp);
    }

    friend ostream & operator<<(ostream &, const Game &);
private:
    Player * _ori_players;          // all players in the game
    Player ** _players;             // pointer to all players in the game, used to swap
    Zone * _ori_zones;              // all zones in the game
    Zone ** _zones;                 // pointer to all zones, used to swap
};

/* -/- game.h -/- */

#endif

#ifndef GAME_H
#define GAME_H

#include "zone.h"
#include "drone.h"
#include "iter.h"

#include <ostream>

using namespace std;

/* -/- game.h -/- */

class Player {
public:
    Player(int, int, int);
    Player() {};
    ~Player();

    const int id {-1};              // player ID

    bool isContorl(const Zone &) const;
    Drone & drones(int) const;      // get the drone
    Iter<Drone> & drones() const;   // iterator of drones
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

    Player & Me() const;            // get my player
    Player & players(int) const;    // get the player
    Iter<Player> & players() const; // iterator of players
    Zone & zones(int) const;        // get the zone
    Iter<Zone> & zones() const;     // iterator of zones
    void Output() const;            // output the destination points to be reached of my drones.

    friend ostream & operator<<(ostream &, const Game &);
private:
    Player * _ori_players;          // all players in the game
    Player ** _players;             // pointer to all players in the game, used to swap
    Zone * _ori_zones;              // all zones in the game
    Zone ** _zones;                 // pointer to all zones, used to swap
};

/* -/- game.h -/- */

#endif

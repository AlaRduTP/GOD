#include "game.h"

/* -/- game.cpp -/- */

Player::Player(int d, int nd, int nz) : id(d), _nd(nd), _nz(nz) {
    _ori_drones = new Drone [nd];
    _drones = new Drone * [nd];
    for(int i = 0; i < nd; i++) {
        _drones[i] = _ori_drones + i;
    }
}

Player::~Player() {
    delete [] _ori_drones;
    delete [] _drones;
}

bool Player::isContorl(const Zone & zone) const {
    return zone._pid == id;
}

Drone & Player::drones(int did) const {
    return _ori_drones[did];
}

Iter<Drone> & Player::drones() const {
    Iter<Drone> * _iter = new Iter<Drone>;
    _iter->set(_drones, _nd);
    return *_iter;
}


Game::Game(int p, int e, int d, int z) : np(p), me(e), nd(d), nz(z) {
    _ori_zones = new Zone [nz];
    _zones = new Zone * [nz];
    for(int i = 0; i < nz; i++) {
        _zones[i] = _ori_zones + i;
    }

    _ori_players = new Player [np];
    _players = new Player * [np];
    for(int i = 0; i < np; i++) {
        new (_ori_players + i) Player(i, nd, nz);
        _players[i] = _ori_players + i;
    }
}

Game::~Game() {
    delete [] _ori_zones;
    delete [] _zones;
    delete [] _ori_players;
    delete [] _players;
}

Player & Game::Me() const {
    return players(me);
}

Player & Game::players(int pid) const {
    return _ori_players[pid];
}

Iter<Player> & Game::players() const {
    Iter<Player> * _iter = new Iter<Player>;
    _iter->set(_players, np);
    return *_iter;
}

Zone & Game::zones(int zid) const {
    return _ori_zones[zid];
}

Iter<Zone> & Game::zones() const {
    Iter<Zone> * _iter = new Iter<Zone>;
    _iter->set(_zones, nz);
    return *_iter;
}

void Game::Output() const {
    for(const Drone & drone : Me().drones()){
        cout << drone.x << ' ' << drone.y << endl;
    }
}

ostream & operator<<(ostream & os, const Game & game) {
    os << "My player ID:                  " << game.me << endl;
    os << "Number of players:             " << game.np << endl;
    os << "Number of drones in each team: " << game.nd << endl;
    os << "Number of zones:               " << game.nz << endl;
    return os;
}

/* -/- game.cpp -/- */

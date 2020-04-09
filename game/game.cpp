#include "game.h"

/* -/- game.cpp -/- */

Player::Player(int d, int nd, int nz) : id(d), _nd(nd), _nz(nz) {
    _ori_drones = new Drone [nd];
    _drones = new Drone * [nd];
    for(int i = 0; i < nd; i++) {
        _drones[i] = _ori_drones + i;
    }
    drones = {_drones, _nd};
}

Player::~Player() {
    delete [] _ori_drones;
    delete [] _drones;
}

bool Player::isControl(const Zone & zone) const {
    return zone._pid == id;
}

Drone & Player::drone(int did) const {
    return _ori_drones[did];
}


Game::Game(int p, int e, int d, int z) : np(p), me(e), nd(d), nz(z) {
    _ori_zones = new Zone [nz];
    _zones = new Zone * [nz];
    for(int i = 0; i < nz; i++) {
        _zones[i] = _ori_zones + i;
    }
    zones = {_zones, nz};

    _ori_players = new Player [np];
    _players = new Player * [np];
    for(int i = 0; i < np; i++) {
        new (_ori_players + i) Player(i, nd, nz);
        _players[i] = _ori_players + i;
    }
    players = {_players, np};
}

Game::~Game() {
    delete [] _ori_zones;
    delete [] _zones;
    delete [] _ori_players;
    delete [] _players;
}

Player & Game::Me() const {
    return player(me);
}

Player & Game::player(int pid) const {
    return _ori_players[pid];
}

Player & Game::Controller(const Zone & zn) const {
    return player(zn._pid);
}

Zone & Game::zone(int zid) const {
    return _ori_zones[zid];
}

Zone & Game::Trace(const Drone & drn) const {
    int zid = -1;
    int v[2] = {0};
    if(drn._trace[0][0] > 0) {
        v[0] = drn._trace[1][0] - drn._trace[0][0];
        v[1] = drn._trace[1][1] - drn._trace[0][1];
    }
    if(v[0] > 0 || v[1] > 0) {
        int max = -1, t[2];
        for(int i = 0; i < nz; i++) {
            const Zone & zn = zone(i);
            t[0] = zn.x - drn._trace[0][0];
            t[1] = zn.y - drn._trace[0][1];
            int dot = (v[0]*t[0] + v[1]*t[1]);
            if(dot > max) {
                dot = max;
                zid = i;
            }
        }
    }
    if(zid < 0) {
        int min = 20000000;
        for(int i = 0; i < nz; i++) {
            int dis = drn - zone(i);
            if(dis < min) {
                min = dis;
                zid = i;
            }
        }
    }
    return zone(zid);
}

Iter<Drone> Game::drones(const Player & ply, const Zone & zn) const {
    Drone ** _drones = new Drone * [nd];
    int count = 0;
    for(Drone & drn : ply.drones) {
        if(drn.In(zn)) {
            _drones[count++] = &drn;
        }
    }
    return {_drones, count, true};
}

int Game::Control(const Zone & zn) const {
    int max = 1;
    int ctr = zn._pid;
    if(ctr != -1) {
        if(ctr != me) {
            const Player & ply = player(ctr);
            return drones(ply, zn).size() + 1;
        } else {
            max = 0;
            for(const Player & ply : players) {
                if(ply.id == me) {
                    continue;
                }
                int count = 0;
                for(Drone & drn : ply.drones) {
                    if(drn.In(zn)) {
                        ++count;
                    }
                }
                max = count > max ? count : max;
            }
        }
    }
    return max;
}

void Game::UpdateZones() {
    for(int i = 0; i < nz; i++) {
        zone(i).Update();
    }
}

void Game::Output() const {
    for(int i = 0; i < nd; i++) {
        const Drone & drone = Me().drone(i);
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

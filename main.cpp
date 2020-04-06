#include "game/game.h"

#include <iostream>

using namespace std;

/* -/- main.cpp -/- */

int main() {
    int P, ID, D, Z;
    cin >> P >> ID >> D >> Z; cin.ignore();

    // Initialize the game by :
    //      - me:   ID of my player
    //      - np:   number of players in the game
    //      - nd:   number of drones in each team
    //      - nz:   number of zones on the map
    Game game(P, ID, D, Z);

    // Output game info
    cerr << game;

    // Initialize the positions of the zone
    for(Zone & zone : game.zones()) {
        cin >> zone; cin.ignore();
    }

    while(1) {
        // Update who is controlling the zones
        for(Zone & zone : game.zones()) {
            zone.Update();
        }

        // Update coordinates of drones of players
        for(const Player & player : game.players()) {
            for(Drone & drone : player.drones()) {
                cin >> drone; cin.ignore();
            }
        }

        // Output game info
        for(const Player & player : game.players()) {
            cerr << "Player #" << player.id << ':' << endl;
            for(Drone & drone : player.drones()) {
                cerr << drone << endl;
            }
            cerr << "--- Control ---" << endl;
            for(Zone & zone : game.zones()) {
                cerr << player.isContorl(zone) << endl;
            }
            cerr << "======" << endl;
        }

        // Your code goes here
        // ...
        for(int i = 0; i < game.nd; i++) {
            game.Me().drones(i) = game.zones(i%3 + 1);
        }

        // Output the destination points to be
        // reached by my drones.
        game.Output();
    }
}

/* -/- main.cpp -/- */

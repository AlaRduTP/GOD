#include "game/game.h"

/* -/- main.cpp -/- */

#include <iostream>

using namespace std;

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
    for(Zone & zone : game.zones) {
        cin >> zone; cin.ignore();
    }

    // Sort zones by x
    GOD::sort(game.zones.begin(), game.zones.end(), [](const Zone & a, const Zone & b) -> bool {
        return a.x < b.x;
    });

    while(1) {
        // Update who is controlling the zones
        game.UpdateZones();

        // Update coordinates of drones of players
        for(const Player & player : game.players) {
            for(Drone & drone : player.drones) {
                cin >> drone; cin.ignore();
            }
        }

        // Sort drones by the distance from zone #0
        game.Sort(game.Me().drones, game.zone(0));

        // Output game info
        for(const Player & player : game.players) {
            cerr << "Player #" << player.id << ':' << endl;
            cerr << "--- Drones ---" << endl;
            for(const Drone & drone : player.drones) {
                cerr << drone << endl;
                if(player.id != game.me) {
                    cerr << "this drone maybe is going/close to " << game.Trace(drone) << endl;
                }
            }
            cerr << "--- Control ---" << endl;
            for(const Zone & zone : game.zones) {
                cerr << "Zone " << zone << " :" << endl;
                if(player.isControl(zone)) {
                    auto drones = game.drones(player, zone);
                    for(const Drone & drone : drones) {
                        cerr << drone << endl;
                    }
                    cerr << "totle: " << drones.size() << endl;
                }
                if(player.id == game.me) {
                    cerr << "you need " << game.Control(zone) << " drone(s) to (keep) control" << endl;
                }
                cerr << "---" << endl;
            }
            cerr << "======" << endl;
        }

        // Your code goes here
        // ...
        for(int i = 0; i < game.nd; i++) {
            game.Me().drone(i) = game.zone(i%3 + 1);
        }

        // Output the destination points to be
        // reached by my drones.
        game.Output();
    }
}

/* -/- main.cpp -/- */

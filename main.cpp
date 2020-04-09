#include "game/game.h"

/* -/- main.cpp -/- */

#include <iostream>

using namespace std;

bool mycmp(const Zone & a, const Zone & b) {
    return a.x < b.x;
}

int main() {
    // ### STEP 1 ###
    // Initialize the game by :
    //      - me:   ID of my player
    //      - np:   number of players in the game
    //      - nd:   number of drones in each team
    //      - nz:   number of zones on the map
    int P, ID, D, Z;
    cin >> P >> ID >> D >> Z; cin.ignore();
    Game game(P, ID, D, Z);

    // ### EXAMPLE ###
    // Output game info
    cerr << game;

    // ### STEP 2 ###
    // Initialize the positions of the zone
    for(Zone & zone : game.zones) {
        cin >> zone; cin.ignore();
    }

    // ### EXAMPLE ###
    // Sort zones by x
    game.Sort(game.zones, mycmp);

    /*  ### CAUTION ###
        Using lambda will cause error here,
        or you can either use `GOD::sort` with a lambda compare function: */
    // GOD::sort(game.zones.begin(), game.zones.end(), [](const Zone & a, const Zone & b) -> bool {
    //     return a.x < b.x;
    // });

    while(1) {
        // ### STEP 3 ###
        // Update who is controlling the zones
        game.UpdateZones();

        // ### STEP 4 ###
        // Update coordinates of drones of players
        for(const Player & player : game.players) {
            for(Drone & drone : player.drones) {
                cin >> drone; cin.ignore();
            }
        }

        // ### EXAMPLE ###
        // Sort drones by the distance from zone #0
        game.Sort(game.Me().drones, game.zone(0));

        // ### EXAMPLE ###
        // Output game info
        for(const Player & player : game.players) {
            cerr << "Player #" << player.id << ':' << endl;
            cerr << "--- Drones ---" << endl;
            for(const Drone & drone : player.drones) {
                cerr << drone << endl;
                if(player.id != game.me) {
                    // Tracing the enemy's drones
                    cerr << "this drone maybe is going/close to " << game.Trace(drone) << endl;
                }
            }
            cerr << "--- Control ---" << endl;
            for(const Zone & zone : game.zones) {
                cerr << "Zone " << zone << " :" << endl;
                if(player.isControl(zone)) {
                    // How many drones are in the controled zone
                    auto drones = game.drones(player, zone);
                    for(const Drone & drone : drones) {
                        cerr << drone << endl;
                    }
                    cerr << "totle: " << drones.size() << endl;
                }
                if(player.id == game.me) {
                    // The least number of my drones to take/keep control the zone
                    cerr << "you need " << game.Control(zone) << " drone(s) to (keep) control" << endl;
                }
                cerr << "---" << endl;
            }
            cerr << "======" << endl;
        }

        // ### STEP 5 ###
        // Your code goes here
        // ...
        game.SocialDistancing();    // Just for example

        // ### STEP 6 ###
        // Output the destination points to be
        // reached by my drones.
        game.Output();

        // game.StayHome();            // Isolate!

        // Back to STEP 3
    }
}

/* -/- main.cpp -/- */

#ifndef DRONE_H
#define DRONE_H

#include "coord.h"

/* -/- drone.h -/- */

using namespace std;

class Drone : public Coord<Drone> {
public:
    friend class Player;
    friend class Game;
    using Coord<Drone>::operator=;
};

/* -/- drone.h -/- */

#endif

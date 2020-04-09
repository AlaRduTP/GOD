#ifndef ZONE_H
#define ZONE_H

#include "coord.h"

/* -/- zone.h -/- */

class Zone : public Coord<Zone> {
public:
    friend class Player;
    friend class Game;
private:
    void Update();
    int _pid {-1};  // who is controlling the zone
};

/* -/- zone.h -/- */

#endif

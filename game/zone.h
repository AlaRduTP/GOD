#ifndef ZONE_H
#define ZONE_H

#include "coord.h"

/* -/- zone.h -/- */

class Zone : public Coord<Zone> {
public:
    friend class Player;

    void Update();
private:
    int _pid {-1};  // who is controlling the zone
};

/* -/- zone.h -/- */

#endif

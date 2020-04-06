#ifndef DRONE_H
#define DRONE_H

#include "coord.h"

#include <iostream>

using namespace std;

/* -/- drone.h -/- */

class Drone : public Coord<Drone> {
public:
	using Coord<Drone>::operator=;
};

/* -/- drone.h -/- */

#endif

#include "particle.h"
#include "math.h"

void SnowPart::incLocation() {
    location.y += velocity;
}


#ifndef PARTICLE_H
#define PARTICLE_H

#include "user_definitions.h"

class Particle {
public:
    Point  getLocation    () const { return location;        }
    double getVelocity    () const { return velocity;        }
    Color  getColor       () const { return color;           }
    int    getLifetime    () const { return lifetime;        }

    void setLocation    (Point p)       { location = p;             }
    void setVelocity    (double vel)    { velocity = vel;           }
    void setColor       (Color col)     { color = col;              }
    void setLifetime    (int lt)        { lifetime = lt;            }

    virtual void incLocation    () {}
    virtual void incVelocity    () {}
    virtual void incLifetime    () { ++lifetime; }

    Particle() {}
    virtual ~Particle() {}

protected:
    Point location;
    double velocity;
    Color color; // каждая компонента варьируется [-1, 1]
    int lifetime;
};

class SnowPart : public Particle {
public:
    SnowPart() : Particle() {}

    void incLocation    ();
    void incVelocity    () {}
};

#endif // PARTICLE_H

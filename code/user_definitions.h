#ifndef USER_DEFINITIONS_H
#define USER_DEFINITIONS_H

#define G 9.8
#define PI 0.52359877559829887307710723054658
#define MAX_Y 10000
#define MIN_Y -10000
#define MAX_X 10000
#define MIN_X -10000
#define MAX_Z 10000
#define MIN_Z -10000

#define SCALE 1.5
#define ANGLE 0.25
#define MOVE 5

#define DARKER_LVL 50

#include <QColor>
#include "calculations.h"

enum Intensity {
    DISAPPEAR = 0,
    MINIMUM, //снег 54.4; 
    MIDDLE,  //снег 57.9; 
    INTENSIVE, //снег 67.6; 
    MAXIMUM  //снег 98.6; 
};

class Point {
public:
    double x, y, z;
    Point() { x = y = z = 0; }
    Point(int nx, int ny, int nz) {
        x = nx; y = ny; z = nz;
    }
    Point(Point const& p) {
        x = p.x; y = p.y; z = p.z;
    }

    Point &operator =(Point const& p) {
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }

    bool operator ==(Point& p) {
        return (x == p.x) && (y = p.y) && (z = p.z);
    }
};

class Color {
public:
    unsigned short int r, g, b;
    Color() {
        r = 255; g = 255; b = 255;
    }

    Color(unsigned short int red, unsigned short int green, unsigned short int blue) {
        r = red;
        g = green;
        b = blue;
    }
    Color(Color const& c) {
        r = c.r;
        g = c.g;
        b = c.b;
    }

    Color &operator =(Color const& c) {
        r = c.r;
        g = c.g;
        b = c.b;
        return *this;
    }

    bool operator ==(Color& col) {
        return (r == col.r) && (g = col.g) && (b = col.b);
    }

    QColor toQColor(int alpha = 255) {
        QColor qc;

        qc.setRed(r);
        qc.setGreen(g);
        qc.setBlue(b);
        qc.setAlpha(alpha);

        return qc;
    }
};

class Size {
public:
    int length, width, height;
    Size() { length = width = height = 0; }
    Size(int l, int w, int h) {
        length = l; width = w; height = h;
    }
    Size(Size const& sz) {
        length = sz.length;
        width = sz.width;
        height = sz.height;
    }

    Size &operator =(Size const& s) {
        length = s.length;
        width = s.width;
        height = s.height;
        return *this;
    }
};

class PointsToSend {
public:
    Point p;
    Color c;

    PointsToSend() {
        p = Point();
        c = Color();
    }
    PointsToSend(PointsToSend const& pnts) {
        p = pnts.p;
        c = pnts.c;
    }

    PointsToSend(Point pnt, Color col) {
        p = pnt;
        c = col;
    }

    PointsToSend &operator =(PointsToSend const& pnts) {
        p = pnts.p;
        c = pnts.c;
        return *this;
    }

    bool operator ==(PointsToSend& pnts) {
        return (pnts.p == p) && (pnts.c == c);
    }
};

struct Cell {
    double z;
    Color col;
};

class Triangle {
public:
    Color col;
    Point p[3];

    Triangle(Point p1, Point p2, Point p3, Color c) {
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
        col = c;
    }
    Triangle() {}
};


#endif // USER_DEFINITIONS_H

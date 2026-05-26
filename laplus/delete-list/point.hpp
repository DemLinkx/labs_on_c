#ifndef POINT_H
#define POINT_H

#include <iostream>

struct point {
    int x, y;
};

inline bool operator<(const point& p1, const point& p2) {
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

inline std::ostream& operator<<(std::ostream& os, const point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

#endif
#include "Coords.h"
#include "Array.h"
 Coords::Coords() {
    x = 0;
    y = 0;
}

 Coords::Coords(int x, int y) {
    this->x = x;
    this->y = y;
}

 bool Coords::operator==(Coords& c) const {
         return x == c.x && y == c.y;
 }

 bool Coords::operator!=(Coords& c) const {
     return x != c.x || y != c.y;
 }

 Coords Coords::operator+(const Coords& c) const {
     return Coords(x + c.x, y + c.y);
 }


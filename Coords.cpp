#include "Coords.h"
#include "Array.h"
 Coords::Coords() {
    x = 0;
    y = 0;
    depth = 0;
}

 Coords::Coords(int x, int y) {
    this->x = x;
    this->y = y;
    depth = 0;
}

 Coords::Coords(int x, int y, int depth) {
    this->x = x;
    this->y = y;
    this->depth = depth;
}

 bool Coords::operator==(Coords& c)
 {
         return x == c.x && y == c.y;
 }

 bool Coords::operator!=(Coords& c)
 {
     return x != c.x || y != c.y;
 }

 Coords Coords::operator+(const Coords& c)
 {
     return Coords(x + c.x, y + c.y);
 }

 String Coords::toString()
 {
     String s = "(";
     s += x;
     s += ",";
     s += y;
     s += ")";
     return s;
 }


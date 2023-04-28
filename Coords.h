#pragma once
#include "Array.h"
class Coords
{
public:
    int x;
    int y;
    int depth;
    Coords();
    Coords(int x, int y);
    Coords(int x, int y, int depth);
    bool operator==(Coords& c);
    bool operator!=(Coords& c);
    Coords operator+(const Coords& c);
    String toString();
};


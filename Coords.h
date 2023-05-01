#pragma once
#include "Array.h"
class Coords
{
public:
    int x;
    int y;
    Coords();
    Coords(int x, int y);
    bool operator==(Coords& c) const;
    bool operator!=(Coords& c) const;
    Coords operator+(const Coords& c) const;
};


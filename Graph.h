#pragma once
#include "HashTable.h"
#include "Array.h"
#include "Coords.h"
class Graph
{
private:
    int width;
    int height;
    struct City {
        Coords location;
        String name;
    };
    Array<City> VIDToCity;
    int** CoordsToVID;
    HashTable<String, int> CityNameToVID;
    int citiesCount = 0;
    const Coords DIRECTIONS[4] = { Coords(0, 1), Coords(0, -1), Coords(1, 0), Coords(-1, 0) };
    struct Flight {
        int destination;
        int time;
    };
    Array<Array<Flight>> adjList;
public:
    Graph(int w, int h);
    ~Graph();
    void AddCity(String& cityName, Coords& location);
    void AddAnonymousCity(Coords& location);
    void AddFlight(String& from, String& to, int time);
    void AddFlight(int& from, int& to, int time);
    void AddFlight(Coords& from, Coords& to, int time);
    void PrintShortestPath(String& from, String& to, bool verbose);
};
#pragma once
#include "HashTable.h"
#include "Array.h"
#include "Coords.h"
class Graph
{
private:
	struct City {
		Coords location;
		String name;
	};
	Array<City> VIDToCity;
	//Array<String> VIDToCityName;
	HashTable<String, int> CityNameToVID;
	int citiesCount = 0;
	const Coords DIRECTIONS[4] = { Coords(0, 1), Coords(0, -1), Coords(1, 0), Coords(-1, 0) };
	struct Flight {
		int destination;
		int time;
	};
	Array<Array<Flight>> adjList;
	Array<bool> parsedAdjMatrix;
	Array<Array<int>> visited;
	int visitedCount = 0;
	Array<int> skip;
public:
	Graph();
	~Graph();
	void AddCity(String& cityName, Coords& location);
	int GetCitiesCount();
	void AddFlight(String& from, String& to, int time);
	void AddFlight(int& from, int& to, int time);
	int bfs(Array<String>& map, Coords& start, Coords& end);
	void ParseAdjMatrix(Array<String>& map);
	//void SelectiveParse(Array<String>& map, Coords& start, Coords& end);
	void PrintShortestPath(Array<String>& map, String& from, String& to, bool verbose);
};


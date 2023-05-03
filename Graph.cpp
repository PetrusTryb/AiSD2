#include "Graph.h"
#include "PriorityQueue.h"
#include <climits>
#include <stdio.h>


Graph::Graph(int w, int h) {
    width = w;
    height = h;
    VIDToCity.Resize(float(w * h) / 1.99);
    CoordsToVID = new int* [height];
    for (int i = 0; i < height; i++) {
        CoordsToVID[i] = new int[width] {-1};
    }
}

Graph::~Graph() {
    delete[] CoordsToVID;
}

void Graph::AddCity(String& cityName, Coords& location) {
    CityNameToVID.Insert(cityName, citiesCount);
    VIDToCity[citiesCount].location = location;
    VIDToCity[citiesCount].name = cityName;
    CoordsToVID[location.y][location.x] = citiesCount;
    citiesCount++;
}

void Graph::AddAnonymousCity(Coords& location) {
    VIDToCity[citiesCount].location = location;
    VIDToCity[citiesCount].name = String(0);
    CoordsToVID[location.y][location.x] = citiesCount;
    citiesCount++;
}

void Graph::PrepareForAddingFlights()
{
    if (adjList.Size() == 0) {
        adjList.Resize(citiesCount);
    }
}

void Graph::AddFlight(String& from, String& to, int time) {
    int fromVID = CityNameToVID[from];
    int toVID = CityNameToVID[to];
    Flight flight;
    flight.destination = toVID;
    flight.time = time;
    adjList[fromVID].Add(flight);
}

void Graph::AddFlight(int& from, int& to, int time) {
    Flight flight;
    flight.destination = to;
    flight.time = time;
    adjList[from].Add(flight);
}

void Graph::AddFlight(Coords& from, Coords& to, int time) {

    int fromVID = CoordsToVID[from.y][from.x];
    int toVID = CoordsToVID[to.y][to.x];
    AddFlight(fromVID, toVID, time);
}

void Graph::PrintShortestPath(String& from, String& to, bool verbose) {
    int fromVID = CityNameToVID[from];
    int toVID = CityNameToVID[to];
    Coords start = VIDToCity[fromVID].location;
    Coords end = VIDToCity[toVID].location;
    if (fromVID == toVID)
    {
        printf("0\n");
        return;
    }
    Array<int> dist = Array<int>(citiesCount);
    Array<int> prev = Array<int>(citiesCount);
    for (int i = 0; i < citiesCount; i++) {
        dist[i] = INT_MAX - 1;
        prev[i] = -1;
    }
    dist[fromVID] = 0;
    PriorityQueue<int> pq;
    pq.Insert(fromVID, 0);
    int v;
    int alt;
    Flight* flight;
    int i;
    while (pq.Count()) {
        int u = pq.Pop();
        int limit = adjList[u].Size();
        for (i = 0; i < limit; ++i) {
            flight = &adjList[u][i];
            v = flight->destination;
            alt = dist[u] + flight->time;
            if (alt >= dist[v] - 200)
                continue;
            dist[v] = alt;
            prev[v] = u;
            pq.Insert(v, alt);
        }
    }
    printf("%d", dist[toVID]);
    int current = toVID;
    if (!verbose || CityNameToVID.Count() <= 2) {
        printf("\n");
        return;
    }
    Array<int> path;
    while (current != -1) {
        path.Add(current);
        current = prev[current];
    }
    for (int i = path.Size() - 2; i > 0; i--) {
        if (VIDToCity[path[i]].name.Size() > 0)
            printf(" %s", VIDToCity[path[i]].name.ToValidString());
    }
    printf("\n");
}
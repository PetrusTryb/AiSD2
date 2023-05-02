#include "Graph.h"
#include "Queue.h"
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
    //printf("%d %d - %s, VID=%d\n", location.x, location.y, cityName.ToValidString(), citiesCount-1);
}

void Graph::AddAnonymousCity(Coords& location) {
    VIDToCity[citiesCount].location = location;
    VIDToCity[citiesCount].name = "";
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
    //printf("%s -> %s: %d\n", from.ToValidString(), to.ToValidString(), time);
    //printf("\t%d -> %d: %d\n", fromVID, toVID, time);
}

void Graph::AddFlight(int& from, int& to, int time) {
    Flight flight;
    flight.destination = to;
    flight.time = time;
    adjList[from].Add(flight);
    //printf("%d -> %d: %d\n", from, to, time);
}

void Graph::AddFlight(Coords& from, Coords& to, int time) {
    
    int fromVID = CoordsToVID[from.y][from.x];
    int toVID = CoordsToVID[to.y][to.x];
    AddFlight(fromVID, toVID, time);
}

void Graph::PrintShortestPath(String& from, String& to, bool verbose) {
    //printf("From: %s\nTo: %s\n", from.ToValidString(), to.ToValidString());
    int fromVID = CityNameToVID[from];
    int toVID = CityNameToVID[to];
    Coords start = VIDToCity[fromVID].location;
    Coords end = VIDToCity[toVID].location;
    if (fromVID == toVID)
    {
        printf("0\n");
        return;
    }
    int* dist = new int[citiesCount];
    int* prev = new int[citiesCount];
    for (int i = 0; i < citiesCount; i++) {
        dist[i] = INT_MAX - 1;
        prev[i] = -1;
    }
    dist[fromVID] = 0;
    PriorityQueue<int> pq;
    pq.Insert(fromVID, 0);
    int v;
    int alt;
    int u;
    int limit;
    Flight* flight;
    int i;
    while (pq.count) {
        u = pq.Pop();
        limit = adjList[u].currentLenght;
        //printf("Limit: %ld", limit);
        //printf("PQ Count: %d\n", pq.Count());
        for (i = 0; i < limit; ++i) {
            flight = &adjList[u][i];
            v = flight->destination;
            alt = dist[u] + flight->time;
            if (alt >= dist[v]-50)
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
        delete[] dist;
        delete[] prev;
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
    delete[] dist;
    delete[] prev;
}
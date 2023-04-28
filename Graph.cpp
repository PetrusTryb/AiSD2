#include "Graph.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include <climits>
#include <stdio.h>


Graph::Graph()
{
	VIDToCity.bigBlockMode(true);
}

Graph::~Graph()
{
	
}

void Graph::AddCity(String& cityName, Coords& location)
{
	CityNameToVID.Insert(cityName, citiesCount);
	VIDToCity.Add({location, cityName});
	//CityNameToVID.Insert(location.toString(), citiesCount);
	citiesCount++;
	skip.Add(0);
	//printf("%d %d - %s, VID=%d\n", location.x, location.y, cityName.ToValidString(), citiesCount-1);
}

int Graph::GetCitiesCount()
{
	return citiesCount;
}

void Graph::AddFlight(String& from, String& to, int time)
{
	if (adjList.size() == 0) {
		adjList = Array<Array<Flight>>(citiesCount);
		adjList.bigBlockMode(true);
	}
	int fromVID = CityNameToVID[from];
	int toVID = CityNameToVID[to];
	Flight flight;
	flight.destination = toVID;
	flight.time = time;
	adjList[fromVID].Add(flight);
	//printf("%s -> %s: %d\n", from.ToValidString(), to.ToValidString(), time);
	//printf("\t%d -> %d: %d\n", fromVID, toVID, time);
}

void Graph::AddFlight(int& from, int& to, int time)
{
	if (adjList.size() == 0)
		adjList = Array<Array<Flight>>(citiesCount);
	Flight flight;
	flight.destination = to;
	flight.time = time;
	adjList[from].Add(flight);
	//printf("%d -> %d: %d\n", from, to, time);
}

int Graph::bfs(Array<String>& map, Coords& start, Coords& end) {
	Queue<Coords> q;
	start.depth = 1;
	q.Enqueue(start);
	if (visitedCount == 0) {
		visited = Array<Array<int>>(map.size());
		for (int i = 0; i < map.size(); i++) {
			visited[i] = Array<int>(map[i].size());
		}
		for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < map[i].size(); j++) {
				visited[i][j] = 0;
			}
		}
	}
	visitedCount++;
	while (q.Count()) {
		Coords current = q.Dequeue();
		if (current == end) {
			return current.depth;
		}
		if (visited[current.x][current.y]>=visitedCount)
			continue;
		visited[current.x][current.y] = visitedCount;
		for (int i = 0; i < 4; i++)
		{
			Coords dir = current + DIRECTIONS[i];
			int cdepth = current.depth + 1;
			if(dir.x>=map.size()||dir.y>=map[0].size()||dir.x<0||dir.y<0)
				continue;
			if ((map[dir.x][dir.y] == '#') && visited[dir.x][dir.y] < visitedCount)
				q.Enqueue({ dir.x,dir.y,cdepth });
			else if (dir == end)
				return current.depth;
		}
	}
	return -1;
}

void Graph::ParseAdjMatrix(Array<String>& map)
{
	int citiesCount = VIDToCity.size();
	for (int i = 0; i < citiesCount; i++) {
		for (int j = i + 1; j < citiesCount; j++) {
			int time = bfs(map, VIDToCity[i].location, VIDToCity[j].location);
			if (time != -1) {
				AddFlight(i, j, time);
				AddFlight(j, i, time);
			}
		}
	}
}

void Graph::PrintShortestPath(Array<String>& map, String& from, String& to, bool verbose)
{
	int fromVID = CityNameToVID[from];
	int toVID = CityNameToVID[to];
	if (fromVID == toVID)
	{
		printf("0\n");
		return;
	}
	Array<int> dist(citiesCount);
	Array<int> prev(citiesCount);
	for (int i = 0; i < citiesCount; i++) {
		dist[i] = INT_MAX/2;
		prev[i] = -1;
	}
	dist[fromVID] = 0;
	PriorityQueue<int> pq;
	pq.Enqueue(fromVID, 0);
	while (pq.Count()) {
		int u = pq.Dequeue();
		for (int i = 0; i < adjList[u].size(); i++) {
			Flight& flight = adjList[u][i];
			int v = flight.destination;
			int alt = dist[u] + flight.time;
			if (alt < dist[v]) {
				dist[v] = alt;
				prev[v] = u;
				pq.Enqueue(v, alt);
			}
		}
	}
	printf("%d", dist[toVID]);
	int current = toVID;
	if (!verbose) {
		printf("\n");
		return;
	}
	Array<int> path;
	while (current != -1) {
		path.Add(current);
		current = prev[current];
	}
	for (int i = path.size() - 2; i > 0; i--) {
		printf(" %s", VIDToCity[path[i]].name.ToValidString());
	}
	printf("\n");
}

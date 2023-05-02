#include <stdio.h>
#include "Array.h"
#include "HashTable.h"
#include "Coords.h"
#include "Graph.h"

using namespace std;

String read() {
    String str;
    char c = '_';
    while (true)
    {
        c = _getchar_nolock();
        if (c != ' ' && c != '\n')
            str.Add(c);
        else if (str.Size())
            return str;
    }
}

int main()
{
    int width = read().ToInt();
    int height = read().ToInt();
    String* map = new String[height];
    for (int i = 0; i < height; i++) {
        map[i] = read();
    }
    String name;
    Coords location(-1, -1);
    Coords invalid(-1, -1);
    Graph graph = Graph(width, height);
    Coords toCheck[8] = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1} };
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] >= 48 && map[i][j] <= 90) {
                name.Add(map[i][j]);
                if (location == invalid)
                    for (int c = 0; c < 8; c++) {
                        if (i + toCheck[c].y < height && j + toCheck[c].x < width && i + toCheck[c].y >= 0 && j + toCheck[c].x >= 0)
                            if (map[i + toCheck[c].y][j + toCheck[c].x] == '*') {
                                location = Coords(j + toCheck[c].x, i + toCheck[c].y);
                            }
                    }
            }
            else if (name.Size()) {
                graph.AddCity(name, location);
                location = invalid;
                name.Clear();
            }
        }
    }
    if (name.Size()) {
        graph.AddCity(name, location);
        location = invalid;
        name.Clear();
    }
    Coords crds;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == '#') {
                crds = { j,i };
                graph.AddAnonymousCity(crds);
            }
        }
    }
    graph.PrepareForAddingFlights();
    Coords from;
    Coords to;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == '#' || map[i][j] == '*') {
                if (i > 0) {
                    if (map[i - 1][j] == '#' || map[i - 1][j] == '*') {
                        from = { j, i - 1 };
                        to = { j, i };
                        graph.AddFlight(from, to, 1);
                        graph.AddFlight(to, from, 1);
                    }
                }
                if (j > 0) {
                    if (map[i][j - 1] == '#' || map[i][j - 1] == '*') {
                        from = { j - 1, i };
                        to = { j, i };
                        graph.AddFlight(from, to, 1);
                        graph.AddFlight(to, from, 1);
                    }
                }
            }
        }
        if (i >= 1)
            map[i - 1].Resize(0);
    }
    delete[] map;
    int flights = read().ToInt();
    String loc;
    String dest;
    for (int i = 0; i < flights; i++) {
        loc = read();
        dest = read();
        int time = read().ToInt();
        graph.AddFlight(loc, dest, time);
        //printf("%s -> %s: %d\n", loc.ToValidString(), dest.ToValidString(), time);
    }
    //graph.ParseAdjMatrix(map);
    int queries = read().ToInt();
    for (int i = 0; i < queries; i++) {
        loc = read();
        dest = read();
        bool showPath = (read().ToInt() == 1);
        graph.PrintShortestPath(loc, dest, showPath);
        continue;
    }

    return 0;
}
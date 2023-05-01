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
        c = getchar();
        if (c != ' ' && c != '\n' && c != EOF && c != '\r')
            str += c;
        else if (str.Size())
            break;
    }
    return str;
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
                name += (map[i][j]);
                if (location == invalid)
                    for (int c = 0; c < 8; c++) {
                        if (i + toCheck[c].y < height && j + toCheck[c].x < map[i].Size() && i + toCheck[c].y >= 0 && j + toCheck[c].x >= 0)
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
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == '#') {
                Coords crds = Coords(j, i);
                graph.AddAnonymousCity(crds);
            }
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == '#' || map[i][j] == '*') {
                if (i > 0) {
                    if (map[i - 1][j] == '#' || map[i - 1][j] == '*') {
                        Coords from = Coords(j, i - 1);
                        Coords to = Coords(j, i);
                        graph.AddFlight(from, to, 1);
                        graph.AddFlight(to, from, 1);
                    }
                }
                if (j > 0) {
                    if (map[i][j - 1] == '#' || map[i][j - 1] == '*') {
                        Coords from = Coords(j - 1, i);
                        Coords to = Coords(j, i);
                        graph.AddFlight(from, to, 1);
                        graph.AddFlight(to, from, 1);
                    }
                }
            }
        }
        if (i >= 1)
            map[i - 1] = Array<char>(1);
    }
    delete[] map;
    int flights = read().ToInt();
    for (int i = 0; i < flights; i++) {
        String loc = read();
        String dest = read();
        int time = read().ToInt();
        graph.AddFlight(loc, dest, time);
        //printf("%s -> %s: %d\n", loc.ToValidString(), dest.ToValidString(), time);
    }
    //graph.ParseAdjMatrix(map);
    int queries = read().ToInt();
    for (int i = 0; i < queries; i++) {
        String from = read();
        String to = read();
        bool showPath = (read().ToInt() == 1);
        graph.PrintShortestPath(from, to, showPath);
        continue;
    }

    return 0;
}
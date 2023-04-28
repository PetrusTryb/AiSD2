#include <stdio.h>
#include "Array.h"
#include "HashTable.h"
#include "Coords.h"
#include "Graph.h"

using namespace std;

String read() {
    String str;
	char c='_';
    while (true)
    {
		c = getchar();
        if (c != ' ' && c != '\n' && c != EOF && c!= '\r')
            str += c;
        else if(str.size())
            break;
	}
    return str;
}

int main()
{
    int width = read().ToInt();
    int height = read().ToInt();
    Array<String> map(height);
    map.bigBlockMode(true);
    for (int i = 0; i < height; i++) {
        map[i] = read();
	}
    String name;
    Coords location(-1,-1);
    Coords invalid(-1, -1);
    Graph graph;
    Coords toCheck[8] = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1} };
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] >= 48 && map[i][j] <= 90) {
                name+=(map[i][j]);
                if(location==invalid)
                    for (int c = 0; c < 8; c++) {
                        if(i+toCheck[c].y<map.size() && j+toCheck[c].x<map[i].size() && i + toCheck[c].y >= 0 && j + toCheck[c].x >= 0)
                            if (map[i + toCheck[c].y][j + toCheck[c].x] == '*') {
                                location = { i + toCheck[c].y,j + toCheck[c].x };
					        }
				    }
			}
            else if (name.size()){
                graph.AddCity(name, location);
                location = invalid;
                name.Clear();
            }
		}
	}
    int flights = read().ToInt();
    for (int i = 0; i < flights; i++) {
        String loc = read();
        String dest = read();
        int time = read().ToInt();
        graph.AddFlight(loc, dest, time);
        //printf("%s -> %s: %d\n", loc.ToValidString(), dest.ToValidString(), time);
    }
    graph.ParseAdjMatrix(map);
    int queries = read().ToInt();
    for (int i = 0; i < queries; i++) {
		String from = read();
		String to = read();
        bool showPath = (read().ToInt() == 1);
		graph.PrintShortestPath(map, from, to, showPath);
        continue;
	}

    return 0;
}

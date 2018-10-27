#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "graph.hpp"
#include "graphreader.hpp"

void driver()
{
    Graph gp;
    gp.addVertex("a");
    gp.addVertex("b");
    gp.addVertex("c");
    gp.addVertex("d");
    gp.addVertex("e");

    gp.addEdge("a", "b", 12);
    gp.addEdge("a", "c", 12);
    gp.addEdge("c", "a", 12);
    gp.addEdge("d", "f", 12);

    gp.bfs("a");
}

void driverReader()
{
    std::string filename = "connlist.txt";
    GraphReader rdr(filename);
    Graph graph(rdr);
    graph.printGraph();
}

int main()
{
    driverReader();
    return 0;
}

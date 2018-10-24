#include <iostream>
#include "graph.hpp"

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

int main()
{
    driver();
    return 0;
}

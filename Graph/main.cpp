#include <iostream>
#include <map>
#include "Graph.h"

using namespace std;

int main() {
    Graph<int> graph;
    graph.add_connection(1, 2, 7);
    graph.add_connection(1, 4, 2);
    graph.add_connection(1, 6, 4);

    graph.add_connection(2, 4, 2);
    graph.add_connection(2, 3, 1);

    graph.add_connection(3, 4, 2);
    graph.add_connection(3, 5, 3);

    graph.add_connection(4, 5, 6);
    graph.add_connection(4, 6, 1);

    graph.add_connection(5, 6, 8);

    cout << graph.to_graphviz("Original") << endl << endl << graph.prim().to_graphviz("Prim");
    return 0;
}

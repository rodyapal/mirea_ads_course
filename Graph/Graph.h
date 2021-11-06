//
// Created by Rodya on 06.11.2021.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <map>
#include <string>
#include <vector>
#include <algorithm>

template<class Type>
class Graph {
private:
    using Connections = std::map<Type, size_t>;

    std::map<Type, Connections> data;
public:

    void add_connection(const Type &first, const Type &second, const size_t &length) {
        data[first][second] = length;
        data[second][first] = length;
    }

    Graph<Type> prim() {
        Graph<Type> result;
        std::vector<Type> selected;
        selected.push_back(data.begin()->first);
		while (selected.size() < data.size()) {
			Type min_node_first, min_node_second; size_t min_size = INT64_MAX;
			for (const auto& [first_node, first_connections] : data) {
				if (std::find(selected.begin(), selected.end(), first_node) != selected.end()) {
					for (const auto& [second_node, connection_size] : first_connections) {
						if (std::find(selected.begin(), selected.end(), second_node) == selected.end() &&
							data[first_node].find(second_node) != data[first_node].end()) { // not in selected and there is a min_connection
							if (connection_size < min_size) {
								min_size = connection_size;
								min_node_first = first_node;
								min_node_second = second_node;
							}
						}
					}
				}
			}
			result.add_connection(min_node_first, min_node_second, min_size);
			selected.push_back(min_node_second);
		}
        return result;
    }

	std::string to_graphviz(const std::string& title = "Data") {
		std::string result = "graph " + title + " {\n";
		std::vector<Type> done;
		for (const auto&[node, connections]: data) {
			for (const auto&[connection_node, connection_size]: connections) {
				if (std::find(done.begin(), done.end(), connection_node) == done.end()) {
					result += "\"" + std::to_string(node) + "\" -- \""
							  + std::to_string(connection_node)
							  + "\" [label=\"" + std::to_string(connection_size) + "\"]\n";
				}
			}
			done.push_back(node);
		}
		result += "}";
		return result;
	}
};


#endif //GRAPH_GRAPH_H

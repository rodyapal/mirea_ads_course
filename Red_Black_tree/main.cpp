#include <iostream>
#include <vector>
#include <string>
#include "StringRBtree.h"

using namespace std;

int main() {
	vector<string> cities = {"Moscow", "Berlin", "Krakov",
							 "London", "Beijin", "Madrid",
							 "Constantinople", "Rome", "Ephesus",
							 "Carthage"};
	StringRBtree tree;
	cout << tree.height() << endl;
	for (const auto& city : cities) {
		tree.insert(city);
	}
	cout << tree.to_graphviz() << endl << tree.concatenate_leaves() << endl;
	tree.direct_traversal(
		[](std::string& city) {
			city[0] = tolower(city[0]);
		}
	);
	cout << tree.to_graphviz() << endl;
	tree.symmetrical_traversal(
			[](std::string& city) {
				city[0] = toupper(city[0]);
			}
	);
	cout << tree.to_graphviz() << endl << tree.height() << endl;
	return 0;
}

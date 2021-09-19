#include <iostream>
#include <vector>
#include <functional>
#include "hash_table.h"

using namespace std;

int hashFunction(const int& key) {
	return key % 7;
}

int main() {
	HashTable<int, Reader, std::function<int(const int&)> > table(4, hashFunction);
	const size_t size = 10;
	for (int i = 0; i < size; i++) {
		table.insert(i, Reader{i, "NAME", "ADDRESS"});
	}
	for (int i = 0; i < size; i++) {
		cout << table[i].toString() << endl;
	}
	table.erase(5);
	cout << "---------------------" << endl;
	for (int i = 0; i < size; i++) {
		try {
			cout << table[i].toString() << endl;
		} catch (exception& e) {
			cerr << e.what() << endl;
		}

	}
    return 0;
}

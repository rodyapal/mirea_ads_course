//
// Created by Rodya on 08.09.2021.
//

#ifndef TWO_H
#define TWO_H

#include <iostream>
#include <bitset>
#include <vector>

namespace taskTwo {
	void a() {
		int size, number = 0, result = 0;
		std::cout << "Size of number sequence [1, 7]: ";
		std::cin >> size;
		std::cout << "Sequence: ";
		for (int i = 0; i < size; i++) {
			std::cin >> number;
			result += (1 << number);
		}
		std::cout << std::bitset<8>(result) << std::endl;
	}

	void b() {
		int size, number = 0;
		unsigned long long result = 0;
		std::cout << "Size of number sequence [1, 63]: ";
		std::cin >> size;
		std::cout << "Sequence: ";
		for (int i = 0; i < size; i++) {
			std::cin >> number;
			result += ((unsigned long long)(1) << number);
		}
		std::cout << std::bitset<64>(result) << std::endl;
	}

	void c() {
		std::vector<bool> data;
		int size, number = 0;
		std::cout << "Size of number sequence: ";
		std::cin >> size;
		std::cout << "Sequence: ";
		for (int i = 0; i < size; i++) {
			std::cin >> number;
			if (number < data.size()) {
				data[number] = true;
			}
			else {
				for (auto filler = data.size(); filler < number; filler++) {
					data.push_back(false);
				}
				data.push_back(true);
			}
		}
		for (int bitIndex = data.size() - 1; bitIndex >= 0; bitIndex--) {
			std::cout << (int)data[bitIndex];
		}
		std::cout << std::endl;
	}
}

void runTaskTwo() {
	taskTwo::a();
	taskTwo::b();
	taskTwo::c();
}

#endif //TWO_H

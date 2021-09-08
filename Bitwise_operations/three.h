//
// Created by Rodya on 08.09.2021.
//

#ifndef THREE_H
#define THREE_H

#include <random>
#include <fstream>
#include <vector>
#include <map>

namespace taskThree {

	const int MAX_NUMBERS_IN_FILE = 9'000'000;
	const int NUMBER_LOWER_THRESHOLD = 1'000'000;
	const int NUMBER_UPPER_THRESHOLD = 9'999'999;

	void generateFile() {
		std::random_device randomDevice;
		std::default_random_engine generator(randomDevice());
		std::uniform_int_distribution<int> mainDistribution(NUMBER_LOWER_THRESHOLD, NUMBER_UPPER_THRESHOLD);
		std::uniform_int_distribution<int> supportDistribution(0, MAX_NUMBERS_IN_FILE);
		int numbersInFile = supportDistribution(generator);

		std::ofstream stream("random_numbers.txt");
		if (stream.is_open()) {
			std::map<int, bool> savedNumbers;
			int randomNumber; bool notUnique;
			for (auto numberIndex = 0; numberIndex < numbersInFile; numberIndex++) {
				do {
					randomNumber = mainDistribution(generator);
					notUnique = savedNumbers[randomNumber];
				} while (notUnique);
				savedNumbers[randomNumber] = true;
				stream << randomNumber << " ";
			}
		} else {
			std::cerr << "[generateFile]: random_numbers.txt is not opened\n";
		}
		stream.close();
	}

	void readFile(std::vector<bool>& data) {
		std::ifstream input("random_numbers.txt");
		if (input.is_open()) {
			int number;
			while (!input.eof()) {
				input >> number;
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
		} else {
			std::cerr << "[readFile]: random_numbers.txt is not opened\n";
		}
		input.close();
	}
}

void runTaskThree() {
	std::vector<bool> data;
	taskThree::generateFile();
	taskThree::readFile(data);
	std::ofstream output("output.txt");
	if (output.is_open()) {
		for (int index = 0; index < data.size(); index++) {
			if (data[index]) output << index << " ";
		}
	} else {
		std::cerr << "[taskThree]: output.txt is not opened\n";
	}
	output.close();
}

#endif //THREE_H

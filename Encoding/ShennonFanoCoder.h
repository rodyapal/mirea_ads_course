//
// Created by Rodya on 28.11.2021.
//

#ifndef ENCODING_SHENNONFANOCODER_H
#define ENCODING_SHENNONFANOCODER_H
#include <map>
#include <vector>
#include <string>
#include <algorithm>

class ShennonFanoCoder {
private:
	std::map<char, Bits> codes; //Character - its code

	std::string source;

	static std::string symbol_to_str(const char& char_symbol) {
		std::string symbol = std::string(1, char_symbol);
		if (char_symbol == '\0') symbol = "NULL";
		else if (char_symbol == ' ') symbol = "space";
		else if (char_symbol == '\n') symbol = "line break";
		return symbol;
	}

	void set_char_codes(std::vector<std::pair<char, int>> occurrences, Bits path) {
		if (occurrences.size() == 1) {
			codes[occurrences[0].first] = path;
			return;
		}

		int full_probability = 0;
		for (const auto& [symbol, probability] : occurrences) {
			full_probability += probability;
		}
		std::sort(occurrences.rbegin(), occurrences.rend(),
				  [](const std::pair<char, int>& left, const std::pair<char, int>& right) {
							return left.second < right.second;
						}
		);
		std::vector<std::pair<char, int>> left, right;
		int left_probability = 0, right_probability = 0;
		for (const auto& [symbol, probability] : occurrences) {
			if (left_probability < full_probability / 2) {
				left.emplace_back(symbol, probability);
				left_probability += probability;
			} else {
				right.emplace_back(symbol, probability);
				right_probability += probability;
			}
		}
		auto left_path = path + (Bits){0};
		auto right_path = path + (Bits){1};
		set_char_codes(left, left_path);
		set_char_codes(right, right_path);
	}

public:

	static ShennonFanoCoder from(const std::string& filename) {
		std::ifstream file(filename);
		if (!file) {
			std::cerr << "File is not available\n";
			std::terminate();
		}
		std::string file_data, line;
		while (std::getline(file, line)) {
			file_data += line + "\n";
		}
		return ShennonFanoCoder(file_data);
	}

	explicit ShennonFanoCoder(const std::string& source) {
		this->source = source;
		build_codes_table(source);
	}

	void build_codes_table(const std::string &source) {
		this->source = source;
		std::map<char, int> occurrences;
		for (const auto &symbol: source) {
			occurrences[symbol]++;
		}
		set_char_codes(to_vector(occurrences), {});
	}

	void print_codes(std::ostream& stream = std::cout) const {
		for (const auto& [symbol , code] : codes) {
			stream << symbol_to_str(symbol) << " : ";
			for (const auto& bit : code) {
				stream << bit;
			}
			stream << std::endl;
		}
	}

	Bits encode() {
		Bits result;
		for (const auto& symbol : source) {
			result = (result + (Bits)codes[symbol]);
		}
		return result;
	}

	std::string decode(Bits binary) {
		std::reverse(binary.begin(), binary.end());
		auto binary_codes = flip_map(codes);
		std::string result; Bits symbol_code;
		while (!binary.empty()) {
			symbol_code.push_back(binary.back());
			binary.erase(binary.end() - 1);

			if (binary_codes.find(symbol_code) != binary_codes.end()) { //Contains
				result += binary_codes[symbol_code];
				symbol_code.clear();
			}
		}
		return result;
	}
};
#endif //ENCODING_SHENNONFANOCODER_H
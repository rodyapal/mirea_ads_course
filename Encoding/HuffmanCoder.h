//
// Created by Rodya on 23.11.2021.
//

#ifndef ENCODING_HUFFMANCODER_H
#define ENCODING_HUFFMANCODER_H

#include "utils.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <list>
#include <memory>
#include <fstream>

class HuffmanCoder {
private:
	std::map<char, Bits> codes; //Character - its code

	std::string source;

	struct Node {
		char symbol = '\0';
		int occurrence = -1;
		std::shared_ptr<Node> left = nullptr, right = nullptr;
	};

	[[nodiscard]] static std::shared_ptr<Node> build_tree(const std::map<char, int>& occurrences) {
		std::list<std::shared_ptr<Node>> nodes;
		for (const auto& [symbol, occurrence_amount] : occurrences) {
			nodes.push_back(std::make_shared<Node>(Node{symbol, occurrence_amount}));
		}
		nodes.sort([](const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right){
			return left->occurrence < right->occurrence;
		});
		while (nodes.size() > 1) {
			auto left = nodes.front();
			nodes.pop_front();
			auto right = nodes.front();
			nodes.pop_front();

			nodes.push_back(std::make_shared<Node>(Node{'\0', right->occurrence + left->occurrence, left, right}));
			nodes.sort([](const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right){
				return left->occurrence < right->occurrence;
			});
		}
		return nodes.front();
	}

	void set_char_codes(const std::shared_ptr<Node>& node, const std::vector<bool>& code) {
		if (node == nullptr) return;

		if (node->left == nullptr && node->right == nullptr) {
			codes[node->symbol] = code;
		} else {
			auto left = code; left.push_back(false);
			auto right = code; right.push_back(true);
			set_char_codes(node->left, left);
			set_char_codes(node->right, right);
		}
	}

	static std::string symbol_to_str(const char& char_symbol) {
		std::string symbol = std::string(1, char_symbol);
		if (char_symbol == '\0') symbol = "NULL";
		else if (char_symbol == ' ') symbol = "space";
		else if (char_symbol == '\n') symbol = "line break";
		return symbol;
	}

	void print_tree(const std::shared_ptr<Node>& node, std::string& description, const Bits& path) {
		if (node == nullptr)
			return;
		std::string symbol = symbol_to_str(node->symbol);
		auto zero = path + (Bits){0};
		auto one = path + (Bits){1};
		if (node->left != nullptr) {
			std::string symbol_left = symbol_to_str(node->left->symbol);
			description += "\"" + symbol + " " + to_string(path) + "\" -> \""
						   + symbol_left + " " + to_string(zero) + "\"[label=0];\n";
		}
		if (node->right != nullptr) {
			std::string symbol_right = symbol_to_str(node->right->symbol);
			description += "\"" + symbol + " " + to_string(path) + "\" -> \""
						   + symbol_right + " " + to_string(one) + "\"[label=1];\n";
		}
		print_tree(node->left, description, zero);
		print_tree(node->right, description, one);
	}

	void print_tree(const std::shared_ptr<Node>& head) {
		std::string result = "digraph Tree {\n";
		print_tree(head, result, {});
		result += "}\n";
		std::cout << result;
	}

public:

	static HuffmanCoder from(const std::string& filename) {
		std::ifstream file(filename);
		if (!file) {
			std::cerr << "File is not available\n";
			std::terminate();
		}
		std::string file_data, line;
		while (std::getline(file, line)) {
			file_data += line + "\n";
		}
		return HuffmanCoder(file_data);
	}

	explicit HuffmanCoder(const std::string& source) {
		this->source = source;
		build_codes_table(source);
	}

	void build_codes_table(const std::string &source) {
		this->source = source;
		std::map<char, int> occurrences;
		for (const auto &symbol: source) {
			occurrences[symbol]++;
		}
		auto head = build_tree(occurrences);
		set_char_codes(head, {});
		print_tree(head);
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

#endif //ENCODING_HUFFMANCODER_H

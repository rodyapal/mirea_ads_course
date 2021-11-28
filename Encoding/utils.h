//
// Created by Rodya on 28.11.2021.
//

#ifndef ENCODING_UTILS_H
#define ENCODING_UTILS_H
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <algorithm>

template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B> &p) {
	return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::map<B, A> flip_map(const std::map<A, B> &src) {
	std::map<B, A> dst;
	std::transform(
			src.begin(), src.end(),
			std::inserter(dst, dst.begin()),
			flip_pair<A, B>
	);
	return dst;
}

template<typename A, typename B>
std::vector<std::pair<A, B>> to_vector(const std::map<A, B> &src) {
	return std::vector<std::pair<A, B>>(src.begin(),  src.end());
}

using Bits = std::vector<bool>;
using Byte = unsigned char;

Bits operator+(const Bits& left, const Bits& right) {
	Bits result;
	result.reserve(left.size() + right.size());
	for (const auto& item : left) result.push_back(item);
	for (const auto& item : right) result.push_back(item);
	return result;
}

std::vector<Bits> chunks(const Bits& bits) {
	Bits buffer; std::vector<Bits> result;
	buffer.reserve(8);
	for (const auto& bit : bits) {
		buffer.push_back(bit);
		if (buffer.size() == 8) {
			result.push_back(buffer);
			buffer.clear();
		}
	}
	return result;
}

std::vector<Byte> to_byte(const std::vector<Bits>& chunks) {
	std::vector<Byte> bytes;
	bytes.reserve(chunks.size());
	for (const auto& chunk : chunks) {
		Byte byte = (Byte)0;
		for (size_t index = 0; index < chunk.size(); index++) {
			byte += (Byte)(chunk[index] << (chunk.size() - index - 1));
		}
		bytes.push_back(byte);
	}
	return bytes;
}

std::string to_string(const Bits& bits) {
	std::string result;
	for (const auto& bit : bits) {
		result += std::to_string(bit);
	}
	return result;
}

#endif //ENCODING_UTILS_H
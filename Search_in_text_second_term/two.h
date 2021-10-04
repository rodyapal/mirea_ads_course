//
// Created by Rodya on 29.09.2021.
//

#ifndef TWO_H
#define TWO_H

#include <algorithm>

std::vector<size_t> prefixFunction(const std::string& str) {
	std::vector<size_t> prefixes(str.length(), 0);
	for (size_t current = 1; current < str.length(); current++) {
		size_t previous = prefixes[current - 1];

		while ((previous > 0) && (str[current] != str[previous]))
			previous = prefixes[previous - 1];

		if (str[current] == str[previous])
			previous++;

		prefixes[current] = previous;
	}
	return prefixes;
}

size_t maxPrefix(const std::string& a, const std::string& b) {
	auto prefixes = prefixFunction(a + '\0' + b);
	return *std::max_element(prefixes.begin(),  prefixes.end());
}

#endif //TWO_H

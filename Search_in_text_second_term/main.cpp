#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using StringVector = std::vector<std::string>;
using StringMap = std::map<std::string, StringVector>;

std::ostream& operator<<(std::ostream& stream, const StringMap& data) {
    for (const auto& [word, reversedWords] : data) {
        stream << word << " : { ";
        for (const auto& reversedWord : reversedWords) {
            stream << reversedWord << " ";
        }
        stream << "}\n";
    }
    return stream;
}

bool isReversed(const std::string& lhs, const std::string& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (int index = 0; index < lhs.size(); index++)
        if (lhs[index] != rhs[rhs.size() - index - 1])
            return false;
    return true;
}

StringVector split(const std::string& str) {
    std::stringstream stream(str);
    std::string buffer; StringVector result;
    while (stream >> buffer) {
        if (buffer[buffer.length() - 1] == ',')
            result.push_back(std::string(buffer.begin(), std::prev(buffer.end())));
        else
            result.push_back(buffer);
    }
    return result;
}

void printReversedWords(const std::string& sentence) {
    auto words = split(sentence);
    StringMap reversedWords;
    for (int mainWordIndex = 0; mainWordIndex < words.size(); mainWordIndex++) {
        for (int compareWordIndex = mainWordIndex + 1; compareWordIndex < words.size(); compareWordIndex++) {
            if (isReversed(words[mainWordIndex], words[compareWordIndex])) {
                reversedWords[words[mainWordIndex]].push_back(words[compareWordIndex]);
            }
        }
    }
    std::cout << reversedWords;
}

int main() {
    printReversedWords("asdf, gdfsh, wertwert twettwl labjdfjh dgj jgd eywerti jgd uyq gjsd, qyu, dgj");
    return 0;
}

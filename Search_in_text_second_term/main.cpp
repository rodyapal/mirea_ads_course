#include "one.h"
#include "two.h"

void testReversedWords() {
	printReversedWords("aaab, qwert yuiop, baaa");
	printReversedWords("aboba, warp, data is here, aboba, aboba, praw");
	printReversedWords("aboba, warp, data is here");
    printReversedWords("aboba");
    printReversedWords("a a b");
}

void testPrefix() {
	std::cout << maxPrefix("aabaa", "aabaabaaaabaabaaab") << std::endl <<
        maxPrefix("aaaaba", "aa") << std::endl <<
		maxPrefix("", "aabaabaaaabaabaaab") << std::endl <<
		maxPrefix("baa", "aabaabaaaabaabaaab") << std::endl <<
		maxPrefix("vaa", "aabaabaaaabaabaaab") << std::endl;
}

int main() {
    testReversedWords();
	testPrefix();
    return 0;
}

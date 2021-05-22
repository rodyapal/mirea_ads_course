#include <iostream>
#include "LinkedList.h"
using namespace std;

int digitalRootIterative(int number) {
	while (number > 9) {
		int sum = 0;
		while (number > 0) {
			sum += number % 10;
			number /= 10;
		}
		number = sum;
	}
	return number;
}

int digitalRootRecursive(int number) {
	int sum = 0;
	while (number > 0) {
		sum += number % 10;
		number /= 10;
	}
	if (sum > 9) return digitalRootRecursive(sum);
	else return sum;
}

int countEven(LinkedList<int>::Node *node, int count = 0) {
	if (node->data % 2 == 0) {
		count++;
	}
	if (node->next == nullptr) return count;
	else return countEven(node->next, count);
}

int main() {
	cout << "digitalRootIterative(12345) = "
		 << digitalRootIterative(12345) << endl
		 << "digitalRootRecursive(12345) = "
		 << digitalRootRecursive(12345) << endl;
	LinkedList<int> list;
	for (int i = 0; i < 10; i++) list.push_front(i);
	cout << "List: " << list << endl << "countEven(list): " << countEven(list.get_head());
	return 0;
}
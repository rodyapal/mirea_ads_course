//
// Created by Rodya on 04.05.2021.
//

#ifndef RECURSIVE_FUNCTIONS_CPP_LINKEDLIST_H
#define RECURSIVE_FUNCTIONS_CPP_LINKEDLIST_H

#include <iostream>
#include <vector>

template<class Type>
class LinkedList {
public:
	struct Node {

		Type data;

		Node *next = nullptr;
		Node *prev = nullptr;

		bool operator==(const Node &other) const {
			return data == other.data;
		}
	};

	~LinkedList() {
		clear();
	}

	void push_front(const Type &data) {
		auto node = new Node{data};
		node->next = head;
		if (head != nullptr) head->prev = node;
		node->prev = nullptr;
		head = node;
	}

	void push_front(Node *node) {
		if (node->next == nullptr) {
			push_front(node->data);
		} else {
			auto item = node;
			while (item->next != nullptr) item = item->next;
			item->next = head;
			head->prev = nullptr;
			head = node;
		}
	}

	void insert_after(Node *node, const Type &data) {
		if (node) {
			auto new_node = new Node{data};
			new_node->next = node->next;
			new_node->prev = node;
			node->next->prev = new_node;
			node->next = new_node;
		} else {
			push_front(data);
		}
	}

	void insert_before(Node *node, const Type &data) {
		if (node) {
			auto new_node = new Node{data};
			new_node->prev = node->prev;
			new_node->next = node;
			node->prev->next = new_node;
			node->prev = new_node;
		} else {
			push_front(data);
		}
	}

	void remove_after(Node *node) {
		if (!node) {
			pop_front();
		} else if (node->next) {
			auto removing_node = node->next;
			node->next = removing_node->next;
			removing_node->next->prev = node;
			delete removing_node;
		}
	}

	void remove_before(Node *node) {
		if (!node) {
			pop_front();
		} else if (node->next) {
			auto removing_node = node->prev;
			node->prev = removing_node->prev;
			removing_node->prev->next = node;
			delete removing_node;
		}
	}

	template<class Predicate>
	void remove_after_while(Node *node, Predicate predicate) {
		while (predicate(node)) remove_after(node);
	}

	void pop_front() {
		if (head) {
			Node *new_head = head->next;
			delete head;
			head->prev = nullptr;
			head = new_head;
		}
	}

	[[nodiscard]]
	Node *find_last(const Type &data) const {
		Node *last_item = nullptr;
		for (auto item = head; item != nullptr; item = item->next)
			if (item->data == data) last_item = item;
		return last_item;
	}

	template<class Predicate>
	[[nodiscard]]
	Node *find_first(const Type &data, Predicate predicate, Node *start = nullptr) const {
		for (auto item = start != nullptr ? start : head; item != nullptr; item = item->next)
			if (predicate(item->data, data)) return item;
		return nullptr;
	}

	[[nodiscard]]
	Node *find_first(const Type &data, Node *start = nullptr) const {
		for (auto item = start != nullptr ? start : head; item != nullptr; item = item->next)
			if (item->data == data) return item;
		return nullptr;
	}

	[[nodiscard]]
	Node *find_ordinal(const Type &data, const size_t &ordinal) const {
		Node *item = nullptr;
		for (int index = 0; index < ordinal; index++) {
			item = find_first(data, item != nullptr ? item->next : item);
		}
		return item;
	}

	[[nodiscard]]
	Node *get_back() const {
		auto item = head;
		while (item->next != nullptr) item = item->next;
		return item;
	}

	[[nodiscard]]
	Node *get_head() const {
		return head;
	}

	void reverse_list() {
		std::vector<Type> values;
		for (auto item = head; item != nullptr; item = item->next)
			values.push_back(item->data);
		clear();
		for (const auto &item : values) {
			push_front(item);
		}
	}

private:
	void clear() {
		while (head) {
			pop_front();
		}
	}

	Node *head = nullptr;
};

template<class Type>
std::ostream &operator<<(std::ostream &stream, const LinkedList<Type>& list) {
	for (auto item = list.get_head(); item != nullptr; item = item->next) stream << item->data << " ";
	return stream;
}

#endif //RECURSIVE_FUNCTIONS_CPP_LINKEDLIST_H

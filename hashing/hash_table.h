//
// Created by Rodya on 16.09.2021.
//
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <iostream>
#include <string>
#include <exception>

struct Reader {
    int id{-1};
    std::string name{};
    std::string address{};

	std::string toString() const {
		return "Reader(id=" + std::to_string(id) + ",name=" + name + ",address=" + address +")";
	}
};

enum class TableEntityState {
	FREE,
	IN_USE
};

template<typename Key_, typename Value_>
struct TableEntity {
	Key_ key;
	Value_ value;
	TableEntityState state = TableEntityState::FREE;
};

template<typename Key, typename Value, typename Hash>
class HashTable {
private:
	using Table = TableEntity<Key, Value>*;
	size_t capacity{};
	size_t size{};

	Table table;
	Hash hashFunc;

	size_t getIndex(const Key& key, const size_t& modulus) const {
		return hashFunc(key) % modulus;
	}

	size_t squareGetIndex(const Key& key, const size_t& constant, const size_t& modulus) const {
		return (hashFunc(key) + (constant + constant * constant) / 2) % modulus;
	}

	void rehash() {
		size_t newCapacity = capacity * 2;

		auto* newTable = new TableEntity<Key, Value>[newCapacity];
		for (size_t i = 0; i < newCapacity; i++) {
			newTable[i] = TableEntity<Key, Value>();
		}

		for (size_t i = 0; i < capacity; i++)
			if (table[i].state == TableEntityState::IN_USE) {
				insert(table[i].key, table[i].value, newTable,  newCapacity);
			}

		delete[] table;

		table = newTable;
		capacity = newCapacity;
	}

	size_t insert(const Key& key_, const Value& value_, Table table_, size_t capacity_) {
		size_t index = getIndex(key_, capacity_);
		for (size_t constant = 1; table_[index].state == TableEntityState::IN_USE; constant++) {
			index = squareGetIndex(key_, constant, capacity_);
		}
		table_[index].key = key_;
		table_[index].value = value_;
		table_[index].state = TableEntityState::IN_USE;
		return index;
	}

public:

	explicit HashTable(size_t capacity, Hash hashFunction)
		: capacity(capacity), size(0), hashFunc(hashFunction)
	{
		table = new TableEntity<Key,Value>[capacity];

		for (size_t i = 0; i < capacity; i++) {
			table[i] = TableEntity<Key, Value>();
		}
	}

	size_t insert(const Key& key, const Value& value) {
		if (size * 2 > capacity) {
			rehash();
		}
		size++;
		return insert(key, value, table, capacity);
	}

	void erase(const Key& key) {
		size_t index = getIndex(key, capacity);
		for (size_t constant = 1; key != table[index].key; constant++) {
			index = squareGetIndex(key, constant, capacity);
		}
		table[index].state = TableEntityState::FREE;
		size--;
	}

	Value& operator[] (const Key& key) const {
		size_t index = getIndex(key, capacity);
		std::vector<bool> indexes(capacity, false);
		for (size_t constant = 1; key != table[index].key; constant++) {
			indexes[index] = true;
			index = squareGetIndex(key, constant, capacity);
			if (std::find(indexes.begin(), indexes.end(), false) == indexes.end())
				throw std::invalid_argument("No entity with given index");
		}
		if (table[index].state == TableEntityState::IN_USE) return table[index].value;
		throw std::invalid_argument("Entity was erased");
	}

	size_t getSize() const {
		return size;
	}

	size_t getCapacity() const {
		return capacity;
	}

	~HashTable() {
		delete[] table;
	}
};

#endif //HASH_TABLE_H

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

/**
 * Hash table with quadratic probing
 * @tparam Key - type of key for hash function
 * @tparam Value - type of stored values
 * @tparam Hash - signature of hash function
 */
template<typename Key, typename Value, typename Hash>
class HashTable {
private:

	enum class TableEntityState {
		FREE,
		IN_USE
	};

	struct TableEntity {
		Key key;
		Value value;
		TableEntityState state = TableEntityState::FREE;
	};

	using Table = TableEntity*;
	size_t capacity{};
	size_t size{};
	size_t itemsInUse{};

	Table table;
	Hash hashFunc;

	/**
	 *	Get item index in table
	 * @param key - key of a table entity for hash function
	 * @param modulus - value the result of a hash function will be divided on. Mostly table capacity
	 * @return index of item in table
	 */
	size_t getIndex(const Key& key, const size_t& modulus) const {
		return hashFunc(key) % modulus;
	}

	/**
	 *	Get item index in table if getIndex() value if occupied
	 * @param key - key of a table entity for hash function
	 * @param constant - step of quadratic probing
	 * @param modulus - value the result of a hash function will be divided on. Mostly table capacity
	 * @return index of item in table depending on given constant
	 */
	size_t squareGetIndex(const Key& key, const size_t& constant, const size_t& modulus) const {
		return (hashFunc(key) + (constant + constant * constant) / 2) % modulus;
	}

	/**
	 * Rebuilds the table with doubled capacity
	 */
	void rehash() {
		size_t newCapacity = capacity * 2;

		auto* newTable = new TableEntity[newCapacity];
		for (size_t i = 0; i < newCapacity; i++) {
			newTable[i] = TableEntity();
		}

		for (size_t i = 0; i < capacity; i++)
			if (table[i].state == TableEntityState::IN_USE) {
				insert(table[i].key, table[i].value, newTable,  newCapacity);
			}

		delete[] table;

		table = newTable;
		capacity = newCapacity;
	}

	/**
	 * Inserts a key-value pair into the given table
	 * @param key_ - key of a table entity for hash function
	 * @param value_ - value to be stored in table
	 * @param table_ - hash table where key-value pairs stored
	 * @param capacity_ - capacity of the given table
	 * @return index of the key-value pair in table
	 */
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
		: capacity(capacity), size(0), itemsInUse(0), hashFunc(hashFunction)
	{
		table = new TableEntity[capacity];

		for (size_t i = 0; i < capacity; i++) {
			table[i] = TableEntity();
		}
	}

	/**
	 * Inserts a key-value pair into the table
	 * @param key - key of a table entity for hash function
	 * @param value - value to be stored in table
	 * @return index of the key-value pair in table
	 */
	size_t insert(const Key& key, const Value& value) {
		if (size * 2 > capacity) {
			rehash();
		}
		size++;
		itemsInUse++;
		return insert(key, value, table, capacity);
	}

	/**
	 * Erases the key-value pair from table
	 * @param key - key of a table entity for hash function
	 */
	void erase(const Key& key) {
		size_t index = getIndex(key, capacity);
		for (size_t constant = 1; key != table[index].key; constant++) {
			index = squareGetIndex(key, constant, capacity);
		}
		table[index].state = TableEntityState::FREE;
		itemsInUse--;
	}

	/**
	 * Get the value by index
	 * @param key - key of a table entity for hash function
	 * @return stored value
	 * @throws invalid_argument when item with given key was deleted or not present in table
	 */
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

	/**
	 * @return items in use + items that were erased
	 */
	size_t getSize() const {
		return size;
	}

	/**
	 * @return amount of items items in use
	 */
	size_t getItemsInUse() const {
		return itemsInUse;
	}

	/**
	 * @return total capacity of the table
	 */
	size_t getCapacity() const {
		return capacity;
	}

	~HashTable() {
		delete[] table;
	}
};

template<typename Hash>
std::ostream& operator<<(std::ostream& stream, const HashTable<int, Reader, Hash>& data) {
	for (int i = 0; i < data.getSize(); i++) {
		try {
			stream << data[i].toString() << std::endl;
		} catch (std::exception& e) {}
	}
	return stream;
}

#endif //HASH_TABLE_H
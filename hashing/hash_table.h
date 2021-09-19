//
// Created by Rodya on 16.09.2021.
//
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>

class Hashable {
public:
    virtual int getIndex() const = 0;
};

struct Reader : Hashable {
    int id{};
    std::string name{};
    std::string address{};

    int getIndex() const override {
        return id;
    }
};

template <class Hashable>
class hash_table {
private:
    std::vector<Hashable> data;

    int hash(const int& key) {
        return key % data.size();
    }

public:
    void insert(const Hashable& item) {
        int index = hash(item.getIndex());
        if (index + 1 >= data.size()) {
            data.resize(data.size() + index)
        }
    }

    void erase(const Hashable& item) {

    }

    void find(const int& index) {

    }

    Type operator[] (const int& index) {

    }

    void size() const {
        return data.size();
    }
};

template<class Hashable>
ostream& operator<<(std::ostream& stream, const hash_table<Hasheble>& data) {

}

#endif //HASH_TABLE_H

#pragma once

#include <array> // std::array
#include <functional> // std::hash
#include <list> // std::list
#include <iostream> // std::ostream, std::clog
#include <utility> // std::pair

#include "hash_table.hpp"

template <class Key, class Value, class Hash = std::hash<Key> >
class ChainingHashTable : public HashTable<Key, Value, Hash> {
private:
    std::array<
        std::list<std::pair<Key, Value> >,
        HashTable<Key, Value, Hash> ::NUM_BUCKETS
    > table;

public:
    void emplace(const Key& key, const Value& value) override {
        size_t index = HashTable<Key, Value, Hash> ::calculate_index(key);
        std::clog << "Hash for '" << key << "': " << index << std::endl;
        table[index].emplace_back(key, value);
    }

    Value& at(const Key& key) override {
        size_t index = HashTable<Key, Value, Hash> ::calculate_index(key);
        std::clog << "Hash for '" << key << "': " << index << std::endl;
        for (auto& [k, value] : table[index]) {
            if (k == key) {
                return value;
            }
        }
        throw "Key not Found in HashTable";
    }

    const Value& at(const Key& key) const override {
        return const_cast<const Value&>(
            const_cast<ChainingHashTable<Key, Value, Hash>*>(this)->at(key)
        );
    }

    template <class K, class V, class H>
    friend std::ostream& operator<<(std::ostream& o, const ChainingHashTable<K, V, H>& hash_table);
};

template <class Key, class Value, class Hash>
std::ostream& operator<<(std::ostream& o, const ChainingHashTable<Key, Value, Hash>& hash_table) {
    bool empty = true;
    for (size_t index = 0; index < HashTable<Key, Value, Hash> ::NUM_BUCKETS; ++index) {
        if(!hash_table.table[index].empty()) {
            if(!empty) {
                o << '\n';
            }
            o << "Index: " << index;
            for (const auto& [key, value] : hash_table.table[index]) {
                o << "\n\tKey: " << key << "\tValue: " << value;
            }
            empty = false;
        }
    }
    if (empty) {
        o << "Empty Hash Table";
    }
    return o;
}

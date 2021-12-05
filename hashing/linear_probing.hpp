#pragma once

#include <array> // std::array
#include <functional> // std::hash
#include <optional> // std::optional
#include <iostream> // std::ostream, std::clog
#include <utility> // std::pair

#include "hash_table.hpp"

template <class Key, class Value, class Hash = std::hash<Key> >
class LinearHashTable : public HashTable<Key, Value, Hash> {
private:
    std::array<
        std::optional<std::pair<Key, Value> >,
        HashTable<Key, Value, Hash> ::NUM_BUCKETS
    > table;

public:
    void emplace(const Key& key, const Value& value) override {
        size_t calculated_index = HashTable<Key, Value, Hash> ::calculate_index(key);
        std::clog << "Hash for '" << key << "': " << calculated_index << std::endl;
        size_t index = calculated_index;
        while (table[index] && table[index]->first != key) {
            // While there is a collision, linearly move forward
            index = (index + 1) % HashTable<Key, Value, Hash> ::NUM_BUCKETS;
            if(index == calculated_index) {
                throw "No Spaces in HashTable";
            }
        }
        table[index] = std::make_pair(key, value);
    }

    Value& at(const Key& key) override {
        size_t calculated_index = HashTable<Key, Value, Hash> ::calculate_index(key);
        std::clog << "Hash for '" << key << "': " << calculated_index << std::endl;
        size_t index = calculated_index;
        while (table[index]) {
            if(table[index]->first == key) {
                return table[index]->second;
            }
            // While there is a collision, linearly move forward
            index = (index + 1) % HashTable<Key, Value, Hash> ::NUM_BUCKETS;
            if(index == calculated_index) {
                break;
            }
        }
        throw "Key not Found in HashTable";
    }

    const Value& at(const Key& key) const override {
        return const_cast<const Value&>(
            const_cast<LinearHashTable<Key, Value, Hash>*>(this)->at(key)
        );
    }

    template <class K, class V, class H>
    friend std::ostream& operator<<(std::ostream& o, const LinearHashTable<K, V, H>& hash_table);
};

template <class Key, class Value, class Hash>
std::ostream& operator<<(std::ostream& o, const LinearHashTable<Key, Value, Hash>& hash_table) {
    bool empty = true;
    for (size_t index = 0; index < HashTable<Key, Value, Hash> ::NUM_BUCKETS; ++index) {
        if(hash_table.table[index]) {
            if(!empty) {
                o << '\n';
            }
            o << "Index: " << index << "\tKey: " << hash_table.table[index]->first << "\tValue: " << hash_table.table[index]->second;
            empty = false;
        }
    }
    if (empty) {
        o << "Empty Hash Table";
    }
    return o;
}

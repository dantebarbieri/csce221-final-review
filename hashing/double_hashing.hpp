#pragma once

#include <array> // std::array
#include <functional> // std::hash
#include <optional> // std::optional
#include <iostream> // std::ostream, std::clog
#include <utility> // std::pair

#include "hash_table.hpp"

template <typename T>
class SecondaryHash {
private:
    static constexpr size_t PRIME = 13;
    std::hash<T> primary_hash;

public:
    size_t operator()(const T& t) {
        // range from 1 to PRIME (important nonzero)
        return PRIME - (primary_hash(t) % PRIME);
    }
};

template <class Key, class Value, class Hash = std::hash<Key>, class DoubleHash = SecondaryHash<Key> >
class DoubleHashTable : public HashTable<Key, Value, Hash> {
private:
    std::array<
        std::optional<std::pair<Key, Value> >,
        HashTable<Key, Value, Hash> ::NUM_BUCKETS
    > table;
    DoubleHash secondary_hash_func;

public:
    void emplace(const Key& key, const Value& value) override {
        size_t calculated_index = HashTable<Key, Value, Hash> ::calculate_index(key);
        size_t offset = secondary_hash_func(key);
        std::clog << "Hash for '" << key << "': " << calculated_index << std::endl;
        std::clog << "Offset for '" << key << "': " << offset << std::endl;
        size_t index = calculated_index;
        for(
            size_t i = 0;
            i < HashTable<Key, Value, Hash> ::NUM_BUCKETS;
            ++i
        ) {
            index = (calculated_index + i * offset) % HashTable<Key, Value, Hash> ::NUM_BUCKETS;
            if(!table[index] || table[index]->first == key) {
                table[index] = std::make_pair(key, value);
                return;
            }
        }
        throw "No Spaces in HashTable";
    }

    Value& at(const Key& key) override {
        size_t calculated_index = HashTable<Key, Value, Hash> ::calculate_index(key);
        size_t offset = secondary_hash_func(key);
        std::clog << "Hash for '" << key << "': " << calculated_index << std::endl;
        std::clog << "Offset for '" << key << "': " << offset << std::endl;
        size_t index = calculated_index;
        for(
            size_t i = 0;
            i < HashTable<Key, Value, Hash> ::NUM_BUCKETS;
            ++i
        ) {
            index = (calculated_index + i * offset) % HashTable<Key, Value, Hash> ::NUM_BUCKETS;
            if(table[index] && table[index]->first == key) {
                return table[index]->second;
            }
        }
        throw "Key not Found in HashTable";
    }

    const Value& at(const Key& key) const override {
        return const_cast<const Value&>(
            const_cast<DoubleHashTable<Key, Value, Hash>*>(this)->at(key)
        );
    }

    template <class K, class V, class H>
    friend std::ostream& operator<<(std::ostream& o, const DoubleHashTable<K, V, H>& hash_table);
};

template <class Key, class Value, class Hash>
std::ostream& operator<<(std::ostream& o, const DoubleHashTable<Key, Value, Hash>& hash_table) {
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

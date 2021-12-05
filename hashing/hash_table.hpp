#pragma once

#include <cstddef>

template <class Key, class Value, class Hash>
class HashTable {
protected:
    Hash hash_func;
    static constexpr size_t NUM_BUCKETS = 7;
    size_t calculate_index(const Key& key) { return hash_func(key) % NUM_BUCKETS; }
    
public:
    virtual void emplace(const Key& key, const Value& value) = 0;
    virtual Value& at(const Key& key) = 0;
    virtual const Value& at(const Key& key) const = 0;
};

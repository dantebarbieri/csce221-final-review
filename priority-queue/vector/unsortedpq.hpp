#pragma once

#include <functional> // std::less
#include <ostream> // std::ostream
#include <vector> // std::vector

#include "../pq.hpp"

template <class T, class Compare = std::less<T> >
class UnsortedPQ : public PQ<T> {
private:
    Compare comp;
    std::vector<T> queue;
public:
    const T& top() const override {
        if (queue.empty()) {
            throw "No minimum in empty queue";
        }
        auto minimum_iterator = queue.begin();
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            if (comp(*it, *minimum_iterator)) {
                minimum_iterator = it;
            }
        }
        return *minimum_iterator;
    }

    void push(const T& data) override {
        queue.push_back(data);
    }

    void pop() override {
        if (queue.empty()) {
            throw "No minimum in empty queue";
        }
        size_t minimum_index = 0;
        for (size_t i = 0; i < queue.size(); ++i) {
            if (comp(queue[i], queue[minimum_index])) {
                minimum_index = i;
            }
        }
        queue.erase(queue.begin() + minimum_index);
    }

    template <class U, class C>
    friend std::ostream& operator<<(std::ostream& o, const UnsortedPQ<U, C>& pq);
};

template <class T, class Compare>
std::ostream& operator<<(std::ostream& o, const UnsortedPQ<T, Compare>& pq) {
    o << '[';
    for (const auto& e : pq.queue) {
        o << e;
        if(&e != &pq.queue.back()) {
            o << ", ";
        }
    }
    return o << ']';
}
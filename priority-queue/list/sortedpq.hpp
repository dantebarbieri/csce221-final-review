#pragma once

#include <functional> // std::less
#include <list> // std::list
#include <ostream> // std::ostream

#include "../pq.hpp"

template <class T, class Compare = std::less<T> >
class SortedPQ : public PQ<T> {
private:
    Compare comp;
    std::list<T> queue;
public:
    const T& top() const override {
        return queue.front();
    }

    void push(const T& data) override {
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            if (comp(data, *it)) {
                queue.insert(it, data);
                return;
            }
        }
        queue.push_back(data);
    }

    void pop() override {
        queue.pop_front();
    }

    template <class U, class C>
    friend std::ostream& operator<<(std::ostream& o, const SortedPQ<U, C>& pq);
};

template <class T, class Compare>
std::ostream& operator<<(std::ostream& o, const SortedPQ<T, Compare>& pq) {
    o << '[';
    for (const auto& e : pq.queue) {
        o << e;
        if(&e != &pq.queue.back()) {
            o << ", ";
        }
    }
    return o << ']';
}
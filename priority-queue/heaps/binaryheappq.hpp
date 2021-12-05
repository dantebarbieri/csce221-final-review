#pragma once

#include <functional>
#include <ostream>

#include "binaryheap.hpp"
#include "../pq.hpp"

template <class T, class Compare = std::less<T> >
class BinaryHeapPQ : public PQ<T> {
private:
    BinaryHeap<T> queue;
public:
    const T& top() const override {
        return queue.top();
    }

    void push(const T& data) override {
        queue.push(data);
    }

    void pop() override {
        queue.pop();
    }

    template <class U, class C>
    friend std::ostream& operator<<(std::ostream& o, const BinaryHeapPQ<U, C>& pq);
};

template <class T, class Compare>
std::ostream& operator<<(std::ostream& o, const BinaryHeapPQ<T, Compare>& pq) {
    return o << pq.queue;
}
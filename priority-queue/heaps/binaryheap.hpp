#pragma once

#include <functional> // std::less
#include <ostream> // std::ostream
#include <utility> // std::swap
#include <vector> // std::vector

template <class T, class Compare = std::less<T> >
class BinaryHeap {
private:
    Compare comp;
    std::vector<T> heap;

    constexpr size_t parent(size_t i) { return (i - 1) >> 1; }
    constexpr size_t left_child(size_t i) { return (i << 1) + 1; }
    constexpr size_t right_child(size_t i) { return (i + 1) << 1; }

    bool is_internal(size_t i) { return left_child(i) < heap.size(); }
    bool is_external(size_t i) { return !is_internal(i); }
    bool is_leaf(size_t i) { return is_external(i); }

    void upheap(size_t i) {
        for (; i > 0 && comp(heap[i], heap[parent(i)]); i = parent(i)) {
            std::swap(heap[i], heap[parent(i)]);
        }
    }

    void downheap(size_t i) {
        while (right_child(i) < heap.size() && (comp(heap[left_child(i)], heap[i]) || comp(heap[right_child(i)], heap[i]))) {
            size_t extreme_child = comp(heap[left_child(i)], heap[right_child(i)]) ? left_child(i) : right_child(i);
            std::swap(heap[i], heap[extreme_child]);
            i = extreme_child;
        }
        if (is_internal(i) && comp(heap[left_child(i)], heap[i])) {
            std::swap(heap[i], heap[left_child(i)]);
            i = left_child(i);
        }
    }
public:
    const T& top() const {
        return heap.front();
    }

    void push(const T& data) {
        heap.push_back(data);
        upheap(heap.size() - 1);
    }

    void pop() {
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        downheap(0);
    }

    template <class U, class C>
    friend std::ostream& operator<<(std::ostream& o, const BinaryHeap<U, C>& bin_heap);
};

template <class T, class Compare>
std::ostream& operator<<(std::ostream& o, const BinaryHeap<T, Compare>& bin_heap) {
    o << '[';
    for (const auto& e : bin_heap.heap) {
        o << e;
        if(&e != &bin_heap.heap.back()) {
            o << ", ";
        }
    }
    return o << ']';
}
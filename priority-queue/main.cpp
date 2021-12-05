#include <iostream>

#include "heaps/binaryheappq.hpp"
#include "list/sortedpq.hpp"
#include "vector/unsortedpq.hpp"

int main() {
    BinaryHeapPQ<size_t> bin_heap_pq;
    SortedPQ<size_t> sorted_pq;
    UnsortedPQ<size_t> unsorted_pq;
    std::cout << "Inserting 5 Random Values" << std::endl;
    for (size_t i = 0; i < 5; ++i) {
        size_t value = rand() % 10;
        std::cout << "\nInserting " << value << '\n';
        bin_heap_pq.push(value);
        sorted_pq.push(value);
        unsorted_pq.push(value);
        std::cout << "Binary Heap PQ: " << bin_heap_pq << std::endl;
        std::cout << "Sorted PQ: " << sorted_pq << std::endl;
        std::cout << "Unsorted PQ: " << unsorted_pq << std::endl;
    }
}
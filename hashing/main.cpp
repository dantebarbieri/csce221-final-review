#include <iostream>
#include <string>
#include <unordered_map>

#include "linear_probing.hpp"
#include "chaining.hpp"
#include "double_hashing.hpp"

int main() {
    std::unordered_map<std::string, int> my_friends {{"Jacob", 21}, {"Erik", 19}, {"Taylor", 26}};
    std::cout << "Linear Probing\n\n";
    {
        LinearHashTable<std::string, int> friends;
        std::cout << "Initially: " << friends << std::endl;
        for(const auto& [name, age] : my_friends) {
            friends.emplace(name, age);
        }
        std::cout << "After adding my friends:\n" << friends << std::endl;
    }
    std::cout << "\n\nChaining\n\n";
    {
        ChainingHashTable<std::string, int> friends;
        std::cout << "Initially: " << friends << std::endl;
        for(const auto& [name, age] : my_friends) {
            friends.emplace(name, age);
        }
        std::cout << "After adding my friends:\n" << friends << std::endl;
    }
    std::cout << "\n\nDouble Hashing\n\n";
    {
        DoubleHashTable<std::string, int> friends;
        std::cout << "Initially: " << friends << std::endl;
        for(const auto& [name, age] : my_friends) {
            friends.emplace(name, age);
        }
        std::cout << "After adding my friends:\n" << friends << std::endl;
    }
}
#include "linked_list.hpp"
#include <iostream>

using namespace ais1002;

template<class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i];
        if (i != v.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

int main() {

    linked_list<int> list;
    list.addFirst(10);
    list.addFirst(5);
    list.addLast(6);
    list.insert(9, list.size() - 2);

    list.remove(0);
    list.remove(list.size() - 1);

    std::cout << list << std::endl;
    std::cout << list.toVector() << std::endl;

    return 0;
}

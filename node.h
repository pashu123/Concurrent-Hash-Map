#ifndef NODE_H_
#define NODE_H_
#include <iostream>


/// Node consists of key, value and a pointer to next node. This is the singly
/// linked list "node".
template <typename KEY_T, typename VAL_T>
struct Node {
    Node* next;
    Node() : next(nullptr) {}
    Node(KEY_T k, VAL_T v) : next(nullptr), key(k), value(v) {}
    ~Node() { next = nullptr; }

    const KEY_T& getKey() const { return key; }

    void setValue(VAL_T v) { value = v; }

    const VAL_T& getValue() const { return value; }

    void printNode() {
        std::cout << "Key: " << key << " Value: " << value << std::endl;
    }

   private:
    KEY_T key;
    VAL_T value;
};

#endif

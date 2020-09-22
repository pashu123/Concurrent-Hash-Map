#ifndef BUCKET_H_
#define BUCKET_H_
#include <iostream>

#include "node.h"

/// Bucket is a singly linked list of node. Front points to the first node of
/// the bucket.
template <typename KEY_T, typename VAL_T>
struct Bucket {
    Bucket() : front(nullptr) {}

    // Traversing and deleting the whole linked list.
    ~Bucket() { delBucket(); }

    // Traverse the whole bucket (linked list) printing the Key Value pairs,
    // Just for debugging purpose.
    void printBucket() {
        Node<KEY_T, VAL_T>* temp = front;

        while (temp != nullptr) {
            temp->printNode();
            temp = temp->next;
        }
    }

    void delBucket() {
        Node<KEY_T, VAL_T>* previous = nullptr;
        Node<KEY_T, VAL_T>* temp = front;

        while (temp != nullptr) {
            previous = temp;
            temp = temp->next;
            delete previous;
        }

        front = nullptr;
    }

   private:
    Node<KEY_T, VAL_T>* front;
};

#endif


#ifndef BUCKET_H_
#define BUCKET_H_
#include <functional>
#include <iostream>
#include <utility>

#include "node.h"

/// Bucket is a singly linked list of node. Front points to the first node of
/// the bucket.
template <typename KEY_T, typename VAL_T>
struct Bucket {
    Bucket() : front(nullptr) {}

    // Traversing and deleting the whole linked list.
    ~Bucket() { delBucket(); }

    // Finds the value, returns the pair of bool and value type, if the key is
    // not found pair.first = False.
    std::pair<bool,VAL_T> find(KEY_T key) {
        Node<KEY_T, VAL_T>* temp = front;

        while (temp != nullptr) {
            if (temp->getKey() == key) {
                return std::make_pair(true, temp->getValue());
            }
            temp = temp->next;
        }
        return std::make_pair(false, VAL_T());
    }

    // Inserting the key and value pair, if the key is found update the value,
    // else insert a new key value pair into the bucket.
    void insert(KEY_T key, VAL_T value) {
        Node<KEY_T, VAL_T>* previous = nullptr;
        Node<KEY_T, VAL_T>* temp = front;

        while (temp != nullptr && temp->getKey() != key) {
            previous = temp;
            temp = temp->next;
        }

        if (nullptr == temp) {     // We have reached the end of the bucket.
            if (nullptr == front)  // Checking the front.
                front = new Node<KEY_T, VAL_T>(key, value);
            else
                previous->next = new Node<KEY_T, VAL_T>(key, value);
        } else {  // Node is found with the key, just change the value.
            temp->setValue(value);
        }
    }

    // Erase the key if found, else do nothing;
    void erase(KEY_T key) {
        Node<KEY_T, VAL_T>* previous = nullptr;
        Node<KEY_T, VAL_T>* temp = front;

        while (temp != nullptr && temp->getKey() != key) {
            previous = temp;
            temp = temp->next;
        }
        // Key not found.
        if (temp == nullptr) return;

        if (front == temp)
            front = temp->next;
        else
            previous->next = temp->next;

        delete temp;
    }

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


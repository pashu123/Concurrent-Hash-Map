#ifndef MAP_H_
#define MAP_H_
#include <functional>
#include <iostream>

#include "bucket.h"
size_t DEFAULT_HASH_SIZE = 1341;

template <typename KEY_T, typename VAL_T>
struct map {
    map(size_t size = DEFAULT_HASH_SIZE) : hashSize(size) {
        hashTable = new Bucket<KEY_T, VAL_T>[hashSize];
    }

    ~map() { delete[] hashTable; }

    std::pair<bool, VAL_T> find(KEY_T k) {
        size_t hashVal = hashFunction(k) % hashSize;
        return hashTable[hashVal].find(k);
    }

    void insert(KEY_T k, VAL_T v) {
        size_t hashVal = hashFunction(k) % hashSize;
        hashTable[hashVal].insert(k, v);
    }

    void erase(KEY_T k) {
        size_t hashVal = hashFunction(k) % hashSize;
        hashTable[hashVal].erase(k);
    }

    void printKeyBucket(KEY_T k){
        size_t hashVal = hashFunction(k) % hashSize;
        hashTable[hashVal].printBucket();
    }

    void clear() {
        for (size_t i = 0; i < hashSize; i++) hashTable[i].clear();
    }

   private:
    Bucket<KEY_T, VAL_T>* hashTable;
    std::hash<KEY_T> hashFunction;
    const size_t hashSize;
};

#endif

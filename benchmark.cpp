#include <thread>
#include <vector>

#include "map.h"

// Storing insert values into a vector.
void insertOp(std::vector<std::pair<int, int>> &insert, int noOperation) {
    srand(0);
    for (int i = 0; i < noOperation; i++) {
        insert.push_back(std::make_pair(rand(), rand()));
    }
}

// Storing find values into a vector.
void findOp(std::vector<int> &find, int noOperation) {
    srand(0);
    for (int i = 0; i < noOperation; i++) {
        find.push_back(rand());
    }
}

// Storing delete values into a vector.
void delOp(std::vector<int> &del, int noOperation) {
    srand(0);
    for (int i = 0; i < noOperation; i++) {
        del.push_back(rand());
    }
}

void insertHash(std::vector<std::pair<int, int>> &vec, map<int, int> &hashmap,
                int low, int high) {
    srand(0);
    for (int i = low; i < high; i++) {
        hashmap.insert(vec[i].first, vec[i].second);
    }
}

void delHash(std::vector<int> &vec, map<int, int> &hashmap, int low, int high) {
    for (int i = low; i < high; i++) {
        hashmap.erase(vec[i]);
    }
}

void findHash(std::vector<int> &vec, map<int, int> &hashmap, int low,
              int high) {
    for (int i = low; i < high; i++) {
        hashmap.find(vec[i]);
    }
}

int main() {
    std::vector<int> threads{1, 2, 4, 8};
    std::cout << "Enter the size of hashmap: ";
    int size;
    std::cin >> size;
    map<int, int> hashMap(size);

    int totalOp = 100000;

    // Inserting Values into the vector.
    std::vector<int> find;
    std::vector<std::pair<int, int>> insert;
    std::vector<int> del;

    // Inserting Values into the vector.
    insertOp(insert, totalOp);
    findOp(find, totalOp);
    delOp(del, totalOp);

    // Initialize the map.
    insertHash(insert, hashMap, 0, totalOp);

    std::cout << "Benchmarking for read Operation" << std::endl;
    for (auto i : threads) {
        std::cout << "No. of Threads: " << i << std::endl;
        std::vector<std::thread> threadVec;
        auto startTime = std::chrono::high_resolution_clock::now();

        // We will divide no. of operations according to thread size.
        int prevSize = 0;
        for (unsigned k = 0; k < i; k++) {
            threadVec.emplace_back([&]() {
                findHash(std::ref(find), std::ref(hashMap), prevSize,
                         prevSize + totalOp / i);
            });
            prevSize = prevSize + totalOp / i;
        }
        for (auto &t : threadVec) t.join();
        auto stopTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            stopTime - startTime);
        std::cout << "Time taken: " << duration.count() << "\n";
    }

    std::cout << "Benchmarking for delete operations" << std::endl;
    for (auto i : threads) {
        hashMap.clear();
        insertHash(insert, hashMap, 0, totalOp);
        std::cout << "No. of Threads: " << i << std::endl;
        std::vector<std::thread> threadVec;
        auto startTime = std::chrono::high_resolution_clock::now();

        // We will divide no. of operations according to thread size.
        int prevSize = 0;
        for (unsigned k = 0; k < i; k++) {
            threadVec.emplace_back([&]() {
                delHash(std::ref(del), std::ref(hashMap), prevSize,
                        prevSize + totalOp / i);
            });
            prevSize = prevSize + totalOp / i;
        }
        for (auto &t : threadVec) t.join();
        auto stopTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            stopTime - startTime);
        std::cout << "Time taken: " << duration.count() << "\n";
    }

    std::cout << "Benchmarking for delete and read operations" << std::endl;
    for (auto i : threads) {
        insertHash(insert, hashMap, 0, totalOp);
        std::cout << "No. of Threads: " << i << std::endl;
        std::vector<std::thread> threadVec;
        auto startTime = std::chrono::high_resolution_clock::now();

        // We will divide no. of operations according to thread size.
        int prevSize = 0;
        for (unsigned k = 0; k < i; k++) {
            threadVec.emplace_back([&]() {
                findHash(std::ref(find), std::ref(hashMap), prevSize,
                         prevSize + totalOp / i);
                delHash(std::ref(del), std::ref(hashMap), prevSize,
                        prevSize + totalOp / i);
            });
            prevSize = prevSize + totalOp / i;
        }
        for (auto &t : threadVec) t.join();
        auto stopTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            stopTime - startTime);
        std::cout << "Time taken: " << duration.count() << "\n";
    }
}

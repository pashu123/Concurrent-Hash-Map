#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

#include "map.h"

#define SHMSIZE 1024

int main(void) {
    key_t key;
    int shmid;
    int infinite_loop = 1;
    char *shm, *s;
    char line[BUFSIZ];

    // Either use ftok or getuid to receive the key.
    key = getuid();

    // Get the shared block created by the client.
    shmid = shmget(key, SHMSIZE, 0666);
    if (shmid < 0) {
        perror("shmget failed: shared memory segment wasn't created");
        exit(EXIT_FAILURE);
    }

    // Map the shared block into this process's memory and give a pointer to it.
    shm = (char *)shmat(shmid, nullptr, 0);
    if (shm == (char *)-1) {
        perror("shmat failed: segment wasn't attached to data space");
        exit(EXIT_FAILURE);
    }

    // Default initialization of hash map.
    map<int, int> hashMap;
    while (infinite_loop) {
        // wait for the user input.
        if (*shm != (int)NULL) {
            // *shm begins with an '@' while there is no new input. Thus, the
            // program has to wait for a new input
            if (*shm != '@') {
                // cnt_char is set to 0.
                int cnt_char = 0;
                memset(line, 0, sizeof(line));

                // String received is saved to line.
                for (s = shm; *s != '$'; s++) {
                    line[cnt_char] = *s;
                    cnt_char++;
                }

                // tokenizing the string and and checking for right tokens.
                char *token = strtok(line, " ");

                // If the input string is "quit" the infinite loop is
                // interrupted, so that the shared memory segment can be
                // dettached
                if (strcmp(token, "quit") == 0) {
                    std::cout << "BYE BYE" << std::endl;
                    infinite_loop = 0;
                }

                else if (strcmp(token, "find") == 0) {
                    char *token1 = strtok(NULL, " ");
                    if (hashMap.find(atoi(token1)).first) {
                        std::cout << "Value found: ";
                        std::cout << hashMap.find(atoi(token1)).second
                                  << std::endl;
                    } else {
                        std::cout << "Value was not found in hashMap"
                                  << std::endl;
                    }
                }

                else if (strcmp(token, "insert") == 0) {
                    char *token1 = strtok(NULL, " ");
                    char *token2 = strtok(NULL, " ");
                    hashMap.insert(atoi(token1), atoi(token2));
                    std::cout << atoi(token1) << "," << atoi(token2)
                              << " key value pair was inserted." << std::endl;
                }

                else if (strcmp(token, "delete") == 0) {
                    char *token1 = strtok(NULL, " ");
                    hashMap.erase(atoi(token1));
                    std::cout << atoi(token1)
                              << " if the key was present in the hasmap then "
                                 "it is deleted"
                              << std::endl;
                } else {
                    std::cout << "Valid token not found please retry"
                              << std::endl;
                }

                // The server signalizes it has finished reading the input
                // string by inserting an '@' symbol to the memory address.
                *shm = '@';
            }
        }
    }

    if (shmdt(shm) == -1) {
        perror("shmdt failed: segment wasn't dettached from data space");
        exit(1);
    }
}

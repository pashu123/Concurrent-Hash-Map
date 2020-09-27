#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

#define SHMSIZE 1024

int main(void) {
    key_t key;
    int shmid;
    int infinite_loop = 1;
    char *shm, *s, c;
    char *user_input = (char *)malloc(sizeof(char) * BUFSIZ);

    // The key is same for client and receiver.
    key = getuid();

    // valid commands in cout.
    std::cout << "The valid commands are: "
              << "find x (finds the value in the hashmap), "
              << "insert x y (Insert the key value pair x,y into hashmap), "
              << "delete x (Deletes the key x), "
              << "quit (quits the current client), "
              << "quitserver (quits the server as well as client)" << std::endl;

    std::cout << "Please make sure that you insert only single space, this "
                 "program is not tested for errors."
              << std::endl;

    // Get the shared block or create it, if invoked by another client.
    shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);

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
    while (infinite_loop) {
        printf("Enter an alpha numeric string: ");
        fgets(user_input, BUFSIZ, stdin);

        if (strncmp(user_input, "quit", 4) == 0) {
            infinite_loop = 0;
        }
        memcpy(shm, user_input, strlen(user_input));
        s = shm;
        s += strlen(user_input);

        // The end of shared memory has '$' token written.
        *s = '$';

        // server signalizes it has finished reading the input string by
        // inserting an '@' symbol to the memory address shm is pointing to.
        while (*shm != '@') sleep(1);
    }
}

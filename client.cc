#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHMSIZ 1024

int main(void) {
    key_t key;
    int shmid;
    int infinite_loop = 1;
    char *shm, *s, c;
    char *user_input = (char *)malloc(sizeof(char) * BUFSIZ);
    key = getuid();

    shmid = shmget(key, SHMSIZ, IPC_CREAT | 0666);

    if (shmid < 0) {
        perror("shmget failed: shared memory segment wasn't created");
        exit(EXIT_FAILURE);
    }

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
        *s = '$';

        // Processor.c signalizes it has finished reading the input string by
        // inserting an '@' symbol to the memory address shm is pointing to (the
        // beginning of the shared memory string). So, here receiver.c is
        // waiting for that signal so that it can restart the loop. ('@' is not
        // alpha numeric, so it won't harm the program main functionality)
        while (*shm != '@') sleep(1);
    }

    // The shared memory segment should be dettached from data space. An error
    // is raised if segment isn't dettached
    if (shmdt(shm) == -1) {
        perror("shmdt failed: segment wasn't dettached from data space");
        exit(1);
    }

    // The shared memory IPC communication should be closed. An error is raised
    // if communication doesn't close
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        perror("shmctl failed: ipc didn't close");
        exit(1);
    }
}

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com.h"  // Contains struct shared_m definition

int main() {
    void *shared_memory = (void *)0;        // Pointer to shared memory
    struct shared_m *shared_stuff;          // Pointer to shared structure
    char buffer[2048];                      // Temporary buffer for input
    int shmid;

    // Create a shared memory segment with key 1234 and necessary permissions
    shmid = shmget((key_t)1234, sizeof(struct shared_m), 0666 | IPC_CREAT);
    shared_memory = shmat(shmid, (void *)0, 0);  // Attach shared memory segment
    shared_stuff = (struct shared_m *)shared_memory;

    while (1) {
        while (shared_stuff->flag == 1) {    // Wait for client to read the message
            sleep(1);
        }

        printf("Enter some text: ");
        fgets(buffer, 2048, stdin);          // Get user input
        strncpy(shared_stuff->text, buffer, 2048);  // Copy input to shared memory
        shared_stuff->flag = 1;              // Set flag to indicate message is ready

        if (strncmp(buffer, "end", 3) == 0)  // Exit if "end" is entered
            exit(0);
    }
}

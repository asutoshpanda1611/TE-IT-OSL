#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com.h"  // Contains struct shared_m definition

int main() {
    void *shared_memory = (void *)0;        // Pointer to shared memory
    struct shared_m *shared_stuff;          // Pointer to shared structure
    int shmid;

    // Access shared memory segment with key 1234
    shmid = shmget((key_t)1234, sizeof(struct shared_m), 0666);
    shared_memory = shmat(shmid, (void *)0, 0);  // Attach shared memory segment
    shared_stuff = (struct shared_m *)shared_memory;
    shared_stuff->flag = 0;                 // Initialize flag to 0

    while (1) {
        if (shared_stuff->flag) {           // Check if a new message is available
            printf("You wrote: %s", shared_stuff->text);  // Print the message
            shared_stuff->flag = 0;         // Set flag to 0 to indicate message read

            if (strncmp(shared_stuff->text, "end", 3) == 0)  // Exit if "end" is received
                exit(0);
        }
    }
}

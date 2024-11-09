assignment 2A


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Bubble Sort (Parent Process)
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Selection Sort (Child Process)
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int arr[20], n;

    printf("Enter the number of integers: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child Process
        printf("\n[Child] Performing Selection Sort...\n");
        selectionSort(arr, n);
        printf("[Child] Sorted Array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Simulate orphan state by delaying child exit
        sleep(5);  // Allows parent to terminate early if needed
        printf("[Child] Exiting...\n");
        exit(0);
    } else {
        // Parent Process
        printf("\n[Parent] Performing Bubble Sort...\n");
        bubbleSort(arr, n);
        printf("[Parent] Sorted Array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Demonstrate Zombie by commenting out wait:
        // wait(NULL); 

        printf("[Parent] Waiting for Child to complete...\n");
        wait(NULL);  // Parent waits for the child
        printf("[Parent] Child process completed.\n");

        // Simulate early parent termination (for orphan state)
        // exit(0);  
    }

    return 0;
}

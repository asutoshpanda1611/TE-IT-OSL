#include <stdio.h>

int main() {
    int Max[10][10], need[10][10], alloc[10][10], avail[10], completed[10], safeSequence[10];
    int p, r, i, j, process, count = 0;

    printf("Enter the no of processes : ");
    scanf("%d", &p);
    for (i = 0; i < p; i++) completed[i] = 0;

    printf("\nEnter the no of resources : ");
    scanf("%d", &r);

    printf("\nEnter the Max/Claim Matrix for each process : ");
    for (i = 0; i < p; i++) {
        printf("\nFor process %d : ", i + 1);
        for (j = 0; j < r; j++) scanf("%d", &Max[i][j]);
    }

    printf("\nEnter the allocation for each process : ");
    for (i = 0; i < p; i++) {
        printf("\nFor process %d : ", i + 1);
        for (j = 0; j < r; j++) scanf("%d", &alloc[i][j]);
    }

    printf("\nEnter the Available Resources : ");
    for (i = 0; i < r; i++) scanf("%d", &avail[i]);

    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            need[i][j] = Max[i][j] - alloc[i][j];

    do {
        process = -1;
        for (i = 0; i < p; i++) {
            if (completed[i] == 0) {
                process = i;
                for (j = 0; j < r; j++) {
                    if (avail[j] < need[i][j]) {
                        process = -1;
                        break;
                    }
                }
            }
            if (process != -1) break;
        }

        if (process != -1) {
            printf("\nProcess %d runs to completion!", process + 1);
            safeSequence[count] = process + 1;
            count++;
            for (j = 0; j < r; j++) {
                avail[j] += alloc[process][j];
                alloc[process][j] = 0;
                Max[process][j] = 0;
                completed[process] = 1;
            }
        }
    } while (count != p && process != -1);

    if (count == p) {
        printf("\nThe system is in a safe state!!\n");
        printf("Safe Sequence is  ");
        for (i = 0; i < p; i++) printf("%d  ", safeSequence[i]);
    } else {
        printf("\nThe system is in an unsafe state!!");
    }

    return 0;
}

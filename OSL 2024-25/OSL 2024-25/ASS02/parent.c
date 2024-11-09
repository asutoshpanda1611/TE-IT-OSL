#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort Function
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
void displayArray(int arr[], int size){
	for(int i = 0 ; i < size ; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

int main(){

	int size, arr[20];
	char *p[25],buff[20];

	system("clear");
	printf("======== Demonstration of EXECV ========\n");
	//taking array input from user
	printf("Enter size of array: ");
	scanf("%d", &size);
	printf("Array elements: ");
	for(int i = 0 ; i < size ; i++){
		scanf("%d", &arr[i]);
	}   

	bubbleSort(arr, 0, size-1);

    for(int i = 0 ; i < size ; i++)
    {
        snprintf(buff,20,"%d",arr[i]);
        p[i+1]=strdup(buff);
    }
    p[0]=(char*)malloc(20);
    strcpy(p[0],"childprocess");
    p[size+1] = 0;
  
    printf("\nSorted Array is: \n");
    displayArray(arr, size);

    execv("./childprocess",p); 

    return 0;
}


#include<stdio.h>

void PrinArray(int arr[], size_t len) {
    printf("\n[");
    for (int k=0;k<len;k++) {
            printf("%d, ", arr[k]);
        }
    }
    printf("]\n");
}

void insertionSort(int arr[], size_t len) {
    int parse = 0;
    for (int i = 0;i<len;i++) {
        for (int j = i-1;j>=0;j--) {
            // Parse
            parse++;
            printf("\nParse %d : \n",parse-1);
            PrintArray(arr, len);
            
            // if the element before j is larger then swap
            if (arr[j] > arr[j+1]) {
                //swap
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            else break;
        }
    }
}

void main() {
    int parse = 0;
    int arr[] = {51, 4, 80, 4, 89, 67, 88, 83, 13, 77};
    int arrlen = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, arrlen);
    
    // Sorted Array
    printf("\nAfter Sorting....\n");
    PrintArray(arr, arrlen);
}


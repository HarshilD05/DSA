// Bubble Sort
#include<stdio.h>

void PrinArray(int arr[], size_t len) {
    printf("\n[");
    for (int k=0;k<len;k++) {
            printf("%d, ", arr[k]);
        }
    }
    printf("]\n");
}

void bubbleSort(int arr[], size_t len) {
    register int i,j,parse = 1;
    for (i=0;i<len-1;i++) {
        for (j=0;j<len-i-1;j++) {
            // if next value is smaller than current value swap
            if (arr[j+1] < arr[j]) {
                //Swap
                int temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
            //Parse
            printf("\n Parse %d: \n",parse);
            PrintArray(arr, len);
            parse++;
        }
    }
}

void main() {
    int arr[] = {19 ,13 ,43 ,65 ,60 ,23 ,28 ,40 ,56 ,58};
    int arrlen = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, arrlen);
    
    //Output
    printf("\n Sorted Array : \n");
    PrintArray(arr, arrlen);
}

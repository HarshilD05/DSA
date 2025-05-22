// Sorting using Selection Sort
#include<stdio.h>

void PrinArray(int arr[], size_t len) {
    printf("\n[");
    for (int k=0;k<arrlen;k++) {
            printf("%d, ", arr[k]);
        }
    }
    printf("]\n");
}

void selectionSort(int arr[], size_t len) {
    int smallIdx, temp;
    int parse = 0;
    
    for (int i=0;i<len-1;i++) {
        smallidx = i; // let i be the smallest element
        for (int j=1+i;j<len;j++) {
            // if in remaining array an element is smaller than arr[i] then change smallest number index to j
            if (arr[j] < arr[smallidx]) smallidx = j;
        }
        //Swap the og small(i) with smallest number of the remaining arr (smallidx) 
        temp = arr[i];
        arr[i] = arr[smallidx];
        arr[smallidx] = temp;

        // Parse for the i loop
        // Debug Pruposes
        parse++;
        printf("\n Parse %d : \n",parse);
        PrintArray(arr, len);
    }        
}

void main() { 
    int arr[] = {51, 4, 80, 4, 89, 67, 88, 83, 13, 77};
    int arrlen = sizeof(arr) / sizeof(arr[0]);

    selectionSort(arr, arrlen);
    
    // Sorted Output
    printf("\n Sorted Output : \n");
    PrintArray(arr, arrlen);
}

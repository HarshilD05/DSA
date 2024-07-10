// Sorting using Selection Sort
#include<stdio.h>
void main() { int parse =0;
    int arr[] = {51, 4, 80, 4, 89, 67, 88, 83, 13, 77};
    int arrlen = sizeof(arr) / sizeof(arr[0]);
    //Sorting
    for (int i=0;i<arrlen-1;i++) {
        int smallidx = i; // let i be the smallest element
        for (int j=1+i;j<arrlen;j++) {
            // if in remaining array an element is smaller than arr[i] then change smallest number index to j
            if (arr[j] < arr[smallidx]) smallidx = j;
        }
        //Swap the og small(i) with smallest number of the remaining arr (smallidx) 
        int temp = arr[i];
        arr[i] = arr[smallidx];
        arr[smallidx] = temp;

        // Parse for the i loop
        parse++;
        printf("\n Parse %d : \n",parse);
        for (int k=0;k<arrlen;k++) {
            printf("%d ", arr[k]);
        }
    }
    // Sorted Output
    printf("\n Sorted Output : \n");
    for (int i=0;i<arrlen;i++) {
        printf("%d ",arr[i]);
    }
}
// Bubble Sort
#include<stdio.h>
void main() {register int i,j,parse = 1 ;
    int arr[] = {19 ,13 ,43 ,65 ,60 ,23 ,28 ,40 ,56 ,58};
    int arrlen = sizeof(arr) / sizeof(arr[0]);
    // Sorting
    for (j=0;j<arrlen-1;j++) {
        for (i=0;i<arrlen-j-1;i++) {
            // if next value is smaller than current value swap
            if (arr[i+1] < arr[i]) {
                //Swap
                int temp = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = temp;
            }
            //Parse
            printf("\n Parse %d: \n",parse);
            for (int k=0;k<arrlen;k++) {
                printf("%d ",arr[k]);
            }
            parse++;
        }
    }
    //Output
    printf("\n Sorted Array : \n");
    for (i=0;i<arrlen;i++) {
        printf("%d ",arr[i]);
    }
}
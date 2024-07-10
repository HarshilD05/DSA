// Quick Sort using first element as pivot
#include<stdio.h>

int partition (int arr[],int low,int high) {
    printf("\nPartition function...\n");
    printf("\tArray : \n\t");
    for (int y = low; y < high;y++) {
        printf("%d ",arr[y]);
    }

    int idx = high;
    int pivot = arr[low];

    for (int x = high-1;x >= low;x--) {
        if (arr[x] >= pivot) {
            idx--;
            int temp = arr[idx];
            arr[idx] = arr[x];
            arr[x] = temp;
        }
    }
    
    printf("\n\tPivot is : %d",pivot);
    printf("\n\tAfter sort : \n\t");
    for (int x = low;x<high;x++) {
        printf("%d ",arr[x]);
    }
    printf("\n\tReturning val : %d",idx);

    return idx;
}

void quick (int arr[],int low, int high) {
    printf("\n Quick FUnction...");
    printf("\n\tArray : \n\t");
    for (int x = low;x<high;x++) {
    printf("%d ",arr[x]);
    }
    printf("\n\t low : %d\thigh : %d",low,high);

    if (low < high-1) {
        int pidx = partition(arr,low,high);

        quick(arr,low,pidx);
        quick(arr,pidx+1,high);
    }

}

void main() {
    int b[] = {67, 88, 83, 13, 77};
    int len = sizeof(b) / sizeof(b[0]);

    quick (b,0,len);

    printf("\nSorted Array : \n");
    for (int j = 0;j<len;j++) {
        printf("%d ",b[j]);
    }
}

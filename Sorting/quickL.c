// Quick function using last element as pivot;
#include<stdio.h>

int partition(int arr[],int low,int high) {
    printf("\nPartition function...\n");
    printf("\tArray : \n\t");
    for (int y = low; y < high;y++) {
        printf("%d ",arr[y]);
    }

    int idx = low-1;
    int pivot = arr[high-1];
    
    for(int i=low;i<high;i++) {
        // Shifting all the elements samller than the pivot before it and larger ones after it
        // Pivot is the first element
        if (arr[i] <= pivot) {
            idx++;
            int temp = arr[idx];
            arr[idx] = arr[i];
            arr[i] = temp;
        }
    }
    
    printf("\n\tPivot is : %d",pivot);
    printf("\n\tAfter sort : \n\t");
    for (int x = low;x<high;x++) {
        printf("%d ",arr[x]);
    }
    printf("\n\tReturning val : %d",idx);

    return idx; // Index of the pivot
    
}

void quick(int arr[],int low,int high) {
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
    int a[] = {51, 4, 80, 4, 89, 67};
    int len = sizeof(a) / sizeof(a[0]);

    quick(a,0,len);
    
    printf("\n Sorted Array : \n");
    for (int x = 0;x<len;x++) {
        printf("%d ",a[x]);
    }
}
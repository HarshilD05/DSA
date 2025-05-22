#include<stdio.h>

void PrinArray(int arr[], size_t start, size_t end) {
    printf("\n[");
    for (int k=start;k<end;k++) {
            printf("%d, ", arr[k]);
        }
    }
    printf("]\n");
}

// Partition Function using Last Element as Pivot
int partitionL (int arr[],int low,int high) {
    printf("\nPartitionL function...\n");
    printf("\tArray : \n\t");
    PrintArray(arr, low, high);

    int idx = low-1;
    int pivot = arr[high-1];
    
    for(int i=low;i<high-1;i++) {
        // Shifting all the elements smaller than the pivot before it and larger ones after it
        if (arr[i] <= pivot) {
            idx++;
            int temp = arr[idx];
            arr[idx] = arr[i];
            arr[i] = temp;
        }
    }
    
    printf("\n\tPivot is : %d",pivot);
    printf("\n\tAfter sort : \n\t");
    PrintArray(arr, low, high);
    
    printf("\n\tReturning val : %d",idx);

    return idx; // Index of the pivot
    
}

// Partition Function using First Element as Pivot
int partitionF(int arr[],int low,int high) {
    printf("\nPartitionF function...\n");
    printf("\tArray : \n\t");
    PrintArray(arr, low, high);

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
    PrintArray(arr, low, high);
    
    printf("\n\tReturning val : %d",idx);

    return idx;
}

void quick (int arr[],int low, int high) {
    printf("\n Quick FUnction...");
    printf("\n\tArray : \n\t");
    PrintArray(arr, low, high);
    
    printf("\n\t low : %d\thigh : %d",low,high);

    if (low < high-1) {
        int pidx = partitionL(arr,low,high);

        quick(arr,low,pidx);
        quick(arr,pidx+1,high);
    }

}

void main() {
    int b[] = {67, 88, 83, 13, 77};
    int len = sizeof(b) / sizeof(b[0]);

    quick (b,0,len);

    printf("\nSorted Array : \n");
    PrintArray(arr, 0, len);
}

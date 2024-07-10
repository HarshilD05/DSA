#include<stdio.h>

void main() {
    int parse =0;
    int arr[] = {51, 4, 80, 4, 89, 67, 88, 83, 13, 77};
    int arrlen = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0;i<arrlen;i++) {
        for (int j = i;j>0;j--) {
            // Parse
            parse++;
            printf("\nParse %d : \n",parse-1);
            for (int x = 0;x<arrlen;x++) {
                printf("%d ",arr[x]);
            }
            // if the element before j is larger then swap
            if (arr[j] < arr[j-1]) {
                //swap
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
            else break;
        }
    }
    // Sorted Array
    printf("\nAfter Sorting....\n");
    for (int x = 0;x<arrlen;x++) {
        printf("%d ",arr[x]);
    }

}


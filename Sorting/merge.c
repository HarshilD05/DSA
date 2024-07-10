
#include<stdio.h>
#include<stdlib.h>

void merge (int arr[],int s,int m,int e,int len) {
    int *new = (int *)malloc(sizeof(int)*(e-s+1));
    int id1 = s,id2 = m+1;
    int x=0;
    printf("\n Merge Function...");
    printf("\n \tId1 : %d \t Id2 : %d",id1,id2);
    printf("\nArray 1 : ");
    for (int i = id1;i<id2;i++) {
        printf("%d ",arr[i]);
    }

    printf("\n Array 2 : ");
    for (int i = id2;i<=e;i++) {
        printf("%d ",arr[i]);
    }

    while (id1<=m && id2<=e) {
        printf("\n\tArr[id1] : %d \t Arr[id2] : %d",arr[id1],arr[id2]);
        if(arr[id1] <= arr[id2]) {
            *(new + x) = arr[id1];
            x++; id1++;
        }
        else {
            *(new + x) = arr[id2];
            x++; id2++;
        }
        printf("\nNew Array : ");
        for (int y = 0;y<x;y++) {
            printf("%d ",*(new + y));
        }

    }

    while (id1 <= m) { 
        *(new + x) = arr[id1];
        x++; id1++;
    }

    while (id2 <= e) {*(new + x++) = arr[id2++]; }

    printf("\nNew Array : ");
    for (int y = 0;y<x;y++) {
        printf("%d ",*(new + y));
    }
    

    for (int i = s,j=0;i<=e;i++,j++)  {
        arr[i] = *(new + j);
    }
    printf("\nChanged Array : ");
    for (int i = 0;i<len;i++) {
        printf("%d ",arr[i]);
    }

}

void divide (int arr[], int s,int e,int len) {
    
    printf("\n \tS : %d \t E : %d",s,e);
    if (s<e) {
        int mid = (s + e)/2;
        printf("\t mid : %d",mid);
        printf("\nDivide Low ....");
        divide(arr,s,mid,len);    
        printf("\nDivide High ....");
        divide(arr,mid+1,e,len);
        merge(arr,s,mid,e,len);
    }

}

void main() {
    int arr[] = {51, 4, 80, 4, 89, 67, 88, 83, 13, 77};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("\n OG Array : [");
    for (int i = 0;i<len;i++) {
        printf("%d ",arr[i]);
    }
    printf("]");

    divide(arr,0,len-1,len);

    printf("\n Sorted Array : [");
    for (int j = 0;j<len;j++) {
        printf("%d ",arr[j]);
    }
    printf("]");

}
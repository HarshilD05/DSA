#include <stdio.h>
#include <stdlib.h>

//Global declaration of Pointers
int F=-1,R=-1;
int arr[5];
int len = sizeof(arr) / sizeof(arr[0]);

void EQ() { int n;
    // Checks For Full Q
    if (R!=-1 && R==F) {
        printf("\nFull Q\n");
    }
    else {
        // Input of data
        printf("ENter value to be EQ : ");
        scanf("%d",&n);
        //If no data initialized then set to start of array
        if (F==-1 && R==-1) {
            F=0;R=0;
        }
    
        //Adding data
        arr[R] = n;
        R++;
        if (R==len) R=0;
        // printf("F: %d\t R : %d",F,R);
    }
}

int DQ() { int d;
    //Checking for Empty Q
    if (F==-1 && R==-1) {
        printf("\nEmpty Q\n");
    }
    //returning the first element in Q
    if (arr[F] != 0) {
        d = arr[F];
        arr[F] = 0;
        F++;
        printf("The DQ element is : %d",d);
    }
    if (F==len) F=0;
    if (F==R) {
        F=-1;R=-1;
    }
    // printf("\nF: %d\t R : %d",F,R);
}

void dis() { int i=F; 
    if (F==-1 && R==-1) printf("\n Empty Q! \n");
    else {
        printf("[");
        while (i < len+1) {
            if (arr[i] != 0) printf("%d ",arr[i]);
            else printf("NULL ") ;
            i++;
            if (i == len) i=0;
            if (i == R) i=len+1;
        }
        printf("]\n");
    }
}

void main() { int x=1,choice;
    while (x!=0) {
        retry : 
        printf("\nPress... \n 1-EQ \t 2-DQ \t 3-Display array \t 0-exit");
        printf("\nYour option : ");
        scanf("%d",&choice);

        switch (choice) {
            case 1 : EQ();  
                    break;

            case 2 : DQ() ; 
                    break;

            case 3 : dis();
                    break;

            case 0 : exit(0);
                    break;
            
            default : printf("Invalid Input!!");
                    goto retry;
        }
    }
}

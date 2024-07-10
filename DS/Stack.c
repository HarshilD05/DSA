#include <stdio.h>

//Global Declaration of TOP
int TOP = -1;
int arr[5];
int len = sizeof(arr) / sizeof(arr[0]);

void PUSH () { int n;
    if (TOP == len - 1) printf("\nStack Overflow\n");
    else {
        printf("ENter the data value : ");
        scanf("%d",&n);

        TOP++;
        arr[TOP] = n;
    }
}

int POP () { int d;
    if (TOP == -1) {printf("\nStack Underflow\n"); d=NULL;}
    else {
        d=arr[TOP];
        TOP--;
    }
    return d;
}

void dis() {
    if (TOP == -1) printf("\nEmpty Stack\n");
    else { printf("[");
        for (int i=0;i<=TOP;i++) {
            printf("%d ",arr[i]);
        }
        printf("]");
    }
} 

void main() { int x=1,choice,data;
    while (x!=0) {
        retry : 
        printf("\nPress... \n 1-PUSH \t 2-POP \t 3-Display array \t 0-exit");
        printf("\nYour option : ");
        scanf("%d",&choice);

        switch (choice) {
            case 1 : PUSH();  
                    break;

            case 2 :  data = POP();
                    if (data != NULL) printf("The POP data is : %d",data); 
                    break;

            case 3 : dis();
                    break;

            case 0 : x=0;
                    break;
            
            default : printf("Invalid Input!!");
                    goto retry;
        }
    }
}
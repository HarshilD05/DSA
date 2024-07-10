 #include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *flink, *rlink;
};

struct node *start = NULL,*t,*n;
int len = 0;

void addNode() { int c;

    n = (struct node*)  malloc( sizeof(struct node) );
    printf("Enter data for node : ");
    scanf("%d",&n->data);

    if (len == 0) {
        start = n;
        t = n;
        n->flink =NULL;
        n->rlink = NULL;
    }
    else {
        retry : 
        printf("\nWhere do you want to add node");
        printf("\nPress... \n1-Start \t0-End \t ELSE enter the position in Link List");
        printf("\nYour Choice : ");
        scanf("%d",&c);

        switch (c) {
            case 1 : 
            n->flink = start;
            start->rlink = n;
            start = n;
            n->rlink = NULL;
            break;

            case 0 :
            t=start;
            while(t->flink != NULL) {
                t = t->flink;
            } 
            n->rlink = t;
            t->flink = n;
            n->flink = NULL;
            break;

            default :
            if (c <= len) {
                t = start;
                for (int i=0;i<c-2;i++) {
                    t = t->flink;
                }
                n->rlink = t;
                n->flink = t->flink;
                t->flink = n;
            }
            else {
                printf("\nInvalid Index!!\n");
                goto retry;
            }
        }
    }
    printf("\nNODE Created SUCCESSFULLY !!");
    len++;
    printf("\t\t%d",len);
}

void remNode() { int d;
    if (len == 0) {
        printf("\nEmpty Link List!!");
    }
    else {
        del : 
        printf("\nWhere do you want to remove node from ?");
        printf("\nPress... \n1-Start \t0-End \t ELSE enter the position in Link List");
        printf("\nYour Choice : ");
        scanf("%d",&d);

        switch (d) {
            case 1 : 
            start = start->flink;
            free( start->rlink );
            start->rlink = NULL;
            break;

            case 0 : 
            t=start;
            while (t->flink->flink != NULL) {t=t->flink;}
            free( t->flink );
            t->flink = NULL;
            break;

            default : 
            if (d<=len) {
                t = start;
                for (int i=0;i<d-2;i++) {
                    t = t->flink;
                }
                t->flink = t->flink->flink;
                free ( t->flink->rlink );
                t->flink->rlink = t;
            }
            else {
                printf("\nInvalid Index!!");
                goto del;
            }
        }
        printf("\nNODE removed SUCCESSFULLY");
        len--;
        printf("\t\t%d",len);
    }
}

void dis() { t=start; 
    if (len == 0) {
        printf("\nEmpty Link list!!");
    }
    else {
        for (int i=0;i<len;i++) {
            printf("\nNODE %d : %d",i+1,t->data);
            t = t->flink;
        }
    }
}

void main() { int choice;
    while (1) {
        start : 
        printf("\n\nPress... \n 1-Add Node \t 2-Delete Node \t 3-Display Link List\t 0-exit");
        printf("\nYour option : ");
        scanf("%d",&choice);

        switch (choice) {
            case 1 : addNode();  
                    break;

            case 2 : remNode() ; 
                    break;

            case 3 : dis();
                    break;

            case 0 : exit(0);
                    break;
            
            default : printf("Invalid Input!!");
                    goto start;
        }
    }
}







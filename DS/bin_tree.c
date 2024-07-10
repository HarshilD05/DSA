#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node {
    int data;
    struct node *left,*right;
};

struct node* create(int arr[],int len);
void BST(int arr[],int len,struct node *root);
void pre (struct node *r);
void IN_Order (struct node *r);
void post (struct node *r);
int height (struct node *root);
void search (struct node *root, int x);
void MinHeap (int arr[],int len,struct node* root);

int main() {
    int arr[] = {};
    int len = sizeof(arr) / sizeof(arr[0]);

    
    printf("\n");
    
    return 0;
}


struct node* create(int arr[],int len) {
    // Static counter to the input array
    static int idx = -1;

    if (idx < len-1) {
    idx++;
    // NO node present in Subtree (-1) so return NULL
    if (arr[idx] == -1) {
        return NULL;
    }
    // Creating new Node
    struct node *New = (struct node*)malloc(sizeof(struct node));
    New->data = arr[idx];
    // Creating left subtree 
    New->left = create(arr,len);
    // Creating Right Subtree
    New->right = create(arr,len);

    // Returning address of the node to the prev root
    return New;
    }
    return NULL;
}

void BST(int arr[],int len,struct node *root) {
    // Counter to traverse through Array
    static int id = -1;
    // Incrementing Counter Everytime BST is called
    id ++;
    // Run only if counter within size of array
    if (id < len) {
        
        struct node *t = root;
        // First Node directly added to root
        if (id == 0){ 
            // printf("\n \tFirst NOde...");
            root->data = arr[id];
            root->left = NULL;
            root->right = NULL;
        }
        else {
            // Create new NOde with NULL links
            struct node *n = (struct node*)malloc( sizeof(struct node) );
            n->data = arr[id];
            n->left = NULL; 
            n->right = NULL;
            // printf("\n \t New NODE data : %d",n->data);

            // printf("\n DAta : %d \t arr[id] : %d",t->data,arr[id]);
            
            while (1) {
                // Travel left if value is less than NODE Data and NULL pointer not reached
                if (arr[id] < t->data && t->left != NULL)  {
                    // printf("\n\tGoing Left");
                    t=t->left;
                }
                // Travel Right if value is >= to NODE Data and NULL pointer not reached
                else if (arr[id] >= t->data && t->right != NULL ) {
                    // printf("\n\tGoing Right");
                    t=t->right;
                }
                else break;
            }
                        
            // printf("\n DAta : %d \t arr[id] : %d",t->data,arr[id]);\
            
            // When Pointer is NULL add new node to left when val < data
            if (arr[id] < t->data) {
                // printf("\n Adding new NOde on left...");
                t->left = n;
            }
            // Otherwise add new node on right
            else {
                // printf("\nAdding New Node to the right...");
                t->right = n;
            }
        }
        BST(arr,len,root);
    }
}

void pre (struct node *r) {
    if (r == NULL) {
        printf("-1 ");
        return;
    }
    printf("%d ",r->data);
    pre(r->left);
    pre(r->right);
}

void IN_Order (struct node *r) {
    if (r == NULL) {
        printf("-1 ");
        return;
    }
    IN_Order(r->left);
    printf("%d ",r->data);
    IN_Order(r->right);
}

void post (struct node *r) {
    if (r == NULL) {
        printf("-1 ");
        return;
    }
    post(r->left);
    post(r->right);
    printf("%d ",r->data);
}

int height (struct node *root) {
    // return 0 if no node present
    if (root == NULL) return 0;
    // height of left subtree
    int l = height(root->left);
    // height of right subtree
    int r = height(root->right);
    // store max val of left or right into 'h'
    int h = (l>r)? l : r ;
    // reurn h + 1 to include the root node
    return h + 1;
}

void search (struct node *root, int x) {
    int level = 0;
    int found = 0;
    struct node *t = root;//77
    
    while (t->left != NULL || t->right!=NULL) {
        if (x < t->data) {
            level ++;
            printf("\n\t Going Left");
            t=t->left;
        }
        else if (x > t->data) {
            level ++;
            printf("\n\t Going Right");
            t=t->right;
        }
        if (t->data == x) {
            printf("\n\tFound");
            found = 1;
            break;
        }
    }
    if (found) printf("\n Level : %d",level);
    else printf("\n Not FOUND...");
}

void MinHeap (int arr[],int len,struct node* root) {
    static int i = 0;
    
    if (i < len) {
        struct node* t;
        
        struct node* New = (struct node*) malloc( sizeof(struct node) );
        New->data = arr[i];
        New->left = NULL;
        New->right = NULL;
        
        if (i == 0) root = New;
        else {
            if (root->data) {
                
            }   
            else 
        }
    }
}





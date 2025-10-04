#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct TreeNode {
  int data;
  struct TreeNode* left;
  struct TreeNode* right;
} TreeNode;

typedef struct BalanceReturnData {
  TreeNode* ptr;
  size_t height;
  size_t leftChildHeight;
  size_t rightChildHeight;
} BalanceReturnData;

typedef struct BST {
  TreeNode* root;
  size_t n_Nodes;
} BST;

BST* createBST() {
  BST* t = (BST*) malloc(sizeof(BST) );
  t->root = NULL;
  t->n_Nodes = 0;

  return t;
}

void TreeCleanup (TreeNode* root) {
  if (root == NULL) return;
  TreeCleanup(root->left);
  TreeCleanup(root->right);
  free(root);
}

void BSTCleanup (BST* tree) {
  TreeCleanup(tree->root);
  free(tree);
}

void InOrderTraversal (TreeNode* root) {
  if (root == NULL) {
    printf("N ");
    return;
  }

  InOrderTraversal(root->left);
  printf("%d ", root->data);
  InOrderTraversal(root->right);
}

void PreOrderTraversal (TreeNode* root) {
  if (root == NULL) {
    printf("N ");
    return;
  }

  printf("%d ", root->data);
  PreOrderTraversal(root->left);
  PreOrderTraversal(root->right);
}

void PostOrderTraversal (TreeNode* root) {
  if (root == NULL) {
    printf("N ");
    return;
  }

  PostOrderTraversal(root->left);
  PostOrderTraversal(root->right);
  printf("%d ", root->data);
}

int TreeHeight (TreeNode* root) {
  if (root == NULL) return 0;
  int leftSubTreeHeight = TreeHeight(root->left);
  int rightSubTreeHeight = TreeHeight(root->right);
  return max(leftSubTreeHeight, rightSubTreeHeight)+1;
}

TreeNode* LeftRotateTree(TreeNode* root) {
  if (root == NULL || root ->right == NULL) return NULL;

  // make the Right Child of Root new Root
  TreeNode* newRoot = root->right;
  root->right = newRoot->left;
  newRoot->left = root;

  return newRoot;
}

TreeNode* RightRotateTree(TreeNode* root) {
  if (root == NULL || root->left == NULL) return NULL;

  TreeNode* newRoot = root->left;
  root->left = newRoot->right;
  newRoot->right = root;

  return newRoot;
}


BalanceReturnData BalanceTree(TreeNode* root) {
  BalanceReturnData ret;
  ret.ptr = root;
  if (root == NULL) {
    ret.height = 0;
    ret.leftChildHeight = 0;
    ret.rightChildHeight = 0;
  }
  else {
    BalanceReturnData lData = BalanceTree(root->left);
    BalanceReturnData rData = BalanceTree(root->right);
    root->left = lData.ptr;
    root->right = rData.ptr;

    // Check The Balance Factor of the ROOT
    int bFactor = lData.height - rData.height;
    // Check For Left Imbalance
    if (bFactor > 1) {
      // Check for LL Imbalance By checking the Child Height
      if (lData.leftChildHeight >= lData.rightChildHeight) {
        root = RightRotateTree(root);

        // Update the Returning Data
        ret.ptr = root;
        ret.leftChildHeight = lData.leftChildHeight;
        ret.rightChildHeight = max(lData.rightChildHeight, rData.height) + 1;
        ret.height = max(ret.leftChildHeight, ret.rightChildHeight) + 1;
      }
      // LR Rotation
      else {
        root->left = LeftRotateTree(root->left);
        root = RightRotateTree(root);

        // Upadting the Return value
        ret.ptr = root;
        ret.leftChildHeight = max(lData.leftChildHeight, lData.rightChildHeight - 1) + 1;
        ret.rightChildHeight = max(rData.height, lData.rightChildHeight - 1) + 1;
        ret.height = max(ret.leftChildHeight, ret.rightChildHeight) + 1;
      }
    }
    // Check for Right Imbalance
    else if (bFactor < -1) {
      // RR imbalance
      if (rData.rightChildHeight >= rData.leftChildHeight) {
        root = LeftRotateTree(root);

        // Update Ret
        ret.ptr = root;
        ret.rightChildHeight = rData.rightChildHeight;
        ret.leftChildHeight = max(lData.height, rData.leftChildHeight) + 1;
        ret.height = max(ret.leftChildHeight, ret.rightChildHeight) + 1;
      }
      // RL Imbalance
      else {
        root->right = RightRotateTree(root->right);
        root = LeftRotateTree(root);
        
        // Update Ret
        ret.ptr = root;
        ret.leftChildHeight = max(lData.height, rData.leftChildHeight - 1) + 1;
        ret.rightChildHeight = max(rData.rightChildHeight, rData.leftChildHeight - 1) + 1;
        ret.height = max(ret.leftChildHeight, ret.rightChildHeight) + 1;
      }

    }
    // If Tree Balanced
    else {
      ret.height = max(lData.height, rData.height) + 1;
      ret.leftChildHeight = lData.height;
      ret.rightChildHeight = rData.height;
    }

  }

  return ret;
}

void InsertNodeInBST (TreeNode* root, TreeNode* newNode) {
  if (newNode->data < root->data) {
    if (root->left == NULL) root->left = newNode;
    else InsertNodeInBST(root->left, newNode);
  }
  else {
    if (root->right == NULL) root->right = newNode;
    else InsertNodeInBST(root->right, newNode);
  }
}

void insertInBST (BST* tree, int val) {
  // Create a Node
  TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode) );
  node->data = val;
  node->left = NULL;
  node->right = NULL;

  // If Tree Empty make this the First Node
  if (tree->root == NULL) {
    tree->root = node;
  }
  else {
    TreeNode* ptr = tree->root;
    InsertNodeInBST(ptr, node);
    BalanceReturnData d = BalanceTree(tree->root);
    tree->root = d.ptr;
  }
  tree->n_Nodes++;

}


void removeNode(TreeNode* ptr) {
  // If Value Found
  // If Leaf Node then Straight up Delete
  if (ptr->left == NULL && ptr->right == NULL) {
    free(ptr);
    return;
  }

  // getting the Inorder Successor
  TreeNode* inSucc;
  // Check if Right SubTree Exists
  if (ptr->right) {
    inSucc = ptr->right;
    while (inSucc->left) {
      inSucc = inSucc->left;
    }    
  }
  else {
    // Take the Inorder Predeccessor
    inSucc = ptr->left;
    while (inSucc->right) {
      inSucc = inSucc->right;
    }
  }

  // Swap values with Inorder Successor
  swap(&inSucc->data, &ptr->data);
  // Call Delete of Inorder Successor
  removeNode(inSucc);
}


void removeValFromBST (BST* tree, int val) {
  // Find the Value in Tree
  TreeNode* ptr = tree->root;
  while (ptr) {
    if (ptr->data == val) break;
    else if (ptr->data < val) ptr = ptr->left;
    else ptr = ptr->right;
  }

  // Value not found
  if (ptr == NULL) {
    printf("\n Value %d not found in Tree ....", val);
    return;
  }
  else {
    removeNode(ptr);
    tree->n_Nodes--;
    BalanceReturnData d = BalanceTree(tree->root);
    tree->root = d.ptr;
  } 
}

int main (int argc, char* argv[]) {
  BST* tree = createBST();

  int choice = -1, val = 0;

  while (choice) {
    printf("\n\n Press... ");
    printf("\n1 - InsertVal  2 - RemoveVal  3 - GetHeight  4 - NodeCount");
    printf("\n5 - PreOrder  6 - InOrder  7 - PostOrder  0 - Exit");
    printf("\nYour Choice : ");
    scanf("%d", &choice);

    switch (choice) {
      // Insert
      case 1: 
      printf("\nEnter Value to Insert : ");
      scanf("%d", &val);
      insertInBST(tree, val);
      break;

      // Remove
      case 2: 
      printf("\nEnter Value to Remove : ");
      scanf("%d", &val);
      removeValFromBST(tree, val);
      break;

      // GetHeight
      case 3: 
      val = TreeHeight(tree->root);
      printf("\nTree Height : %d", val);
      break;

      // Node Count
      case 4: 
      printf("\n Nodes in Tree : %d", tree->n_Nodes);
      break;

      // PreOrder
      case 5: 
      printf("\nPreOrder Traversal : \n");
      PreOrderTraversal(tree->root);
      printf("\n");
      break;

      // InOrder
      case 6: 
      printf("\nInOrder Traversal : \n");
      InOrderTraversal(tree->root);
      printf("\n");
      break;

      // PostOrder
      case 7: 
      printf("\nPostOrder Traversal : \n");
      PostOrderTraversal(tree->root);
      printf("\n");
      break;

      default : ;
    }
  }

  printf("\nBYE BYE !! \n");
  // Cleanup
  BSTCleanup(tree);

  return 0;
}



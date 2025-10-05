#include <iostream>

using namespace std;

enum RB_NODE_COLOR { RED, BLACK, DOUBLE_BLACK };

enum DIRECTION { LEFT, RIGHT };

// Overload the << operator for RB_NODE_COLOR enum
ostream& operator<<(ostream& os, const RB_NODE_COLOR& color) {
  switch (color) {
    case RED:
      os << "RED";
      break;
    case BLACK:
      os << "BLACK";
      break;
    case DOUBLE_BLACK:
      os << "DOUBLE_BLACK";
      break;
    default:
      os << "UNKNOWN_COLOR";
      break;
  }
  return os;
}

// Overload the << operator for DIRECTION enum
ostream& operator<<(ostream& os, const enum DIRECTION& dir) {
  switch (dir) {
    // case ROOT:
    //     os <<"ROOT";
    //     break;
    case LEFT:
      os << "LEFT";
      break;
    case RIGHT:
      os << "RIGHT";
      break;
    default:
      os << "Unknown Direction...";
      break;
  }
  return os;
}

typedef struct RBTreeNode {
  int data;
  struct RBTreeNode* left;
  struct RBTreeNode* right;
  struct RBTreeNode* parent;
  enum RB_NODE_COLOR color;

  RBTreeNode(int val)
      : data(val), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}

} RBTreeNode;

void printRBTreeNode(RBTreeNode n) {
  cout <<"\n Node Address : "<< &n ;
  cout <<"\n Data : " << n.data << "  Color : " << n.color;
  cout <<"\n Left : " << n.left;
  cout <<"\n Right : " << n.right;
  cout <<"\n Parent : " << n.parent;
  cout <<endl;
}

class RBTree {
  RBTreeNode* _root;
  size_t _size;

  void _TreeCleanup(RBTreeNode* root) {
    if (root == nullptr) return;
    _TreeCleanup(root->left);
    _TreeCleanup(root->right);
    delete root;
  }

  DIRECTION _GetChildDirection(RBTreeNode* node) {
    if (node->parent == nullptr) return LEFT;
    if (node == node->parent->left)
      return LEFT;
    else
      return RIGHT;
  }

  pair<RBTreeNode*, DIRECTION> _GetUncle(RBTreeNode* node);
  pair<RBTreeNode*, DIRECTION> _GetSibling(RBTreeNode* node);

  void _CheckInsertBalance(RBTreeNode* node);

  RBTreeNode* _LeftRotate(RBTreeNode* node);
  RBTreeNode* _RightRotate(RBTreeNode* node);

  size_t _HeightHelper(RBTreeNode* root);

  void _InOrderTraversal(RBTreeNode* root);
  void _PreOrderTraversal(RBTreeNode* root);
  void _PostOrderTraversal(RBTreeNode* root);

  void _HandleDoubleBlack(RBTreeNode* node);
  void _DeleteNode(RBTreeNode* node);

 public:
  RBTree() {
    _root = nullptr;
    _size = 0;
  }

  size_t size() { return _size; }

  size_t getHeight() { return _HeightHelper(this->_root); }

  void PrintInOrder() { _InOrderTraversal(this->_root); }

  void PrintPreOrder() { _PreOrderTraversal(this->_root); }

  void PrintPostOrder() { _PostOrderTraversal(this->_root); }

  void insert(int val);

  void remove(int val);

  RBTreeNode* find(int val);

  ~RBTree() { _TreeCleanup(this->_root); }
};

// Basic Node utility functions
size_t RBTree::_HeightHelper(RBTreeNode* root) {
  if (root == nullptr) return 0;
  // Get Left SubTree Height
  size_t lHeight = _HeightHelper(root->left);
  size_t rHeight = _HeightHelper(root->right);

  return (max(lHeight, rHeight) + 1);
}

pair<RBTreeNode*, DIRECTION> RBTree::_GetUncle(RBTreeNode* node) {
  // Check if Parent Exists
  RBTreeNode* p = node->parent;
  if (p == nullptr) return {nullptr, LEFT};

  // Check if GrandParent exists
  if (p->parent == nullptr) return {nullptr, LEFT};

  RBTreeNode* gp = p->parent;
  // check which child is the parent Left or Right and return Uncle Accordingly
  if (gp->left == p)
    return {gp->right, RIGHT};
  else
    return {gp->left, LEFT};
}

pair<RBTreeNode*, DIRECTION> RBTree::_GetSibling(RBTreeNode* node) {
  // Root / Empty node has No Sibling
  if (node == nullptr || node->parent == nullptr) return {nullptr, LEFT};

  DIRECTION dir = _GetChildDirection(node);
  if (dir == LEFT)
    return {node->parent->right, RIGHT};
  else
    return {node->parent->left, LEFT};
}

// Traversal Functions
void RBTree::_InOrderTraversal(RBTreeNode* root) {
  if (root == nullptr) {
    cout << "{ NULL, " << BLACK << " } ";
    return;
  }
  _InOrderTraversal(root->left);
  cout << "{ " << root->data << ", " << root->color << " } ";
  _InOrderTraversal(root->right);
}

void RBTree::_PreOrderTraversal(RBTreeNode* root) {
  if (root == nullptr) {
    cout << "{ NULL, " << BLACK << " } ";
    return;
  }
  cout << "{ " << root->data << ", " << root->color << " } ";
  _PreOrderTraversal(root->left);
  _PreOrderTraversal(root->right);
}

void RBTree::_PostOrderTraversal(RBTreeNode* root) {
  if (root == nullptr) {
    cout << "{ NULL, " << BLACK << " } ";
    return;
  }
  _PostOrderTraversal(root->left);
  _PostOrderTraversal(root->right);
  cout << "{ " << root->data << ", " << root->color << " } ";
}

// Searching Function
RBTreeNode* RBTree::find(int val) {
  RBTreeNode* ptr = this->_root;
  while (ptr) {
    if (ptr->data == val) break;
    else if (val < ptr->data) ptr = ptr->left;
    else ptr = ptr->right;
  }

  return ptr;
}

// Tree Rotations
RBTreeNode* RBTree::_LeftRotate(RBTreeNode* root) {
  if (root == nullptr || root->right == nullptr) return root;

  // make the Right Child of Root new Root
  RBTreeNode* newRoot = root->right;
  root->right = newRoot->left;
  newRoot->left = root;

  // Update Parents
  newRoot->parent = root->parent;
  if (root->right) root->right->parent = root;
  root->parent = newRoot;

  return newRoot;
}

RBTreeNode* RBTree::_RightRotate(RBTreeNode* root) {
  if (root == nullptr || root->left == nullptr) return root;

  RBTreeNode* newRoot = root->left;
  root->left = newRoot->right;
  newRoot->right = root;

  // Update Parents
  newRoot->parent = root->parent;
  if (root->left) root->left->parent = root;
  root->parent = newRoot;

  return newRoot;
}

// Insert Utility Functions
void RBTree::_CheckInsertBalance(RBTreeNode* node) {
  if (node == nullptr) return;
  // Check if Node is Root
  if (node == this->_root) {
    // Set color to BLACK
    node->color = BLACK;
    return;
  }

  // Check if Red Red conflict
  if (node->parent->color == RED) {
    // Check Uncle
    pair<RBTreeNode*, DIRECTION> ret = _GetUncle(node);
    RBTreeNode* uncle = ret.first;
    DIRECTION dir = ret.second;

    // If uncle is BLACK
    if (uncle == nullptr || uncle->color == BLACK) {
      // Save GrandParent Node
      RBTreeNode* gp = node->parent->parent;

      // check if Near Child then Rotate accordingly
      if ((dir == LEFT && node == node->parent->left) ||
          (dir == RIGHT && node == node->parent->right)) {
        if (dir == LEFT)
          gp->right = _RightRotate(gp->right);
        else
          gp->left = _LeftRotate(gp->left);
      }

      // When Far Child Issue then Rotate Accordingly at Grand Parent then
      // switch colors with new Root Store Great GrandParent
      RBTreeNode* ggp = gp->parent;
      // Get the Direction of gp to ggp
      DIRECTION gp_dir = _GetChildDirection(gp);

      RBTreeNode* newRoot = (dir == LEFT) ? _LeftRotate(gp) : _RightRotate(gp);
      // Swapping colors of the newRoot with the OG GP
      newRoot->color = BLACK;
      gp->color = RED;

      // Update GGP child
      // Check if GGP is Null meaning gp was root
      if (ggp == nullptr) this->_root = newRoot;
      // If GGP is Normal Node
      else {
        if (gp_dir == LEFT)
          ggp->left = newRoot;
        else
          ggp->right = newRoot;
      }

      // **NOTE** : newRoots parent already updated during the Rotate function
      // so no need to explicitly update
    }
    // if Uncle is RED
    else {
      // Switch Colors of Parent and Uncle to BLACK and GP to red
      node->parent->color = BLACK;
      uncle->color = BLACK;
      uncle->parent->color = RED;

      // Check if GP is properly colored
      _CheckInsertBalance(uncle->parent);
    }
  }
}

void RBTree::insert(int val) {
  RBTreeNode* newNode = new RBTreeNode(val);

  // Check if Inserted at Root
  if (this->_root == nullptr) {
    this->_root = newNode;
    // Set Root as Black
    newNode->color = BLACK;
  }
  // Insertion in Tree
  else {
    RBTreeNode* ptr = this->_root;
    while (ptr) {
      // If Smaller value add to Left
      if (val < ptr->data) {
        if (ptr->left)
          ptr = ptr->left;
        else {
          ptr->left = newNode;
          break;
        }
      } else {
        if (ptr->right)
          ptr = ptr->right;
        else {
          ptr->right = newNode;
          break;
        }
      }
    }

    // add Parent Pointer
    newNode->parent = ptr;

    // Check Black Depth Balance
    _CheckInsertBalance(newNode);
  }

  // Update Tree Size
  this->_size++;
}

// Delete utility Functions
void RBTree::_HandleDoubleBlack(RBTreeNode* node) {
  if (node == nullptr) return;
  // If Double Black node is Root turn to Black
  if (node == this->_root) {
    node->color = BLACK;
    return;
  }

  // Store Grand Parent
  RBTreeNode* gp = node->parent->parent;
  DIRECTION parentDir = _GetChildDirection(node->parent);
  RBTreeNode* newRoot;

  // Check the Sibling
  pair<RBTreeNode*, DIRECTION> ret = _GetSibling(node);
  RBTreeNode* sibling = ret.first;
  DIRECTION siblingDir = ret.second;

  // If Sibling is Red
  if (sibling->color == RED) {
    // Swap Parent and Sibling Colors
    node->parent->color = RED;
    sibling->color = BLACK;

    // Rotate Parent towards Double Black
    if (siblingDir == LEFT)
      newRoot = _RightRotate(node->parent);
    else
      newRoot = _LeftRotate(node->parent);

    // Update the GP Child
    if (gp == nullptr)
      this->_root = newRoot;
    else if (parentDir == LEFT)
      gp->left = newRoot;
    else
      gp->right = newRoot;

    // ReCheck Double Black
    _HandleDoubleBlack(node);
  }
  // When Sibling is Black
  else {
    // Check if Sibling Children are Both BLACK
    if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
        (sibling->right == nullptr || sibling->right->color == BLACK)) {

      // Add Black to Parent , Make Sibling RED
      sibling->parent->color = (sibling->parent->color == BLACK)? DOUBLE_BLACK : BLACK;
      sibling->color = RED;
      // Remove Double Black
      node->color = BLACK;

      // Check if Double Black still exists at Parent
      if (node->parent->color == DOUBLE_BLACK) _HandleDoubleBlack(node->parent);
    }
    // If a Red Child Exists
    else {
      if (siblingDir == LEFT) {
        // Check if Near Child red then convert it into far Child Red
        if (sibling->right && sibling->right->color == RED) {
          // Swapping Sibling and Near Child Colors
          sibling->color = RED;
          sibling->right->color = BLACK;

          // Rotate Sibling away from DB
          node->parent->left = _LeftRotate(sibling);
          // Update the Sibling
          sibling = node->parent->left;
        }

        // Handling Far Child RED
        // Swapping parent and Sibling colors
        swap(node->parent->color, sibling->color);
        // Rotate Parent Towards Double Black
        newRoot = _RightRotate(node->parent);

        // Update Grand Parent Child
        if (gp == nullptr) this->_root = newRoot;
        else if (parentDir == LEFT)
          gp->left = newRoot;
        else
          gp->right = newRoot;

        // Make Far Red Child Black
        sibling->left->color = BLACK;
        
        // remove Double Black
        node->color = BLACK;
      } 
      // Sibling DIR = RIGHT
      else {
        // Check if Near Child red then convert it into far Child Red
        if (sibling->left && sibling->left->color == RED) {
          // Swapping Sibling and Near Child Colors
          sibling->color = RED;
          sibling->left->color = BLACK;

          // Rotate Sibling away from DB
          node->parent->right = _RightRotate(sibling);
          // Update the Sibling
          sibling = node->parent->right;
        }

        // Handling Far Child RED
        // Swapping parent and Sibling colors
        swap(node->parent->color, sibling->color);
        // Rotate Parent Towards Double Black
        newRoot = _LeftRotate(node->parent);

        // Update Grand Parent Child
        if (gp == nullptr) this->_root = newRoot;
        else if (parentDir == LEFT)
          gp->left = newRoot;
        else
          gp->right = newRoot;

        // Make Far Red Child Black
        sibling->right->color = BLACK;
        
        // remove Double Black
        node->color = BLACK;
      }


      // If near Child is Red
      if ((siblingDir == LEFT && sibling->left && sibling->left->color == RED) ||
          (siblingDir == RIGHT && sibling->right && sibling->right->color == RED) ) {
        
        // Swap Sibling and near Child Color
        sibling->color = RED;

      }
    }
  }
}

void RBTree::_DeleteNode(RBTreeNode* ptr) {
  // Delete only at Leaf Node
  if (ptr->left == NULL && ptr->right == NULL) {
    // If RED leaf node then straight up Delete
    if (ptr->color == BLACK) {
      ptr->color = DOUBLE_BLACK;
      _HandleDoubleBlack(ptr);
    }
    
    // Update Parent Link
    DIRECTION dir = _GetChildDirection(ptr);
    if (dir == LEFT) ptr->parent->left = nullptr;
    else ptr->parent->right = nullptr;

    // Delete the Node
    delete ptr;
    
    // Update Tree Size
    this->_size--;

    return;
  }

  // Getting the Inorder Successor
  RBTreeNode* inSucc;
  // Check if Right SubTree Exists
  if (ptr->right) {
    inSucc = ptr->right;
    while (inSucc->left) {
      inSucc = inSucc->left;
    }
  } else {
    // Take the Inorder Predeccessor
    inSucc = ptr->left;
    while (inSucc->right) {
      inSucc = inSucc->right;
    }
  }

  // Swap values with Inorder Successor
  swap(inSucc->data, ptr->data);
  // Call Delete of Inorder Successor
  _DeleteNode(inSucc);
}

void RBTree::remove(int val) {
  // Find the Value in Tree
  RBTreeNode* ptr = find(val);

  // Value not found
  if (ptr == nullptr) {
    cout << "Value " << val << " not found in Tree ...." << endl;
    return;
  }

  _DeleteNode(ptr);
}


// Main
int main() {
  RBTree rbTree;

  int choice = -1, val = 0;
  RBTreeNode* ptr;

  while (choice) {
    cout <<"\n Press... " << endl;
    cout <<"1 - InsertVal  2 - RemoveVal  3 - Find "<<endl;
    cout <<"4 - Tree Size  5 - Tree Height"<< endl;
    cout <<"6 - PreOrder  7 - InOrder  8 - PostOrder  0 - Exit" << endl;
    cout <<"Your Choice : ";
    cin >> choice;

    switch (choice) {
      // Insert
      case 1:
        cout << "Enter Value to Insert : " << endl;
        cin >> val;
        rbTree.insert(val);
        break;

      // Remove
      case 2:
        cout<<"Enter Value to Remove : "<< endl;
        cin >> val;
        rbTree.remove(val);
        break;

      // Find
      case 3:
        cout<<"Enter Value to Find : "<<endl;
        cin >> val;
        ptr = rbTree.find(val);
        if (ptr == nullptr) cout<<"Value "<< val <<" not Found..."<<endl;
        else printRBTreeNode(*ptr);
        break;

      // Tree Size
      case 4:
        cout << "Tree Nodes : " << rbTree.size() << endl;
        break;

      // Tree Height
      case 5:
        cout << "Tree Height : " << rbTree.getHeight() << endl;
        break;

      // PreOrder
      case 6:
        cout << "PreOrder Traversal : " << endl;
        rbTree.PrintPreOrder();
        cout << endl;
        break;

      // InOrder
      case 7:
        cout << "InOrder Traversal : " << endl;
        rbTree.PrintInOrder();
        cout << endl;
        break;

      // PostOrder
      case 8:
        cout << "PostOrder Traversal : " << endl;
        rbTree.PrintPostOrder();
        cout << endl;
        break;

      default:;
    }
  }

  cout << "BYE BYE!!" << endl;

  return 0;
}

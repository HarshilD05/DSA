#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct ListNode {
  int data;
  struct ListNode* next;
} ListNode;

typedef struct LinkedList {
  size_t size;
  ListNode* head;
  ListNode* tail;
} LinkedList;

LinkedList* initLinkedList () {
  LinkedList* ll = (LinkedList*) malloc(sizeof(LinkedList));
  ll->size = 0;
  ll->head = NULL;
  ll->tail = NULL;

  return ll;
}

void printLL(LinkedList* ll) {
  printf("\n\nLinked List : \n");
  if (ll->size == 0) {
    printf("Empty Linked List...\n");
    return;
  }

  ListNode* ptr = ll->head;
  for (int i = 0;i<ll->size;++i) {
    printf("%d ", ptr->data);
    ptr = ptr->next;
  }
  printf("\n");

  return;
}

void insertListNode(LinkedList* ll, int data, int pos) {
  if (pos > ll->size) {
    printf("\nCannot Insert at Pos : %ld for LL of Size : %ld\n", pos, ll->size);
    return;
  }
  if (pos < 0) {
    return insertListNode(ll, data, ll->size+1 + pos);
  }

  ListNode* newNode = (ListNode*) malloc(sizeof(ListNode) );
  newNode->data = data;
  newNode->next = NULL;

  // Insert At Start
  if (pos == 0) {
    newNode->next = ll->head;
    ll->head = newNode;
    ll->size++;
    return;
  }

  // Insert At End
  if (pos == ll->size) {
    ll->tail->next = newNode;
    ll->tail = newNode;
    ll->size++;
    return;
  }

  // Insert In Middle
  ListNode* ptr = ll->head;
  for (int i = 1;i<pos;++i) {
    ptr = ptr->next;    
  }
  // Insert node
  newNode->next = ptr->next;
  ptr->next = newNode;  
  // Update Size
  ll->size++;
  return;
}

ListNode* removeListNode(LinkedList* ll, int pos) {
  // Check Pos Greater than LL Size
  if (pos > ll->size-1) {
    printf("Cannot remove Node at Idx : %d for LinkedList of Size : %d", pos, ll->size);
    return NULL;
  }
  // Check Negative Pos
  if (pos < 0) {
    return removeListNode(ll, ll->size + pos);
  }

  // Create Dummy Node
  ListNode* dummy = (ListNode*)malloc(sizeof(ListNode) );
  dummy->next = ll->head;

  // Traverse till pos
  ListNode* ptr = dummy;
  for (int i = 0;i<pos;++i) {
    ptr = ptr->next;
  }
  // Store removed Node in Temp
  ListNode* temp = ptr->next;
  // update Pointers
  ptr->next = ptr->next->next;
  temp->next = NULL;
  ll->head = dummy->next;
  // update Size
  ll->size--;

  // Cleanup
  free(dummy);

  return temp;
}

ListNode* listNodeAtPos(LinkedList* ll, int pos) {
  // Check Pos Greater than LL Size
  if (pos > ll->size-1) {
    printf("Cannot Get Node at Idx : %d for LinkedList of Size : %d", pos, ll->size);
    return NULL;
  }
  // Check Negative Pos
  if (pos < 0) {
    return listNodeAtPos(ll, ll->size+pos);
  }

  // Traverse till pos
  ListNode* ptr = ll->head;
  for (int i = 0;i<pos;++i) {
    ptr = ptr->next;
  }

  return ptr;
}

void LinkedListCleanup (LinkedList* ll) {
  ListNode* ptr = ll->head;
  ListNode* del = NULL;
  while (ptr) {
    del = ptr;
    ptr = ptr->next;
    free(del);
  }
  free(ll);
}

int main (int argc, char* argv[]) {
  LinkedList* ll = initLinkedList();

  int choice = -1;
  int data = 0;
  int pos = 0;
  ListNode* node = NULL;

  while (choice) {
    printf("\n\n Linked List Program...");
    printf("\nPress...");
    printf("\n 1 - Insert  2 - Remove  3 - GetNode  4 - DisplayLL  5 - getSize  0 - Exit");
    printf("\nYour Choice : ");
    scanf("%d", &choice);

    switch(choice) {
      case 1: 
      printf("\n\nInserting Node in LinkedList...");
      printf("\nEnter data to be Inserted : ");
      scanf("%d", &data);
      printf("\nEnter Pos to be Inserted at : ");
      scanf("%d", &pos);
      insertListNode(ll, data, pos);
      break;

      case 2: 
      printf("\n\nRemoving Node in LinkedList...");
      printf("\nEnter Pos to be Removed at : ");
      scanf("%d", &pos);
      node = removeListNode(ll, pos);
      if (node) printf("\nNode(%p) Val(%d) removed...", node, node->data);
      break;

      case 3: 
      printf("\n\nGetting Node in LinkedList...");
      printf("\nEnter Pos to Fetch from : ");
      scanf("%d", &pos);
      node = listNodeAtPos(ll, pos);
      if (node) printf("\nNode at Pos(%d) : %d [%p]", pos, node->data, node);
      break;

      case 4:
      printLL(ll);
      break;

      case 5: 
      printf("\nLinked List Size : %ld", ll->size);
      break;

      default: 
      break;
    }

  }

  // Cleanup
  LinkedListCleanup(ll);

  return 0;
}

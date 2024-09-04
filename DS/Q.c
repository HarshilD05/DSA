#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct Queue {
  int* que;
  size_t size;
  size_t capacity;
  size_t front;
  size_t rear;
} Queue;

void enQueue (Queue* q, int val) {
  // Check if Empty Que
  //  Can also use front == -1
  if (q->size == 0) {
    q->front = 0;
    q->rear = 0;
  }
  // Check if Que Full
  // Can also use front == rear
  else if (q->capacity == q->size) {
    // Reallocating Que to a container with twice the size
    int* temp = q->que;
    size_t newCapacity = 2*q->capacity;
    q->que = (int*) calloc(newCapacity, sizeof(int) );

    // Copying contents
    int idx = 0;
    for (int i = q->front; idx < q->size; ++i, ++idx) {
      if (i == q->capacity) i=0;
      q->que[idx] = temp[i];
    }

    // Freeing previous memory
    free(temp);
    
    // Update Size and Capacity
    q->size = idx;
    q->capacity = newCapacity;
    
    // Update Front and rear
    q->front = 0;
    q->rear = idx;
  }

  // Updating Queue
  q->que[q->rear] = val;
  q->rear++;
  q->size++;

  // Loop rear back for circular Que
  if (q->rear == q->capacity) {
    q->rear = 0;
  }

}

int deQueue (Queue* q) {
  // Check if Que is Empty
  if (q->size == 0) {
    printf("\nCannot Remove from Empty Queue....");
    return 0;
  }

  int val = q->que[q->front];
  // Update the Front ptr and size
  q->front++;
  q->size--;
  // Check if Deletion made it empty
  // Can also use front = rear
  if (q->size == 0) {
    q->front = -1;
    q->rear = -1;
  }

  return val;
}

Queue* initializeQueue (size_t len) {
  printf("\n\nInitialise Queue Fn...");
  struct Queue* que = (struct Queue*) malloc(sizeof(struct Queue) );
  que->que = calloc(len, sizeof(int) );
  que->size = 0;
  que->capacity = len;
  que->front = -1;
  que->rear = -1;

  printf("\nQue Params Initialisation Complete....");

  return que;
}

void printQueue (Queue* q) {
  printf("\n\n Front : %d     Rear : %d", q->front, q->rear);
  printf("\nSize : %d    Capacity : %d", q->size, q->capacity);

  printf("\nQue Values : \n");

  // Check if Empty Que
  if (q->size == 0) return;

  for (int i = 0, idx = q->front;i<q->size;++i, idx++) {
    if (idx == q->capacity) idx = 0;
    printf("%d ", q->que[idx]);
  }
  printf("\n\n");
}

int main(int argc, char *argv[]) {
  Queue* q = initializeQueue(2);

  int choice = 0;
  int val = 0;

  while (choice != 4) {
    printf("\n\nQueue Program....");
    printf("\nPress...");
    printf("\n1 : Insert Value");
    printf("\n2 : Remove Value");
    printf("\n3 : Print Queue");
    printf("\n4 : exit");
    printf("\n Your Choice : ");

    scanf("%d", &choice);
    
    switch (choice) {
    case 1:
    printf("\n Enter Value to Insert : ");
    scanf("%d", &val);
    enQueue(q, val);
    break;

    case 2 : 
    val = deQueue(q);
    printf("\n Val Removed : %d", val);
    break;

    case 3 : 
    printQueue(q);
    break;

    case 4: 
    printf("\n\nExiting the Program....");
    break;
    
    default:
      printf("\nWrong Option Selected...");
      break;
    }
  }
  
  return 0;
}

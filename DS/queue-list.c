#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node *next;
} Node;

typedef struct {
  int length;
  Node *head;
  Node *tail;

} Queue;

int empty(Queue *q) { return q->length == 0; }

void enqueue(Queue *q, int value) {
  Node *newNode = malloc(sizeof(Node));
  newNode->val = value;
  if (q->head == NULL) {
    q->head = newNode;
  } else {
    q->tail->next = newNode;
  }
  q->tail = newNode;
  q->length++;
}

int dequeue(Queue *q) {
  if (empty(q))
    return 0;
  Node *removedNode = q->head;
  int value = removedNode->val;
  q->head = q->head->next;
  q->length--;
  free(removedNode);
  return value;
}

void print(Queue *q) {
  Node *current = q->head;
  while (current != NULL) {
    printf("%d ", current->val);
    current = current->next;
  }
  printf("\n");
}

int main() {
  Queue *q = malloc(sizeof(Queue));
  enqueue(q, 1);
  enqueue(q, 2);
  enqueue(q, 3);
  enqueue(q, 4);
  print(q);
  dequeue(q);
  dequeue(q);
  dequeue(q);
  dequeue(q);
  print(q);
  return 0;
}

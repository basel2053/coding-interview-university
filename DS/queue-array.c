#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5
typedef struct {
  int length;
  int data[CAPACITY];
} Queue;

int empty(Queue *q) { return q->length == 0; }
int full(Queue *q) { return q->length == CAPACITY; }

void enqueue(Queue *q, int value) {
  if (full(q))
    return;
  q->data[q->length] = value;
  q->length++;
}

int dequeue(Queue *q) {
  if (empty(q))
    return 0;
  int value = q->data[0];
  for (int i = 0; i < q->length; i++) {
    q->data[i] = q->data[i + 1];
  }
  q->length--;
  return value;
}

void print(Queue *q) {
  for (int i = 0; i < q->length; i++) {
    printf("%d ", q->data[i]);
  }
  printf("\n");
}

int main() {
  Queue *q = malloc(sizeof(Queue));
  enqueue(q, 1);
  enqueue(q, 2);
  enqueue(q, 3);
  enqueue(q, 4);
  enqueue(q, 5);
  print(q);
  dequeue(q);
  dequeue(q);
  print(q);

  return 0;
}

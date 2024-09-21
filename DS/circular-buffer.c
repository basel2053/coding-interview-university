#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5
typedef struct {
  int length;
  int data[CAPACITY];
  int read;
  int write;
} Queue;

int empty(Queue *q) { return q->length == 0; }
int full(Queue *q) { return q->length - 1 == CAPACITY; }

void enqueue(Queue *q, int value) {
  if (full(q))
    return;
  q->data[q->write] = value;
  q->write = (q->write + 1) % CAPACITY;
  q->length++;
}

int dequeue(Queue *q) {
  if (empty(q))
    return 0;
  int value = q->data[q->read];
  q->read = (q->read + 1) % CAPACITY;
  q->length--;
  return value;
}

void print(Queue *q) {
  for (int i = 0; i < q->length; i++) {
    int index = (q->read + i) % CAPACITY;
    printf("%d ", q->data[index]);
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
  dequeue(q);
  dequeue(q);
  dequeue(q);
  print(q);

  return 0;
}

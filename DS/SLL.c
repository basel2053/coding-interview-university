#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node *next;
} Node;

typedef struct {
  int size;
  Node *head;

} SLL;

// typedef struct {
//   int size;
//   Node *head;
//   Node *tail;
//
// } SLL;

int size(SLL *list) { return list->size; }

int isEmpty(SLL *list) { return list->size == 0; }

void push_front(SLL *list, int value) {
  Node *newNode = malloc(sizeof(Node));
  newNode->val = value;
  newNode->next = list->head;
  list->head = newNode;
  list->size++;
}

Node *pop_front(SLL *list) {
  if (isEmpty(list))
    return NULL;

  Node *removedNode = list->head;
  list->head = list->head->next;
  free(removedNode);
  list->size--;
  return removedNode;
}

void push_back(SLL *list, int value) {
  Node *newNode = malloc(sizeof(Node));
  newNode->val = value;
  if (list->head == NULL) {
    list->head = newNode;
  } else {
    Node *current = list->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
  list->size++;
}

Node *pop_back(SLL *list) {
  if (isEmpty(list))
    return NULL;
  if (list->size == 1) {
    Node *removedNode = list->head;
    free(list->head);
    list->head = NULL;
    return removedNode;
  }
  Node *current = list->head;
  while (current->next->next != NULL) {
    current = current->next;
  }
  Node *removedNode = current->next;
  current->next = NULL;
  free(removedNode);
  list->size--;
  return removedNode;
}

void insert(SLL *list, int index, int value) {
  if (index < 0 || index > list->size)
    return;
  if (index == 0)
    return push_front(list, value);
  if (index == list->size)
    return push_back(list, value);
  Node *newNode = malloc(sizeof(Node));
  newNode->val = value;
  Node *current = list->head;
  for (int i = 0; i < index - 1; i++) {
    current = current->next;
  }
  Node *nextNode = current->next;
  current->next = newNode;
  newNode->next = nextNode;
  list->size++;
}

Node *find(SLL *list, int index) {
  if (index < 0 || index >= list->size)
    return NULL;

  Node *current = list->head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }
  return current;
}

Node *front(SLL *list) { return isEmpty(list) ? NULL : list->head; }

Node *back(SLL *list) {
  if (isEmpty(list))
    return NULL;
  Node *current = list->head;
  while (current->next != NULL) {
    current = current->next;
  }
  return current;
}

int erase(SLL *list, int index) {
  if (index < 0 || index >= list->size)
    return 0;

  if (index == 0) {
    pop_front(list);
    return 1;
  }

  Node *current = list->head;
  for (int i = 0; i < index - 1; i++) {
    current = current->next;
  }
  Node *nextNode = current->next;
  current->next = nextNode->next;
  free(nextNode);
  list->size--;
  return 1;
}

int remove_value(SLL *list, int value) {
  if (isEmpty(list))
    return 0;
  Node *current = list->head;
  Node *previous = NULL;
  while (current != NULL) {
    if (current->val == value)
      break;
    previous = current;
    current = current->next;
  }
  if (current == NULL)
    return 0;
  if (previous == NULL) {
    list->head = NULL;
  } else {
    previous->next = current->next;
    current->next = NULL;
  }
  free(current);
  list->size--;
  return 1;
}

int value_n_from_end(SLL *list, int nth) {
  if (isEmpty(list))
    return 0;
  int index = list->size - (nth + 1);
  Node *existingNode = find(list, index);
  return existingNode->val;
}

void reverse(SLL *list) {
  Node *current = list->head;
  Node *previous = NULL;
  Node *next = NULL;
  while (current != NULL) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }
  list->head = previous;
}

void print(SLL *list) {
  Node *current = list->head;
  while (current != NULL) {
    printf("%d ", current->val);
    current = current->next;
  }
  printf("\n");
}

int main() {
  SLL list = {0, NULL};
  push_front(&list, 1);
  push_front(&list, 2);
  push_front(&list, 3);
  pop_front(&list);
  push_back(&list, 2);
  push_back(&list, 3);
  pop_front(&list);
  reverse(&list);
  print(&list);
  pop_back(&list);
  pop_back(&list);
  pop_back(&list);
  print(&list);
  return 0;
}

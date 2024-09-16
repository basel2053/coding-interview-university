#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int capacity;
  int length;
  int *arr;
} DynamicArray;

void resize(DynamicArray *slice, int capacity) {
  int *newArr = realloc(slice->arr, sizeof(int) * capacity);
  if (newArr == NULL) {
    printf("Memory reallocation failed!\n");
    exit(1);
  }
  slice->arr = newArr;
  slice->capacity = capacity;
}

void addAndShift(DynamicArray *slice, int index, int val) {
  int newVal = val, oldVal;
  for (int i = index; i <= slice->length; i++) {
    oldVal = *(slice->arr + i);
    *(slice->arr + i) = newVal;
    newVal = oldVal;
  }
}

void init(DynamicArray *slice, int size) {
  slice->capacity = size;
  slice->length = 0;
  slice->arr = malloc(size * sizeof(int));
  if (slice->arr == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
}

int isEmpty(DynamicArray *slice) { return slice->length == 0; }

void push(DynamicArray *slice, int val) {
  int cap = slice->capacity;
  int len = slice->length;
  if (len == cap) {
    resize(slice, cap * 2);
  }
  slice->arr[len] = val;
  slice->length++;
}

void prepend(DynamicArray *slice, int val) {
  int cap = slice->capacity;
  int len = slice->length;
  if (len == cap) {
    resize(slice, cap * 2);
  }
  addAndShift(slice, 0, val);
  slice->length++;
}

int pop(DynamicArray *slice) {
  if (isEmpty(slice))
    return -1;

  int cap = slice->capacity;
  int len = slice->length;
  int lastIndex = len - 1;
  int val = *(slice->arr + lastIndex);
  *(slice->arr + lastIndex) = 0;
  slice->length--;
  if (len <= cap / 4) {
    resize(slice, cap / 2);
  }
  return val;
}

int get(DynamicArray *slice, int index) {
  return index < 0 || index >= slice->length ? -1 : *(slice->arr + index);
}

void set(DynamicArray *slice, int index, int val) {
  if (index < 0 || index >= slice->length)
    return;
  int *arr = slice->arr;
  *(arr + index) = val;
}

void delete(DynamicArray *slice, int index) {
  if (index < 0 || index >= slice->length)
    return;

  for (int j = index; j < slice->length - 1; j++) {
    slice->arr[j] = slice->arr[j + 1];
  }
  slice->arr[slice->length - 1] = 0;
  slice->length--;
  if (slice->length <= slice->capacity / 4) {
    resize(slice, slice->capacity / 2);
  }
}

void deleteAll(DynamicArray *slice, int count, ...) {
  va_list args;
  va_start(args, count);
  for (int i = 0; i < count; i++) {
    delete (slice, va_arg(args, int));
  }
  va_end(args);
}

int removeItem(DynamicArray *slice, int val, int multiple) {
  int *arr = slice->arr;
  for (int i = 0; i < slice->length; i++) {
    if (arr[i] == val) {
      delete (slice, i);
      return 1;
    }
  }
  return 0;
}

void insert(DynamicArray *slice, int index, int val) {
  if (index < 0 || index > slice->length)
    return;
  int cap = slice->capacity;
  int len = slice->length;
  if (index == len)
    return push(slice, val);
  if (index == 0)
    return prepend(slice, val);
  if (len == cap) {
    resize(slice, cap * 2);
  }
  addAndShift(slice, index, val);
  slice->length++;
}

int find(DynamicArray *slice, int val) {
  for (int i = 0; i < slice->length; i++) {
    if (slice->arr[i] == val) {
      return i;
    }
  }
  return -1;
}

int size(DynamicArray *slice) { return (*slice).length; }

int main() {
  DynamicArray slice;
  int x = 5;
  int *ptr = &x;
  init(&slice, 4);
  push(&slice, 10);
  push(&slice, 20);
  push(&slice, 30);
  push(&slice, 40);
  push(&slice, 50);
  push(&slice, 60);
  delete (&slice, 2);
  set(&slice, 4, 200);
  prepend(&slice, 5);
  insert(&slice, 3, 30);
  insert(&slice, 6, 60);
  insert(&slice, 7, 70);
  insert(&slice, 9, 250);
  insert(&slice, 0, 1);
  deleteAll(&slice, 3, 5, 4, 2);
  printf("%d\n", pop(&slice));
  for (int i = 0; i < slice.length; i++) {
    printf("%d ", slice.arr[i]);
  }
  printf("\n%d\n", get(&slice, 5));
  printf("arr cap: %d, arr length: %d\n", slice.capacity, slice.length);
  printf("%d\n", isEmpty(&slice));
  free(slice.arr);
  return 0;
}

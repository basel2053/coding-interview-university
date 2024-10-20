#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

typedef struct {
  int capacity;
  int length;
  int *arr;
} BinaryHeap;

void swap(BinaryHeap *heap, int a, int b) {
  int tmp = heap->arr[a];
  heap->arr[a] = heap->arr[b];
  heap->arr[b] = tmp;
}

void init(BinaryHeap *heap, int size) {
  heap->capacity = size;
  heap->length = 0;
  heap->arr = malloc(size * sizeof(int));
  if (heap->arr == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
}

void sift_up(BinaryHeap *heap, int index) {
  int parentIndex = (index - 1) / 2;
  if (heap->arr[index] <= heap->arr[parentIndex])
    return;
  swap(heap, index, parentIndex);
  sift_up(heap, parentIndex);
}

void sift_down(BinaryHeap *heap, int index) {
  int leftChild = 2 * index + 1;
  int rightChild = 2 * index + 2;
  int max = index;

  if (leftChild < heap->length && heap->arr[index] < heap->arr[leftChild]) {
    max = leftChild;
  }
  if (rightChild < heap->length && heap->arr[max] < heap->arr[rightChild]) {
    max = rightChild;
  }
  if (index != max) {
    swap(heap, index, max);
    sift_down(heap, max);
  }
}

void insert(BinaryHeap *heap, int data) {
  if (heap->length == heap->capacity)
    return;
  int idx = heap->length;
  heap->arr[idx] = data;
  sift_up(heap, idx);
  heap->length++;
}

int get_max(BinaryHeap *heap) { return heap->arr[0]; }

int get_size(BinaryHeap *heap) { return heap->length; }

int is_empty(BinaryHeap *heap) { return heap->length == 0; }

int extract_max(BinaryHeap *heap) {
  if (is_empty(heap))
    return -1;
  int lastIndex = heap->length - 1;
  swap(heap, 0, lastIndex);
  int maxValue = heap->arr[lastIndex];
  heap->arr[lastIndex] = -1;
  heap->length--;
  sift_down(heap, 0);
  return maxValue;
}

int remove_item(BinaryHeap *heap, int index) {
  if (is_empty(heap))
    return -1;
  int lastIndex = heap->length - 1;
  swap(heap, index, lastIndex);
  int value = heap->arr[lastIndex];
  heap->arr[lastIndex] = -1;
  heap->length--;
  sift_down(heap, index);
  return value;
}

void heapify(BinaryHeap *heap) {
  for (int i = heap->length / 2 - 1; i >= 0; i--) {
    sift_down(heap, i);
  }
}

void heap_sort(BinaryHeap *heap) {
  heapify(heap);
  int n = heap->length;
  for (int i = heap->length - 1; i >= 0; i--) {
    swap(heap, 0, i);
    heap->length--;
    sift_down(heap, 0);
  }
  // NOTE: as sift_down method depends on the length we need to decrement it to
  // not swap with an already sorted element
  heap->length = n;
}

int main() {
  BinaryHeap heap;
  init(&heap, MAX_SIZE);
  insert(&heap, 10);
  insert(&heap, 5);
  insert(&heap, 7);
  insert(&heap, 8);
  insert(&heap, 9);
  insert(&heap, 12);
  // extract_max(&heap);
  heap_sort(&heap);
  for (int i = 0; i < heap.length; i++) {
    printf("%d ", heap.arr[i]);
  }
  printf("\nMax value in heap: %d, and have length of: %d\n", get_max(&heap),
         get_size(&heap));
  return 0;
}

#include <stdio.h>
#include <stdlib.h>

int binarySearch(int target, int *arr, int size) {
  int left = 0, right = size - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] > target) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return -1;
}

int recursionBinarySearch(int target, int *arr, int left, int right) {
  int mid = left + (right - left) / 2;
  if (left > right) {
    return -1;
  }
  if (arr[mid] == target) {
    return mid;
  } else if (arr[mid] > target) {
    return recursionBinarySearch(target, arr, left, mid - 1);
  } else {
    return recursionBinarySearch(target, arr, mid + 1, right);
  }
}

int main() {
  int size = 10;
  int *arr = malloc(size * sizeof(int));
  for (int i = 0, j = 1; i < size; j += 2, i++) {
    arr[i] = j;
  }
  int result = recursionBinarySearch(13, arr, 0, size - 1);
  printf("Result is: %d\n", result);
  return 0;
}

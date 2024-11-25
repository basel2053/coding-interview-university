#include <stdio.h>
#include <stdlib.h>

#define SIZE 4

int bubbleSort(int arr[]) {
  int temp;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  return *arr;
}

int selectionSort(int arr[]) {

  int max, temp, j;
  for (int i = 0; i < SIZE; i++) {
    max = 0;
    for (j = 0; j < SIZE - i; j++) {
      if (arr[j] > arr[max]) {
        max = j;
      }
    }
    temp = arr[j - 1];
    arr[j - 1] = arr[max];
    arr[max] = temp;
  }

  return *arr;
}

// int insertionSort(int arr[]) {
//   int temp, curr;
//   for (int i = 1; i < SIZE; i++) {
//     curr = i;
//     for (int j = i - 1; j >= 0; j--) {
//       if (arr[curr] < arr[j]) {
//         temp = arr[curr];
//         arr[curr] = arr[j];
//         arr[j] = temp;
//         curr = j;
//       } else
//         break;
//     }
//   }
//   return *arr;
// }

int insertionSort(int arr[]) {
  int j;
  for (int i = 1; i < SIZE; i++) {
    int key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j + 1] = key;
  }
  return *arr;
}

void merge(int arr[], int l, int m, int r) {
  int len1 = m - l + 1;
  int len2 = r - m;
  int i, j, k;
  int arr1[len1], arr2[len2];
  for (i = 0; i < len1; i++) {
    arr1[i] = arr[l + i];
  }
  for (j = 0; j < len2; j++) {
    arr2[j] = arr[m + 1 + j];
  }

  i = 0, j = 0;
  k = l;

  while (i < len1 && j < len2) {
    if (arr1[i] < arr2[j]) {
      arr[k] = arr1[i];
      i++;
    } else {

      arr[k] = arr2[j];
      j++;
    }
    k++;
  }

  while (i < len1) {
    arr[k] = arr1[i];
    i++;
    k++;
  }
  while (j < len2) {
    arr[k] = arr2[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int left, int right) {
  if (left < right) {
    int med = left + (right - left) / 2;
    mergeSort(arr, left, med);
    mergeSort(arr, med + 1, right);
    merge(arr, left, med, right);
  }
}

void swap(int arr[], int idx, int idx2) {
  int temp = arr[idx];
  arr[idx] = arr[idx2];
  arr[idx2] = temp;
}

int partition(int arr[], int low, int high) {
  int i = low + 1, j = high, pivot = low;

  while (i <= j) {
    while (arr[j] > arr[pivot]) {
      j--;
    }
    while (arr[i] < arr[pivot] && i <= j) {
      i++;
    }
    if (i < j) {
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
      i++;
      j--;
    }
  }
  int temp = arr[pivot];
  arr[pivot] = arr[j];
  arr[j] = temp;
  return j;
}
void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int p = partition(arr, low, high);
    printf("%d\n", p);
    quickSort(arr, low, p - 1);
    quickSort(arr, p + 1, high);
  }
}

void sift_down(int arr[], int i, int size) {
  int left = i * 2 + 1;
  int right = i * 2 + 2;
  int max = i;

  if (left < size && arr[left] > arr[max]) {
    max = left;
  }
  if (right < size && arr[right] > arr[max]) {
    max = right;
  }
  if (i != max) {
    swap(arr, i, max);
    sift_down(arr, max, size);
  }
}

void heapify(int arr[]) {
  for (int i = 0; i < SIZE / 2; i++) {
    sift_down(arr, i, SIZE);
  }
}
void getMax(int arr[], int i) { swap(arr, 0, SIZE - i - 1); }

void heapSort(int arr[]) {
  heapify(arr);
  for (int i = SIZE - 1; i >= 0; i--) {
    swap(arr, 0, i);
    sift_down(arr, 0, i);
  }
}

int main() {
  // int arr[SIZE] = {6, 4, 13, 30, 18, 22, 29, 12, 2, 26};
  int arr[SIZE] = {6, 4, 13, 30};
  // int result = bubbleSort(arr);
  // int result = selectionSort(arr);
  // int result = insertionSort(arr);
  // mergeSort(arr, 0, SIZE - 1);
  quickSort(arr, 0, SIZE - 1);
  for (int i = 0; i < SIZE; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}

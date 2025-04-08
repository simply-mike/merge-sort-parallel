#include "merge.h"
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  int *L = (int *)malloc(n1 * sizeof(int));
  int *R = (int *)malloc(n2 * sizeof(int));

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j])
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }
  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];

  free(L);
  free(R);
}

void mergeSort(int arr[], int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

void insertionSort(int arr[], int left, int right) {
  for (int i = left + 1; i <= right; i++) {
    int key = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

#define INSERTION_SORT_THRESHOLD 32

void hybridMergeSort(int arr[], int left, int right) {
  if (right - left + 1 <= INSERTION_SORT_THRESHOLD) {
    insertionSort(arr, left, right);
  } else {
    int mid = left + (right - left) / 2;
    hybridMergeSort(arr, left, mid);
    hybridMergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

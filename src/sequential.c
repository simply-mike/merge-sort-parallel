#include "merge.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int n = 1000000;
  int mode = 0;
  if (argc >= 2)
    n = atoi(argv[1]);
  if (argc >= 3)
    mode = atoi(argv[2]);

  int *arr = (int *)malloc(n * sizeof(int));
  srand(time(NULL));
  generateArray(arr, n, mode);

  clock_t start = clock();
  mergeSort(arr, 0, n - 1);
  clock_t end = clock();

  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Sequential merge sort time: %f seconds\n", time_spent);

  free(arr);
  return 0;
}

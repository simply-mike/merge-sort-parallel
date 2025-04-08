#include "utils.h"
#include <stdlib.h>
#include <time.h>

// Array generation function:
// mode = 0 - random (typical case)
// mode = 1 - sorted (best case)
// mode = 2 - reverse order (worst case)
void generateArray(int *arr, int n, int mode) {
  if (mode == 1) {
    for (int i = 0; i < n; i++)
      arr[i] = i;
  } else if (mode == 2) {
    for (int i = 0; i < n; i++)
      arr[i] = n - i;
  } else {
    srand(time(NULL));
    for (int i = 0; i < n; i++)
      arr[i] = rand();
  }
}

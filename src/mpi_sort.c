#include "merge.h"
#include "utils.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef DEBUG
void is_sorted(int *data, int n) {
  for (int i = 0; i < n - 1; i++) {
    if (data[i] > data[i + 1]) {
      printf("%d %d %d\n", i, data[i], data[i + 1]);
      printf("array is not sorted \n");
      return;
    }
  }
  printf("GRATZ array is sorted \n");
}
#endif

int main(int argc, char *argv[]) {
  int rank, size, n = 1000000, mode = 0;

#ifdef DEBUG
  n = 100;
#endif

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (argc >= 2)
    n = atoi(argv[1]);
  if (argc >= 3)
    mode = atoi(argv[2]);

  int *data = NULL;
  int local_n = n / size;
  int *local_data = (int *)malloc(local_n * sizeof(int));

  if (rank == 0) {
    data = (int *)malloc(n * sizeof(int));
    srand(time(NULL));
    generateArray(data, n, mode);
  }

  double start_time = MPI_Wtime();

  MPI_Scatter(data, local_n, MPI_INT, local_data, local_n, MPI_INT, 0,
              MPI_COMM_WORLD);
  mergeSort(local_data, 0, local_n - 1);
  MPI_Gather(local_data, local_n, MPI_INT, data, local_n, MPI_INT, 0,
             MPI_COMM_WORLD);

  if (rank == 0) {
    for (int step = local_n; step < n; step *= 2) {
      for (int i = 0; i < n; i += 2 * step) {
        int mid = i + step - 1;
        int right = (i + 2 * step - 1 < n) ? (i + 2 * step - 1) : (n - 1);
        if (mid < right)
          merge(data, i, mid, right);
      }
    }
    double end_time = MPI_Wtime();
    printf("MPI merge sort time: %f seconds\n", end_time - start_time);

#ifdef DEBUG
    for (int i = 0; i < n; i++) {
      printf("%d ", data[i]);
    }
    printf("\n");
    is_sorted(data, n);
#endif

    free(data);
  }
  free(local_data);
  MPI_Finalize();
  return 0;
}

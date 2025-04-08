# Parallel Merge Sort

This project demonstrates various implementations of the merge sort algorithm using C and MPI. It includes:

- **Sequential Merge Sort** – a classic implementation for single-processor execution.
- **MPI-based Parallel Merge Sort** – a distributed version using OpenMPI to speed up sorting.
- **Hybrid Merge Sort** – a combination of merge sort and insertion sort (used on small subarrays) for additional performance improvements.

---

## Project Structure

```
project/
├── src/                
│   ├── merge.h         # Declarations of sorting functions
│   ├── merge.c         # Implementation of merge sort, insertion sort, and hybrid sort functions
│   ├── sequential.c    # Sequential merge sort implementation
│   ├── mpi_sort.c      # Parallel merge sort using MPI
│   └── hybrid_sort.c   # Hybrid merge sort implementation (merge sort + insertion sort)
├── Makefile            # Build script
└── README.md           # This documentation
```

---

## Requirements

- **OS:** Unix-like
- **Compiler:** GCC, mpicc
- **Interpreter:** Python 3
- **MPI:** OpenMPI (e.g., install via `sudo apt install openmpi-bin libopenmpi-dev`)
- **Build Tool:** Make

---

## Building the Project

To build all versions of the project, run:

```bash
make
```

This will compile the source files and produce the following executables:

- `sequential` – for the sequential version of merge sort.
- `mpi_sort` – for the MPI-based parallel version.
- `hybrid_sort` – for the hybrid merge sort.

To remove the compiled files and object directories, run:

```bash
make clean
```

---

## Running the Executables

### Sequential Merge Sort

Run the sequential version using:

```bash
./sequential [array_size] [mode]
```

- **array_size**: The number of elements in the array (default: 1,000,000).
- **mode**:
  - `0` – Random data (typical case)
  - `1` – Sorted data (best case)
  - `2` – Reverse-sorted data (worst case)

**Example:**

```bash
./sequential 1000000 0
```

---

### MPI-based Parallel Merge Sort

Run the MPI version with a specified number of processes:

```bash
mpirun -np [num_processes] ./mpi_sort [array_size] [mode]
```

**Example:**

```bash
mpirun -np 4 ./mpi_sort 1000000 0
```

---

### Hybrid Merge Sort

Run the hybrid version using:

```bash
./hybrid_sort [array_size] [mode]
```

**Example:**

```bash
./hybrid_sort 1000000 0
```

---

## Algorithm Details

| Algorithm          | Best Case      | Average Case  | Worst Case     |
|--------------------|----------------|---------------|----------------|
| Merge Sort         | O(n log n)     | O(n log n)    | O(n log n)     |
| Insertion Sort     | O(n)           | O(n²)         | O(n²)          |
| **Hybrid Merge Sort** | O(n log n)  | O(n log n)    | O(n log n)     |

The hybrid algorithm uses insertion sort for subarrays of size 32 or less, reducing overhead in recursive calls and taking advantage of better cache performance on small arrays.

---


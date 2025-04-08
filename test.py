import subprocess
import re
import statistics

ITER = 100
ARRAY_SIZE = 1000000
MODE = 0  # 0 - random (typical case)
NUM_PROCESSES = 4

time_regex = re.compile(r'([0-9]+\.[0-9]+)')

def run_command(cmd):
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    match = time_regex.search(result.stdout)
    if match:
        return float(match.group(1))
    else:
        return None

def test_executable(cmd, iterations):
    times = []
    for i in range(iterations):
        t = run_command(cmd)
        if t is not None:
            times.append(t)
    return statistics.mean(times)

seq_cmd = f"./sequential {ARRAY_SIZE} {MODE}"
mpi_cmd = f"mpirun -np {NUM_PROCESSES} ./mpi_sort {ARRAY_SIZE} {MODE}"
hyb_cmd = f"./hybrid_sort {ARRAY_SIZE} {MODE}"

avg_seq = test_executable(seq_cmd, ITER)
avg_mpi = test_executable(mpi_cmd, ITER)
avg_hyb = test_executable(hyb_cmd, ITER)

print("--------------------------------------------")
print(f"Average Sequential Merge Sort time: {avg_seq:.6f} seconds")
print(f"Average MPI Merge Sort time:        {avg_mpi:.6f} seconds")
print(f"Average Hybrid Merge Sort time:     {avg_hyb:.6f} seconds")

speedup_mpi = avg_seq / avg_mpi if avg_mpi > 0 else 0
print(f"Speedup (Sequential / MPI):         {speedup_mpi:.6f}")
speedup_hyb = avg_seq / avg_hyb if avg_mpi > 0 else 0
print(f"Speedup (Sequential / Hybrid):      {speedup_hyb:.6f}")
print("--------------------------------------------")


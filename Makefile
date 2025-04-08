CC = gcc
MPICC = mpicc

CFLAGS = -O2 -Wall
LDFLAGS = 

SRC_DIR = src

UTILS_SRC = $(SRC_DIR)/utils.c
COMMON_SRC = $(SRC_DIR)/merge.c $(UTILS_SRC)
COMMON_HDR = $(SRC_DIR)/merge.h $(SRC_DIR)/utils.h

BIN_SEQ = sequential
BIN_MPI = mpi_sort
BIN_HYB = hybrid_sort

.PHONY: all clean

all: $(BIN_SEQ) $(BIN_MPI) $(BIN_HYB)

$(BIN_SEQ): $(SRC_DIR)/sequential.c $(COMMON_SRC) $(COMMON_HDR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_MPI): $(SRC_DIR)/mpi_sort.c $(COMMON_SRC) $(COMMON_HDR)
	$(MPICC) $(CFLAGS) -o $@ $^

$(BIN_HYB): $(SRC_DIR)/hybrid_sort.c $(COMMON_SRC) $(COMMON_HDR)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(BIN_SEQ) $(BIN_MPI) $(BIN_HYB)


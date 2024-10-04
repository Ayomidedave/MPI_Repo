
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define M 3 // Number of rows in A

#define K 3 // Number of columns in A and rows in B

#define N 2 // Number of columns in B



void initialize_matrices(int A[M][K], int B[K][N]) {

  // Initialize matrix A and B with values

  // For simplicity, hardcoded values are used here

  int count = 1;

  for (int i = 0; i < M; i++)

    for (int j = 0; j < K; j++)

      A[i][j] = count++;

   

  count = 1;

  for (int i = 0; i < K; i++)

    for (int j = 0; j < N; j++)

      B[i][j] = count++;

}



void print_matrix(int C[M][N]) {

  // Function to print matrix C

  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      printf("%d ", C[i][j]);

    }

    printf("\n");

  }

}



int main(int argc, char** argv) {

  int rank, size;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Comm_size(MPI_COMM_WORLD, &size);



  int A[M][K], B[K][N], C[M][N] = {0};

  int local_rows; // Number of rows for the local process



  if (rank == 0) {

    // Initialize matrices A and B in the root process

    initialize_matrices(A, B);

  }



  // Broadcast matrix B to all processes

  MPI_Bcast(B, K * N, MPI_INT, 0, MPI_COMM_WORLD);



  // Calculate local rows for each process

  local_rows = M / size + (rank < M % size ? 1 : 0); // Divide rows, account for remainder

  int local_A[local_rows][K]; // Buffer to hold a portion of A

  int local_C[local_rows][N]; // Buffer to hold a portion of C



  // Manually distribute rows of A to each process

  if (rank == 0) {

    // Send rows to each process

    int current_row = 0;

    for (int p = 0; p < size; p++) {

      local_rows = M / size + (p < M % size ? 1 : 0);

      for (int i = 0; i < local_rows; i++) {

        MPI_Send(A[current_row + i], K, MPI_INT, p, 0, MPI_COMM_WORLD);

      }

      current_row += local_rows; // Update current_row for the next process

    }

  } else {

    // Receive rows of A 

    MPI_Status status;

    for (int i = 0; i < local_rows; i++) {

      MPI_Recv(local_A[i], K, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

    }

  }



  // Performing the multiplication for part of A

  for (int i = 0; i < local_rows; i++) {

    for (int j = 0; j < N; j++) {

      local_C[i][j] = 0;

      for (int k = 0; k < K; k++) {

        local_C[i][j] += local_A[i][k] * B[k][j];

      }

    }

  }



  // Gathering the parts of C from all processes

  if (rank == 0) {

    // Copy local results to the global C matrix

    for (int i = 0; i < local_rows; i++) {

      for (int j = 0; j < N; j++) {

        C[i][j] = local_C[i][j];

      }

    }

    // Receiving the result from the processes.

    int current_row = local_rows;

    for (int p = 1; p < size; p++) {

      local_rows = M / size + (p < M % size ? 1 : 0);

      for (int i = 0; i < local_rows; i++) {

        MPI_Recv(C[current_row + i], N, MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      }

      current_row += local_rows; // Update current_row for the next process

    }

  } else {

    // Send local results to the root process

    MPI_Send(local_C, local_rows * N, MPI_INT, 0, 0, MPI_COMM_WORLD);

  }



  if (rank == 0) {

    // Print the result

    printf("Resultant Matrix C:\n");

    print_matrix(C);

  }



  MPI_Finalize();

  return 0;

}
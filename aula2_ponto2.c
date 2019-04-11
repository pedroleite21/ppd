#include <stdio.h>
#include <string.h>
#include "mpi.h"
#define SIZE 5

void main(int argc, char** argv) 
{
	int my_rank;
	int proc_n;
	int source;
	int dest;
	int tag = 50;
	
	MPI_Status status;

	MPI_Init (&argc,  &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_n);

	int vector[SIZE] = {0, 1, 2, 3, 4};
	int buffer;

	for(int i=0; i<SIZE; i++) {
	
		if(my_rank == 0) {
			buffer = vector[i];
	
		} else {
			// senao recebo	do anterior
			MPI_Recv(&buffer, 1, MPI_INT, my_rank-1, tag, MPI_COMM_WORLD, &status);	
		}

		if(my_rank == (proc_n - 1)) {
			printf("[%d] : %d\n", my_rank, buffer);
		
		} else {
	
			MPI_Send(&buffer, 1, MPI_INT, my_rank + 1, tag, MPI_COMM_WORLD);	
		}
	
	}

	MPI_Finalize();
}

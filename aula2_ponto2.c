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

	int vector[SIZE][1];
	int buffer;

	double t1, t2;

	for(int i=0; i<SIZE; i++) {
	
		if(my_rank == 0) {
			t1 = MPI_Wtime();
	
			buffer = vector[i][i];
	
		} else {
			// senao recebo	do anterior
			MPI_Recv(&buffer, 1, MPI_INT, my_rank-1, tag, MPI_COMM_WORLD, &status);	
		}

		buffer += 1;

		if(my_rank == (proc_n - 1)) {	
			MPI_Send(&buffer, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);

			printf("[%d] : %d\n", my_rank, buffer);
		
		} else {
	
			MPI_Send(&buffer, 1, MPI_INT, my_rank + 1, tag, MPI_COMM_WORLD);	
		}


		if(my_rank == 0) {
			MPI_Recv(&buffer, 1, MPI_INT, my_rank-1, tag, MPI_COMM_WORLD, &status);
			t2 = MPI_Wtime();
			printf("[BUFFER] : %d\n", buffer);
			printf("[TEMPO] : %lf\n", t2-t1);	
		}
	}

	MPI_Finalize();
}

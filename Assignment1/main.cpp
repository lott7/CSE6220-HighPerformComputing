// CSE6220 - Programming Assignment 1
// Parallel Pi Estimation

#include <cstdlib>
#include <ctime>
#include<mpi.h>

int main(int argc, char *argv[]) {
    // Defining variables
    int p, rank, remainder; // Variables for MPI
    long long int n, local_count = 0, total_count = 0; // Variables for calculation
    double x, y, pi_estimate, start_time, end_time; // Variables for timing and result

    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &p); // // Get total number of processes; max(processors) = 10 'locally'
    MPI_Comm_rank(comm, &rank); // Get rank of current process

    // Processor 0
    if (rank == 0) {
        // Check if the correct number of command-line arguments is provided
        if (argc != 2) {
            printf("Error: %s <integer>\n", argv[0]);
            MPI_Abort(comm, 1);
        }
        n = atoll(argv[1]); // Number of points to be used for estimation
        start_time = MPI_Wtime(); // Start timing

        remainder = n % p; // Calculate the remainder
    }

    // Processors 1 to n-1
    // Broadcast the number of points to all processors (1 to n-1)
    MPI_Bcast(&n, 1, MPI_LONG_LONG, 0, comm);
    // starting address of buffer, number of entries in buffer, datatype,
    // rank of broadcast root, communicator

    // Calculate the number of points each process will handle
    long long int points_per_processor = n / p;
    
    // Seed random number generator differently for each process
    srand(time(NULL) + rank);

    // For loop counter
    long long int for_loop_count = 0;

    for (;;) {
        // Distributing additional values to the first n % p processors
        if (rank < remainder && remainder > 0) {
            if (for_loop_count >= points_per_processor + 1) {
                break;
            }
        // Regular case for n % p = 0 && distributing no additional values
        } else {
            if (for_loop_count >= points_per_processor) {
                break;
            }
        }
        x = (double)rand() / RAND_MAX; // Generate random x-coordinate
        y = (double)rand() / RAND_MAX; // Generate random y-coordinate
        if (x * x + y * y <= 1.0) {// Check if the point is inside the unit circle
            local_count++; // Increment local count if inside the circle
        }
        // Incrementing the foor loop counter
        for_loop_count++;
    }

    // Reduce the local counts from all processes to get the total count
    MPI_Reduce(&local_count, &total_count, 1, MPI_LONG_LONG, MPI_SUM, 0, comm);
    // address of send buffer, address of receive buffer, number of elements in send buffer,
    // datatype, reduce operation, rank of root processor, communicator

    // Processor 0 computes the final estimate and prints the result
    if (rank == 0) {
        pi_estimate = 4.0 * total_count / n; // Compute the estimated value of pi
        end_time = MPI_Wtime(); // Stop timing
        printf("%.12f, %.12f\n", pi_estimate, end_time - start_time); // Print the result
    }

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}



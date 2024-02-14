README.txt
CSE 6220 - Assignment 1
Parallel Pi Estimation

---

Description:
This project aims to estimate the value of Pi through a parallel Monte Carlo simulation over the unit square.

Approach:
- Each processor is assigned a portion of random numbers to generate based on the total number of points and the number of processors.
- Random (x, y) coordinates are generated within the [0, 1] x [0, 1] unit square.
- If the Euclidean Distance from the origin ||(x, y)||₂ ≤ 1, then the point is within the circle.
- At the end of the process, the points inside the circle are summed, and Pi is estimated using the formula: pi = (4 * points_inside_circle) / total_points.

---

Compiler and Operating System Information:
- Compiler: 5.15.90.1-microsoft-standard-WSL2 #1 SMP Fri Jan 27 02:56:13 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
- Operating System: Microsoft Windows 11 Home / Ubuntu 22.04.2 LTS
- Open MPI: 4.1.2

Instructions to Compile and Run the C++ Program:
1. Ensure you have a C++ compiler installed on your system as well as Open MPI. If not, you can install one appropriate for your operating system.

2. Open a terminal/command prompt and navigate to the directory containing the source code files.

3. Use the provided Makefile to compile the C++ program. Run the following command:
   $ make

   This will use the Makefile to compile the program and create an executable.

4. Once the compilation is successful, run the executable using the following command:
   $ mpirun -np <integer> ./pi_calc <integer>
   
   Replace <integer> with the desired number of processors and the total number of points.

   Example:
   $ mpirun -np 4 ./pi_calc 1000000

   The program will then return you the Pi estimation run with 4 processors using 1,000,000 data points.

Compiling on the PACE Cluster:
1. Once compiled, execute the program using the following command:
   $ srun -n {p} pi_calc {n}
   
   Replace {p} with the desired number of processors and {n} with the total number of points.


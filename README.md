# MPI_Repo

<<<<<<< HEAD
## Module 2

## Analysis
I couldn't run it on my jupyter notebook but I was able to run it on vscode. I feel this is what I could do I just used MPI_send and MPI_Receive which serves as a blocking communication which basically the prints number of rows to each process, and the other processes receive these rows. I also used 2 nodes to execute the program.

## Result
Resultant Matrix C: -1526224497 828338432 76 100 0 0

Im not really sure but this is what I was able to output using blocking communication.

## Module 3

## Performance Optimization and Parallel Computing Report

## Introduction
The objective was to improve the performance of the initial implementation by applying various optimization techniques and parallel computing strategies.

## Initial Profiling Output
The profiling results indicate that the total execution time of the function was 3.216 seconds, with 5251 function calls. The high cumulative time suggests that there are significant areas within the code that could benefit from optimization.

## Code Optimization
After applying these optimizations, the profiling output reflected a marginal increase in the total number of function calls (5254 function calls compared to the initial 5251) but resulted in an overall increase in execution time to 3.336 seconds.

## Parallelization, observation, challenges faced, and conclusion.
The total execution time for the optimized and parallelized code was measured at 7.6761 seconds. This indicates that, despite optimizations, the new implementation did not achieve a reduction in overall execution time compared to the original version.
=======
## Analysis
I couldn't run it on my jupyter notebook but I was able to run it on vscode. I feel this is what I could do I just used MPI_send and MPI_Receive which serves as a blocking communication which basically the  prints number of rows to each process, and the other processes receive these rows. I also used 2 nodes to execute the program.

## Result
Resultant Matrix C:
-1526224497 828338432 
76 100 
0 0 

Im not really sure but this is what I was able to output using blocking communication.
>>>>>>> e8984c1cd787ac6a27a31e6d538df364bf0a903e

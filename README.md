<h1>MULTI-THREADED PRIME NUMBER CALCULATOR</h1>

This project is a Parallel Prime Number Calculator that efficiently finds all prime numbers up to a user-defined limit (N) using multi-threading techniques. Inspired by the problem description in the provided image, the core objective is to distribute the task of testing numbers for primality across multiple threads, which can significantly speed up the overall computation compared to single-threaded solutions.
<h3>Key Features</h3>

  * <h5>Multi-threaded Computation:</h5>
    Utilizes multiple threads to check different regions of the number range in parallel, effectively dividing the workload and leveraging modern multi-core processors for faster results.

  * <h5>Single-threaded Comparison:</h5>
    Includes a single-threaded variant, allowing direct comparison of execution times and showcasing the benefits of parallelization.

  * <h5>Flexible Thread Usage:</h5>
    The number of threads can be specified by the user, facilitating experimentation (e.g., running with 1 vs. 4 threads for numbers up to 100,000).

  * <h5>Performance Measurement:</h5>
    Supports performance benchmarking using timing commands (such as time ./prime_finder) to observe and compare execution durations across different thread counts and input sizes.

<h3>Example Usage</h3>

`bash`
 <p><b>Run the program with a limit of 100,000 and 4 threads
 ./prime_finder 100000 4</b></p>

<h3>Applications</h3>

  * Demonstrates how parallel processing reduces computation time for CPU-intensive mathematical tasks.

  * Serves as an educational tool for understanding thread synchronization, load balancing, and performance gains in concurrent programming.

<h3>Typical Workflow</h3>

  * Input the upper range (N) and number of threads to use.
 
  * The range is divided equally among all threads.

  * Each thread independently checks numbers in its assigned block for primality.

  * Results are merged and optionally compared with single-threaded timings for performance evaluation.

<h3>Relevant Technologies</h3>

  * Implemented in C language supporting multi-threading.

  * Utilizes thread management libraries (e.g., pthreads in C Threads).

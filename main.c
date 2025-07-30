#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 4

// Global primes array and count
int *prime_list = NULL;
int prime_count = 0;

// Thread timing structure
typedef struct {
    int thread_num;
    int start_idx;
    int end_idx;
    double time_taken;
} ThreadData;

// Sieve of Eratosthenes: fill `prime_list` and count
void compute_primes(int N) {
    char *is_prime = calloc(N+1, sizeof(char));
    prime_list = malloc((N+1) * sizeof(int)); // will fit at most N numbers
    prime_count = 0;

    for (int i = 2; i <= N; i++) is_prime[i] = 1;

    for (int i = 2; i*i <= N; i++) {
        if (is_prime[i]) {
            for (int j = i*i; j <= N; j += i) is_prime[j] = 0;
        }
    }
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) prime_list[prime_count++] = i;
    }
    free(is_prime);
}

// Each thread "processes" (in this version: prints) its chunk of primes; records self time.
void *thread_worker(void *arg) {
    ThreadData *data = (ThreadData*) arg;
    clock_t t_start = clock();

    int cnt = 0;
    for (int i = data->start_idx; i < data->end_idx; i++) {
        // Do real work here: for demo, we'll count and could "process" prime_list[i]
        cnt++;
    }

    clock_t t_end = clock();
    data->time_taken = (double)(t_end - t_start)/CLOCKS_PER_SEC;
    printf("Thread %d: processed %d primes (from %d to %d), time: %.4fs\n",
           data->thread_num, cnt, prime_list[data->start_idx], prime_list[data->end_idx-1], data->time_taken);
    pthread_exit(NULL);
}

int main() {
    int N;
    printf("Enter the limit (N): ");
    if (scanf("%d", &N) != 1 || N < 2) {
        printf("Invalid input or N < 2.\n");
        return 1;
    }

    // Step 1: Precompute all primes up to N
    compute_primes(N);
    printf("Total primes found: %d\n", prime_count);

    // Step 2: Set up and assign prime sublists to threads
    pthread_t tid[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];
    int primes_per_thread = prime_count / MAX_THREADS;
    int extras = prime_count % MAX_THREADS; // distribute leftovers

    int idx = 0;
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_data[i].thread_num = i + 1;
        thread_data[i].start_idx = idx;
        // Spread out the extras, one per thread until done
        int chunk = primes_per_thread + (i < extras ? 1 : 0);
        thread_data[i].end_idx = idx + chunk;
        thread_data[i].time_taken = 0;
        idx += chunk;
    }
    
    // Step 3: Launch threads
    clock_t t_start = clock();
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&tid[i], NULL, thread_worker, (void*)&thread_data[i]);
    }
    // Step 4: Join and record max thread time
    double max_time = 0;
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(tid[i], NULL);
        if (thread_data[i].time_taken > max_time) max_time = thread_data[i].time_taken;
    }
    clock_t t_end = clock();

    printf("\nMax thread time: %.4fs\n", max_time);
    printf("Total elapsed (wall) time: %.4fs\n", (double)(t_end-t_start)/CLOCKS_PER_SEC);

    free(prime_list);
    return 0;
}

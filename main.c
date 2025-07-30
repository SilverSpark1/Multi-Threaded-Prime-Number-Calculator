#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 8

int *prime_arr;
int N;

typedef struct {
    int thread_num;
    int start;
    int end;
} ThreadData;

void *printprime(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int i, j, flag;

    for (i = data->start; i <= data->end; i++) {
        flag = 0;
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0 && i > 1) {
            prime_arr[i] = 1;
        }
    }
    pthread_exit(NULL);
}

int main() {
    printf("Enter the limit (N): ");
    if (scanf("%d", &N) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
        return 1;
    }

    if (N < 2) {
        printf("No primes exist for N=%d.\n", N);
        return 0;
    }

    prime_arr = (int *)calloc(N + 1, sizeof(int));
    if (prime_arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    pthread_t tid[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];

    int chunk = (N - 1) / MAX_THREADS + 1;

    clock_t start = clock();

    for (int i = 0; i < MAX_THREADS; i++) {
        thread_data[i].thread_num = i + 1;
        thread_data[i].start = 2 + i * chunk;
        thread_data[i].end = ((i + 1) * chunk + 1 > N) ? N : ((i + 1) * chunk + 1);
        pthread_create(&tid[i], NULL, printprime, (void *)&thread_data[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    clock_t end = clock();

    printf("\nPrime numbers up to %d:\n", N);
    for (int i = 2; i <= N; i++) {
        if (prime_arr[i])
            printf("%d ", i);
    }
    printf("\n");

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime taken (Multi-threaded): %.4f seconds\n", time_taken);

    free(prime_arr);
    return 0;
}

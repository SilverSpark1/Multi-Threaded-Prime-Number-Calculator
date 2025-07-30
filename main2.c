#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    int N;
    printf("Enter the limit (N): ");
    if (scanf("%d", &N) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
        return 1;
    }

    if (N < 2) {
        printf("No primes exist for N=%d.\n", N);
        return 0;
    }

    clock_t start = clock();

    printf("Prime numbers up to %d (Single-threaded):\n", N);
    for (int i = 2; i <= N; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime taken (Single-threaded): %.4f seconds\n", time_taken);

    return 0;
}

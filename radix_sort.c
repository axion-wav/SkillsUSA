/*
 * Radix Sort Implementation in C
 * 
 * A fire radix sort with demo print
 * Supports unsigned integers only
 * Base-10 implementation with O(d*n) time complexity where d is number of digits
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BASE 10
#define MAX_ARRAY_SIZE 10000

/*
 * Extract a specific digit from a number
 * num: the number to extract from
 * exp: the exponent (power of base) representing the digit position
 * base: the base of the number system (default 10)
 * Returns: the digit at the specified position
 */
static inline unsigned int get_digit(unsigned int num, unsigned int exp, unsigned int base) {
    return (num / exp) % base;
}

/*
 * Counting sort - stable sort based on a specific digit position
 * arr: input array
 * n: size of array
 * exp: exponent representing which digit position to sort by
 * base: the base of the number system
 */
static void counting_sort(unsigned int *arr, size_t n, unsigned int exp, unsigned int base) {
    if (n == 0) {
        return;
    }

    unsigned int *output = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int *count = (unsigned int *)calloc(base, sizeof(unsigned int));
    
    if (!output || !count) {
        fprintf(stderr, "Memory allocation failed\n");
        free(output);
        free(count);
        exit(EXIT_FAILURE);
    }

    // Count digit frequencies
    for (size_t i = 0; i < n; i++) {
        unsigned int d = get_digit(arr[i], exp, base);
        count[d]++;
    }

    // Convert to prefix sums
    for (unsigned int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }

    // Build output array (iterate backwards for stability)
    for (size_t i = n; i > 0; i--) {
        unsigned int x = arr[i - 1];
        unsigned int d = get_digit(x, exp, base);
        output[count[d] - 1] = x;
        count[d]--;
    }

    // Copy output back to original array
    memcpy(arr, output, n * sizeof(unsigned int));

    free(output);
    free(count);
}

/*
 * Radix sort - sorts an array of unsigned integers
 * arr: array to be sorted (modified in-place)
 * n: size of array
 * base: the base of the number system (default 10)
 */
void radix_sort(unsigned int *arr, size_t n, unsigned int base) {
    if (n == 0) {
        return;
    }

    // Find maximum value to determine number of digits
    unsigned int max_val = arr[0];
    for (size_t i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    // Sort by each digit position
    for (unsigned int exp = 1; max_val / exp > 0; exp *= base) {
        counting_sort(arr, n, exp, base);
    }
}

/*
 * Print array elements
 */
static void print_array(const unsigned int *arr, size_t n) {
    printf("[");
    for (size_t i = 0; i < n; i++) {
        printf("%u", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/*
 * Generate random test data with weighted distribution
 * Similar to the Python implementation
 */
static size_t generate_test_data(unsigned int *arr, size_t max_size __attribute__((unused))) {
    srand((unsigned int)time(NULL));
    
    // Generate 100 random numbers with weighted digit distribution
    size_t n = 100;
    
    for (size_t i = 0; i < n; i++) {
        // Weighted random selection of digit count (1-10)
        int weight_sum = 30 + 20 + 20 + 15 + 30 + 40 + 60 + 80 + 120 + 300; // 715
        int r = rand() % weight_sum;
        int digits;
        
        if (r < 30) digits = 1;
        else if (r < 50) digits = 2;
        else if (r < 70) digits = 3;
        else if (r < 85) digits = 4;
        else if (r < 115) digits = 5;
        else if (r < 155) digits = 6;
        else if (r < 215) digits = 7;
        else if (r < 295) digits = 8;
        else if (r < 415) digits = 9;
        else digits = 10;
        
        // Generate number with specified digits
        unsigned int min_val = (digits == 1) ? 0 : 1;
        for (int d = 1; d < digits; d++) {
            min_val *= 10;
        }
        
        unsigned int max_val = 1;
        for (int d = 0; d < digits; d++) {
            max_val *= 10;
        }
        max_val -= 1;
        
        // Generate random number in range
        if (max_val > min_val) {
            arr[i] = min_val + (rand() % (max_val - min_val + 1));
        } else {
            arr[i] = min_val;
        }
    }
    
    return n;
}

int main(void) {
    unsigned int *arr = (unsigned int *)malloc(MAX_ARRAY_SIZE * sizeof(unsigned int));
    
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    size_t n = generate_test_data(arr, MAX_ARRAY_SIZE);

    printf("UNSORTED: \n");
    print_array(arr, n);

    radix_sort(arr, n, BASE);

    printf("\nSORTED: \n");
    print_array(arr, n);

    free(arr);
    return EXIT_SUCCESS;
}

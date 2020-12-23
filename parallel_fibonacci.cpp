/*
 * Copyright 2020 Diego Bravo B, diego.bravo@alumnos.ucn.cl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom
 *  the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <cstdio>
#include <omp.h>
#include <cmath>

using namespace std;

#define MAX 300

/**
 *  This function find the factorization given a number.
 *
 *  Naive implementation...
 */
void factorization(long double number) {

    // The counter for the exponent
    int counter = 0;

    // The 2 needs to be a 'long double'
    long double two = 2;

    // While the number it still divisible by 2, print it and divide again
    while (fmodl(number, two) == 0) {
        //printf("%.0Lf x ", two);
        number = (number / two);
        counter++;
    }

    // Print the 2 with its exponent
    if (counter > 0) {
        printf("%.0Lf^%d x ", two, counter);
    }
    // The loop from 3 -> sqrt(number)
    for (long double i = 3; i <= sqrt(number); i += 2) {

        // The counter for the exponent
        counter = 0;

        // While the remainder of division number/i is 0, print i and divide by n again
        while (fmodl(number, i) == 0) {
            // printf("%.0Lf x ", i);
            counter++;
            number = (number * (1 / i));
        }

        // To give the output a more clean format
        if (counter == 1) {
            printf("%.0Lf x ", i);
        } else if (counter >= 2) {
            printf("%.0Lf^%d x ", i, counter);
        }

    }
    // If the n at the end is a prime number
    if (number > 2) {
        printf("%.0Lf ", number);
    }

}

/**
 * This function prints the fibonacci sequence given a certain maximum.
 *
 * @param max The maximum number of fibonacci sequences numbers that will be printed.
 *
 */
void fibonacci(int max) {

    // The initial values for the sequence
    long double x = 0;
    long double y = 1;
    long double result;

    // The variable in the for loop
    int i;

#pragma omp parallel for ordered shared(max, x, y) private(i) schedule(runtime) reduction(+:result)

    // The for loop that calculates every fibonacci
    for (i = 0; i <= max; ++i) {

#pragma omp ordered

        // If i is equal to 0, just print it
        if (i == 0) {
            printf("\n n: %d -> %.0Lf = %.0Lf", i, x , x);

            // Uncomment this line if you want to know what thread is calculating the fib number
            printf(" (thread %d) ", omp_get_thread_num());
        }

        // If i is equal to 1, just print it
        if (i == 1) {
            printf( "\n n: %d -> %.0Lf = %.0Lf", i, y, y);

            // Uncomment this line if you want to know what thread is calculating the fib number
            printf(" (thread %d) ", omp_get_thread_num());

        }

        // When i is equal to 2 or bigger than it, add the values and then print the result
        if (i >= 2) {
            // Get the fibonacci number
            result = x + y;

            // Print the fibonacci number
            printf("\n n: %d -> %.0Lf = ", i, result);

            // Uncomment this line if you want to know what thread is calculating the fib number
            printf(" (thread %d) ", omp_get_thread_num());

            // Print factorization
            factorization(result);

            // Update values
            x = y;
            y = result;

        }
    }

}

/*
 * The entry point of the program.
 */
int main() {

    printf("Calculating fibonacci series... \n");

    // Take the start time
    double start = omp_get_wtime();

    fibonacci(MAX);

    // Take the end time
    double stop = omp_get_wtime();
    double execution_time = stop - start;

    // Print the results
    printf("\n Done. \n Execution time was %f seconds\n", execution_time);

    return 0;
}

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

#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>

#define MAX 300

/** This function find the factorization given a number
 *
 *  Naive implementation...
 */
void factorization(mpz_t number) {

    // Construct an mpz_class from an mpz_t
    mpz_class testNumber = mpz_class(number);
    mpz_class two = mpz_class("2", 10);

    // The loop
    while ((testNumber % two) == 0) {
        gmp_printf("%Zd x ", two);
        testNumber = (testNumber / two);
    }

    // The i variable is equal to 3 in decimal base
    mpz_class i = mpz_class("3", 10);

    // The conditional to the loop
    mpz_class square_root = sqrt(testNumber);

    // Loop from i = 3 to sqrt(number)
    for (i; i <= square_root; i = i + two) {

        // While i divides n, print i and divide by n
        while ((testNumber % i) == 0) {
            gmp_printf("%Zd x ", i);
            testNumber = (testNumber / i);
        }

    }

    if (testNumber > two) {
        gmp_printf("%Zd ", testNumber);
    }

}

/**
 * This method prints the fibonacci sequence.
 *
 * @param max The maximum fibonacci numbers that will be printed.
 **/
void fibonacci(int max) {
    // The first 2 numbers of the sequence
    mpz_t x;
    mpz_t y;

    // The variable that will contain the next fibonacci number
    mpz_t result;

    // Init
    mpz_init(x);
    mpz_init(y);
    mpz_init(result);

    // Assignament
    mpz_set_ui(x, 0);
    mpz_set_ui(y, 1);
    mpz_set_ui(result, 0);

    // Border validation
    if (max <= 0) {
        printf("Wrong argument!");
    }

    // The for loop
    for (int i = 0; i <= max; i++) {

        // If i is equal to 0, just print it
        if (i == 0) {
            gmp_printf("n: %d -> %Zd = ", i, x);
        }

        // If i is equal to 1, just print it
        if (i == 1) {
            gmp_printf("\n n: %d -> %Zd = ", i, y);
        }

        // When i is equal to 2 or bigger thant it, add the two values and the print the result.
        if (i >= 2) {

            // result = x + y
            mpz_add(result, x, y);

            // Print the result
            gmp_printf("\n n = %d -> %Zd = ", i, result);

            // Print the factorization
            factorization(result);

            /* Update the values
            x = y
            y = result

    TODO: use the method swap? check the documentation.
             */
            mpz_set(x, y);
            mpz_set(y, result);

        }

    }

}

/**
 * The entry point of the app.
 **/
int main() {

    printf("Calculating fibonacci series... \n");

    fibonacci(MAX);

    printf("\n Done. \n");
    return 0;

}


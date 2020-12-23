# Parallel Fibonacci

Assignament for High Performance Computing course.

# About

The program was created using the library **OMP** for C++. It calculates the first 300 fibonacci numbers along with their factorization.

# How to run

This program need a C++ Compiler to run. The program was tested using **GNU C++ Compiler**. Also if you want to run the program with more of 1 thread is necessary to set the number of threads variable.

So, for the compilation you need to run:

```g++ -fopenmp parallel_fibonacci.cpp -o parallel_fibonacci.out ```

- Additionally, you can use optimization flags like ```-O2``` or ```-O1```

After being compiled, execute the program using the next line, with n being the number of threads to use:

```  OMP_NUM_THREADS=n ./parallel_fibonacci.out ```


#

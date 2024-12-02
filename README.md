# LBYARCH MP 2
- **Co, Bianz Jann Kenrick Y.**
- **David,Peter Jan B.**

## SAXPY Kernel Implementation and Benchmarking
This project implements and benchmarks the SAXPY operation \( Z[i] = A * X[i] + Y[i] \) using two approaches:
1. **C Programming**
2. **x86-64 Assembly**

The goal is to compare the performance of the C implementation against the assembly implementation while ensuring correctness and meeting the specified requirements.

## Setup and Usage
### Prerequisites
- Make sure that GCC (MinGW-w64) is installed on your local machine.
- Make sure that NASM is installed on your local machine.

### Steps to Run:
1. **Clone the repository:**

    git clone https://github.com/peterrdavid/LBYARCH-MP2

2. **Run the batch script**

    run.bat

3. **If the batch script does not run, follow these steps manually:**

    nasm -f win64 saxpy_asm.asm
     gcc -c saxpy_c.c -o saxpy_c.obj -m64
     gcc saxpy_c.obj saxpy_asm.obj -o saxpy.exe -m64
     ./saxpy.exe

## Comparative Execution Time and Performance Analysis
### Execution Time Results
1. **C Kernel:**
- Run 1 (Vector Size: 1048576): Duration = 1
- Run 2 (Vector Size: 16777216): Duration = 28
- Run 3 (Vector Size: 268435456): Duration = 461

2. **Assembly Kernel:**
- Run 1 (Vector Size: 1048576): Duration = 2
- Run 2 (Vector Size: 16777216): Duration = 40
- Run 3 (Vector Size: 268435456): Duration = 664

### Performance Analysis
1. **C Implementation**
    For all runs, the first 10 elements of the result vector Z are consistent and match the expected computation.

2. **Assembly Implementation**
    The Assembly kernel produces exactly the same results as the C kernel for the same inputs.

3. **Observations**
- The memcmp function confirms that all elements in the output arrays from both kernels match perfectly. This eliminates the possibility of numerical errors or implementation bugs in either kernel.
- Both kernels implement the SAXPY operation accurately, producing the same results for all tested vector sizes and configurations.
- Regardless of the performance differences, you can rely on either implementation to compute correct results.






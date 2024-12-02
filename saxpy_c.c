#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// x86-64 assembly kernel
extern void saxpy_asm(float *X, float *Y, float *Z, int n, float A);

// C kernel
void saxpy_c(float *X, float *Y, float *Z, int n, float A) {
  for (int i = 0; i < n; i++) {
    Z[i] = A * X[i] + Y[i]; // SAXPY (A * X + Y) function
    // printf("%f * %f + %f = %f \n", A, X[i], Y[i], Z[i]);
  }
}

int main() {
  int i; // index
  int j; // index
  float A;            // scalar values
  float *X, *Y;       // pointers to vectors X and Y (input vectors)
  float *Z_c, *Z_asm; // pointers to vectors Z for C and x86-64 assembly (result vectors)
  clock_t start_time, end_time;
  double duration;
  int vector_sizes[] = {11, 1 << 20, 1 << 24, 1 << 28};
  int c_runtimes[3];
  int asm_runtimes[3];

  srand(time(NULL));

  for (i = 0; i < 1; i++) { // only picks first for testing
    A = (rand() % 11) + 1;

    printf("VECTOR SIZE = %d \n", vector_sizes[i]);
    printf("Current value of A = %.2f \n\n", A);

    // allocate memory
    X = (float *)malloc(vector_sizes[i] * sizeof(float));
    Y = (float *)malloc(vector_sizes[i] * sizeof(float));
    Z_c = (float *)malloc(vector_sizes[i] * sizeof(float));
    Z_asm = (float *)malloc(vector_sizes[i] * sizeof(float));

    if (!X || !Y || !Z_c || !Z_asm) {
      printf("Memory allocation failed.\n");
      free(X);
      free(Y);
      free(Z_c);
      free(Z_asm);
      return -1;
    }

    for (j = 0; j < vector_sizes[i]; j++) { //assign random values
      float n = (rand() % 11) + 1;
      X[j] = Y[j] = n;
      printf("Selected number for slot %d = %f \n", j, n);
      // printf("iteration = %d\n", j);
    }

    // call C kernel
    // saxpy_c(X, Y, Z_c, vector_sizes[i], A);

    start_time = clock();
    for (j = 0; j < 30; j++) {
     saxpy_c(X, Y, Z_c, vector_sizes[i], A);
    }
    end_time = clock();

    duration = end_time - start_time;

    // C Output
    printf("First 10 Results for C kernel:\n");
    for (j = 0; j < 10; j++) {
      if (Z_c[i] == 0) {
        break;
      } else {
        printf("C: Z[%d] = %.2f\n", j, Z_c[j]);
      }
    }

    printf("%lu - %lu = %f \n", end_time, start_time, duration);
    printf("Duration for C kernel = %.2f \n\n", (double)duration);

    // call x86-64 assembly kernel
    start_time = clock();
    for (j = 0; j < 30; j++) {
      saxpy_asm(X, Y, Z_asm, vector_sizes[i], A);
    }
    end_time = clock();

    duration = end_time - start_time;

    // Assembly Output
    printf("First 10 Results for Assembly kernel:\n");
    for (j = 0; j < 10; j++) {
      if (Z_asm[i] == 0) {
        break;
      } else {
        printf("C: Z[%d] = %.2f\n", j, Z_asm[j]);
      }
    }
    printf("Duration for Assembly kernel = %.2f \n\n", (double)duration);

    // free memory
    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);
    printf("FREED\n");
  }

  return 0;
}
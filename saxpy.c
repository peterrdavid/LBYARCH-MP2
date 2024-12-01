#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// x86-64 assembly kernel

// C kernel
void saxpy_c(float *X, float *Y, float *Z, int n, float A) {
  for (int i = 0; i < n; i++) {
    Z[i] = A * X[i] + Y[i]; // SAXPY (A * X + Y) function
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
  int vector_sizes[] = {1 << 20, 1 << 24, 1 << 28};
  int c_runtimes[3];
  int asm_runtimes[3];

  for (i = 0; i < 3; i++) { //only picks first for testing
    A = rand() % 21;

    printf("VECTOR SIZE = %d \n", vector_sizes[i]);
    // printf("Current value of A = %.2f \n\n", A);

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
      float n = rand() % 21;
      X[j] = Y[j] = n;
      // printf("iteration = %d\n", j);
    }

    // call C kernel
    start_time = clock();
    for (j = 0; j < 30; j++) {
      saxpy_c(X, Y, Z_c, vector_sizes[i], A);
    }
    end_time = clock();

    duration = end_time - start_time;

    // call x86-64 assembly kernel

    // C Output
    printf("\nFirst 10 Results:\n");
    for (j = 0; j < 10; j++) {
      if (Z_c[i] == 0) {
        break;
      } else {
        printf("C: Z[%d] = %.2f\n", j, Z_c[j]);
      }
    }

    printf("\nDuration = %.2f \n\n", (double)duration);

    // free memory
    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);
  }

  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// x86-64 assembly kernel

// C kernel
void saxpy_c(float *X, float *Y, float *Z, int n, float A) {
  printf("N = %d\n", n);
  printf("A = %f\n", A);
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
  int vector_sizes[] = {3, 1 << 20, 1 << 24, 1 << 30};
  int c_runtimes[3];
  int asm_runtimes[3];

  for (i = 0; i < 1; i++) { //only picks first for testing
    A = rand() % 21;

    printf("size = %d \n", vector_sizes[i]);
    printf("A = %.2f \n\n", A);

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

    for (j = 0; j < vector_sizes[i]; j++) {
      printf("Current iteration of j = %d \n", j);
      float n = rand() % 21;
      X[j] = Y[j] = n;
      printf("X vector position %d = %f \n", j, X[j]);
      printf("Y vector position %d = %f \n\n", j, Y[j]);
    }

    // call C kernel
    saxpy_c(X, Y, Z_c, vector_sizes[i], A);

    // call x86-64 assembly kernel

    // C Output
    printf("\nResult:\n");
    for (i = 0; i < (vector_sizes[i] < 10 ? vector_sizes[i] : 10); i++) {
      printf("C: Z[%d] = %.2f\n", i, Z_c[i]);
    }

    // free memory
    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);
  }

  return 0;
}

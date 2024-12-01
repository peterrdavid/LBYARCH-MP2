#include <stdio.h>
#include <stdlib.h>

// x86-64 assembly kernel

// C kernel
void saxpy_c(float *X, float *Y, float *Z, int n, float A) {
  for (int i = 0; i < n; i++) {
    Z[i] = A * X[i] + Y[i]; // SAXPY (A * X + Y) function
  }
}

int main() {
  int n; // vector size
  int i; // index
  int j;
  float *X, *Y;       // pointers to vectors X and Y (input vectors)
  float *Z_c, *Z_asm; // pointers to vectors Z for C and x86-64 assembly (result
                      // vectors)
  float A;            // scalar values
  int vector_sizes[] = {1 << 20, 1 << 24, 1 << 30};
  int c_runtimes[3];
  int asm_runtimes[3];

  // input scalar value
  printf("Enter scalar value (A): ");
  if (scanf("%f", &A) != 1) {
    printf("Invalid input.\n");
    return -1;
  }

  for (i = 0; i < 3; i++) {
    // free memory
    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);

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

    for (j = 0; j < vector_sizes[i]; i++) {
      X[i] = Y[i] = rand() % 20;
    }
  }

  // call C kernel
  saxpy_c(X, Y, Z_c, n, A);

  // call x86-64 assembly kernel

  // C Output
  printf("\nResult:\n");
  for (i = 0; i < (n < 10 ? n : 10); i++) {
    printf("C: Z[%d] = %.2f\n", i, Z_c[i]);
  }

  // free allocated memory
  free(X);
  free(Y);
  free(Z_c);
  free(Z_asm);

  return 0;
}

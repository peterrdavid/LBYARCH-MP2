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
    int n;                  // vector size
    int i;                  // index
    float *X, *Y;           // pointers to vectors X and Y (input vectors)
    float *Z_c, *Z_asm;     // pointers to vectors Z for C and x86-64 assembly (result vectors)
    float A;                // scalar value

    // input vector size
    printf("Enter vector size (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return -1;
    }

    // input scalar value
    printf("Enter scalar value (A): ");
    if (scanf("%f", &A) != 1) {
        printf("Invalid input.\n");
        return -1;
    }

    // allocate memory
    X = (float *)malloc(n * sizeof(float));
    Y = (float *)malloc(n * sizeof(float));
    Z_c = (float *)malloc(n * sizeof(float));
    Z_asm = (float *)malloc(n * sizeof(float));

    if (!X || !Y || !Z_c || !Z_asm) {
        printf("Memory allocation failed.\n");
        free(X);
        free(Y);
        free(Z_c);
        free(Z_asm);
        return -1;
    }

    // input vector X values
    printf("\nEnter %d elements for vector X:\n", n);
    for (i = 0; i < n; i++) {
        printf("X[%d] = ", i);
        if (scanf("%f", &X[i]) != 1) {
            printf("Invalid input.\n");
            free(X);
            free(Y);
            free(Z_c);
            free(Z_asm);
            return -1;
        }
    }

    // input vector Y values
    printf("\nEnter %d elements for vector Y:\n", n);
    for (i = 0; i < n; i++) {
        printf("Y[%d] = ", i);
        if (scanf("%f", &Y[i]) != 1) {
            printf("Invalid input.\n");
            free(X);
            free(Y);
            free(Z_c);
            free(Z_asm);
            return -1;
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

#include <stdio.h>
#include <stdlib.h>

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

    return 0;
}

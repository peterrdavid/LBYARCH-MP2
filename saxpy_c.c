#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// x86-64 assembly kernel
extern void saxpy_asm(float *X, float *Y, float *Z, int n, float A);

// C kernel
void saxpy_c(float *X, float *Y, float *Z, int n, float A) {
  for (int i = 0; i < n; i++) {
    Z[i] = A * X[i] + Y[i]; // SAXPY (A * X + Y) function
  }
}

int main() {
  int i;  
  int j;
  float A;         
  float *X, *Y;       
  float *Z_c, *Z_asm;
  int vector_sizes[] = {1 << 20, 1 << 24, 1 << 28}; 
  clock_t start_time, end_time;
  long durations[30];
  long durations_sum = 0;
  int c_avg_runtimes[3];
  int asm_avg_runtimes[3];

  // Initiate random number generation
  srand(time(NULL)); 


  // Loop for the 3 vector sizes (2^20, 2^24, 2^28)
  for (i = 0; i < 3; i++) {
    A = (rand() % 10) + 1; // Assign random value to A


    printf("_________________________________\n");
    printf("\n######### RUN NUMBER %d #########\n", i + 1);

    printf("\nVECTOR SIZE = %d \n", vector_sizes[i]);
    
    printf("_________________________________\n");

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

    for (j = 0; j < vector_sizes[i]; j++) { // assign random values to X and Y
      float n = (rand() % 10) + 1;
      X[j] = Y[j] = n;
    }

    // call C kernel and time each execution, storing into durations
    for (j = 0; j < 30; j++) {
      start_time = clock();
      saxpy_c(X, Y, Z_c, vector_sizes[i], A);
      end_time = clock();
      durations[j] = end_time - start_time;
    }

    // find average runtime
    for (j = 0; j < 30; j++) {
      durations_sum = durations_sum + durations[j];
    }
    c_avg_runtimes[i] = durations_sum / 30;

    // C Output
    printf("C KERNEL\n");
    printf("First 10 Results:\n");
    for (j = 0; j < 10; j++) {
      if (Z_c[j] == 0) {
        break;
      } else {
        printf("Z[%d] = %.2f\n", j, Z_c[j]);
      }
    }

    printf("Duration: %lu \n\n", c_avg_runtimes[i]);

    // call x86-64 assembly kernel and time each execution, storing into durations
    for (j = 0; j < 30; j++) {
      start_time = clock();
      saxpy_asm(X, Y, Z_asm, vector_sizes[i], A);
      end_time = clock();
      durations[j] = end_time - start_time;
    }

    // find average runtime
    for (j = 0; j < 30; j++) {
      durations_sum = durations_sum + durations[j];
    }
    asm_avg_runtimes[i] = durations_sum / 30;

    // Assembly Output
    printf("ASSEMBLY KERNEL\n");
    printf("First 10 Results:\n");
    for (j = 0; j < 10; j++) {
      if (Z_asm[j] == 0) {
        break;
      } else {
        printf("Z[%d] = %.2f\n", j, Z_asm[j]);
      }
    }

    
    printf("Duration: %lu \n\n", asm_avg_runtimes[i]);

    int unequal = memcmp(Z_c, Z_asm, sizeof(Z_c));
    if(!unequal)
        printf("Assembly and C results match.\n");
    else
        printf("Assembly and C results do not match.\n");

    // free memory
    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);
  }

  return 0;
}
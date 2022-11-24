// C Program to multiply two matrix using pthreads without
// use of global variables
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// matrix dimensions
#define M 2
#define N 2
#define P 2
#define MAX_DATA 32

// thread function
void *mult(void *arg) {
  int *temp = (int *)arg;
  int t = 0, i = 0;

  // take the length of row, the length of column will be (i + x), where i is
  // the iterator over data
  int x = temp[0];

  // multiplying row to column
  for (i = 1; i <= x; i++) {
    t += temp[i] * temp[i + x];
  }

  // the result
  int *result = (int *)malloc(sizeof(int));
  *result = t;

  // returing result and exiting thread
  pthread_exit(result);
}

// Driver code
int main() {

  int matA[M][N] = {{1, 0}, {0, 1}};
  int matB[N][P] = {{2, 0}, {0, 2}};

  // row and col size of mat A and B
  int ar = M, ac = N, br = N, bc = P;

  // for iterations
  int i, j, k;

  // max size of the resultant matrix
  int cdim = ar * bc;

  // array of threads to compute each row of resultant matrix
  pthread_t *threads;
  threads = (pthread_t *)malloc(cdim * sizeof(pthread_t));

  // thread counter
  int count = 0;

  //  data sent to thread
  int *temp = NULL;

  // iterate matrix A vertically
  for (i = 0; i < ar; i++)
    // iterate matrix B horizontally
    for (j = 0; j < bc; j++) {

      // storing row and column elements in data
      temp = (int *)malloc((MAX_DATA) * sizeof(int));
      temp[0] = ac;

      // col of A to multiply
      for (k = 0; k < ac; k++) {
        temp[k + 1] = matA[i][k];
      }

      // row of matrix b to multiply
      for (k = 0; k < br; k++) {
        temp[k + ac + 1] = matB[k][j];
      }

      // prodoocciinngggg threeaddddsss
      pthread_create(&threads[count++], NULL, mult, (void *)(temp));
    }

  printf("The resultant matrix:- \n");
  for (i = 0; i < cdim; i++) {
    void *k;

    // terminate threads, get return values
    pthread_join(threads[i], &k);

    int *result = (int *)k;
    printf("%d ", *result);
    if ((i + 1) % bc == 0)
      printf("\n");
  }

  return 0;
}

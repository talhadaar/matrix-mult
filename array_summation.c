#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct SummationItem {
  int a;
  int b;
  int *array;
};

void *summation(void *arg) {
  struct SummationItem *details = (struct SummationItem *)arg;

  int *sum = malloc(sizeof(int));
  *sum = 0;
  for (int i = details->a; i < details->b; i++) {
    *sum += details->array[i];
  }
  pthread_exit(sum);
}

int main(int argc, char **argv) {
  int N = atoi(argv[1]);
  int *array = malloc(sizeof(int) * 1000);

  // populate array and display
  for (int i = 0; i < 1000; i++) {
    array[i] = rand() % 1000;
    printf("%i ", array[i]);
  }
    printf("\n");

  // array of threads to sum each range of the array
  pthread_t *threads;
  threads = (pthread_t *)malloc(N * sizeof(pthread_t));

  // thread counter
  int count = 0;

  //  data sent to thread
  struct SummationItem *temp = NULL;

  // range of each
  int range = 1000 / N;

  for (int i = 0; i < N; i++) {
    temp = (struct SummationItem*)malloc(sizeof(struct SummationItem));
    temp->a = i * range;
    temp->b = (i+1)*range;
    temp->array = array;

    pthread_create(&threads[count++], NULL, summation, (void *)(temp));
  }

// get results from all threads
    int sum =0;
    void *thread_result;
    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], &thread_result);
        sum+= *(int*)thread_result;
    }
    
    printf("Summation result: %i", sum);
  return 0;
}
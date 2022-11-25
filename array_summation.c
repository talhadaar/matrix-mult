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

  printf("\nTHREAD %d - Sum of Range [%i, %i]: %i", pthread_self(), details->a,
         details->b, *sum);

  pthread_exit(sum);
}

int main(int argc, char **argv) {

  // doing this takay seg fault se dimaagh kharaab na hou
  if (argc == 1)
    exit(EXIT_FAILURE);

  int N = atoi(argv[1]);
  int *array = malloc(sizeof(int) * 1000);

  // populate array
  for (int i = 0; i < 1000; i++) {
    array[i] = rand() % 10;
  }

  // create array of threads to sum each range of the array
  pthread_t *threads;
  threads = (pthread_t *)malloc(N * sizeof(pthread_t));

  // thread counter
  int count = 0;

  //  of data sent to thread
  struct SummationItem *temp = NULL;

  // width of each summation
  int range = 1000 / N;

  for (int i = 0; i < N; i++) {
    // create a new summation info item
    temp = (struct SummationItem *)malloc(sizeof(struct SummationItem));
    temp->a = i * range;
    temp->b = (i + 1) * range - 1;
    temp->array = array;

    printf("\nRange %i: [%i, %i]", i, temp->a, temp->b);
    pthread_create(&threads[count++], NULL, summation, (void *)(temp));
  }

  // get results from all threads
  int sum = 0;
  void *thread_result;
  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], &thread_result);
    sum += *(int *)thread_result;
  }

  printf("\nSummation result: %i", sum);
  return 0;
}
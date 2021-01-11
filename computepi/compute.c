#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "compute.h"

/* Number of hits */
unsigned int hits;

/* Mutex Semaphore */
pthread_mutex_t mutex;

/* Thread function */
void * thread_function(void * data) {
    /* The input variable contains the number of points that the thread must
     * calculate */
    int points = *((int *)data);
    int inside_points = 0;
    double x, y;
    struct drand48_data rand_buffer;
    srand48_r(time(NULL), &rand_buffer);
    /* TODO: Implement the loop that obtains the random points and counts how
     * many of those lay within the circumference of radius 1 */
    for(int i = 0; i < points; i++){

      drand48_r(&rand_buffer, &x);
      drand48_r(&rand_buffer, &y);
      printf("X e Y: %lf %lf \n", x ,y);
      int z = x*x + y*y;
      if (z < 1){
          pthread_mutex_lock(&mutex);
          inside_points += 1;
          pthread_mutex_unlock(&mutex);}
    }
    /* TODO: Add the count to the global variable hits in mutual exclusion */
    pthread_mutex_lock(&mutex);
    hits = hits + inside_points;
    pthread_mutex_unlock(&mutex);

    return NULL;

}

void compute(int npoints, int nthreads) {
    pthread_mutex_init(&mutex, NULL);
    int points_to_calculate = (int)(npoints / nthreads);
    int last_points = (int) (points_to_calculate + (npoints - points_to_calculate * nthreads));
    /* TODO: Erase the following line: */

    /* TODO: Launch the threads that will count the points */
    pthread_t thread_id[nthreads];
    for(int i = 0; i < nthreads - 1; i++){
        sleep(1);
        pthread_create(&thread_id[i], NULL, &thread_function, &points_to_calculate);}
    sleep(1);
    pthread_create(&thread_id[nthreads-1], NULL, &thread_function, &last_points);
    /* TODO: Wait for all threads to finish */

    for(int i = 0; i < nthreads; i++){
        pthread_join(thread_id[i], NULL);}
    /* TODO: print the ratio of points that meet the criteria */
    double ratio = ((double) hits / (double) npoints);
    printf("------------------\n");
    printf("hits: %d\n", hits);
    printf("npoints: %d\n", npoints);
    printf("ratio: %lf\n", ratio);
    double pi = ratio * 4;
    printf("------------------\n");
    printf("Value of Pi: %lf\n", pi);
    printf("------------------\n");
    /* The following print string can be used to print the calculated value:
     * printf("%.8f\n", VALUE_OF_PI);
     * where VALUE_OF_PI is the floating-point value to be printed.
     */

}


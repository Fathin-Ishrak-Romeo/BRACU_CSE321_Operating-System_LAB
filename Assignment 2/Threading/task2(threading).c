#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_INTEGERS 5

int current_number = 1;

pthread_mutex_t mutex;

void *thread_function(void *arg) {
    int thread_id = *(int *)arg; 

    pthread_mutex_lock(&mutex); 

    for (int i = 0; i < NUM_INTEGERS; i++) {
        printf("Thread %d prints %d\n", thread_id, current_number);
        current_number++;
    }

    pthread_mutex_unlock(&mutex); 
    free(arg); 
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        int *thread_id = malloc(sizeof(int)); 
        *thread_id = i;
        if (pthread_create(&threads[i], NULL, thread_function, thread_id) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); 
    return 0;
}

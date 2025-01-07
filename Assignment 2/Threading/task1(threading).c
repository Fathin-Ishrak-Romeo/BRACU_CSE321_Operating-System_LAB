#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
pthread_cond_t cond;
int current_thread = 0; 

void *thread_function(void *arg) {
    int thread_id = *(int *)arg; 

    pthread_mutex_lock(&mutex); 
    while (thread_id != current_thread) {
        pthread_cond_wait(&cond, &mutex); 
    }

    printf("thread-%d running\n", thread_id + 1);
    sleep(1); 
    printf("thread-%d closed\n", thread_id + 1);

    current_thread++;
    pthread_cond_broadcast(&cond); 
    pthread_mutex_unlock(&mutex); 

    free(arg); 
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

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
    pthread_cond_destroy(&cond); 
    return 0;
}

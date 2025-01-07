#include <pthread.h>   
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX 10
#define BUFLEN 6
#define NUMTHREAD 2

void *consumer(int *id);
void *producer(int *id);

char buffer[BUFLEN];
char source[BUFLEN];
int pCount = 0;
int cCount = 0;
int buflen;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREAD] = {0, 1};
int i = 0;
int j = 0;

int main() {
    pthread_t thread[NUMTHREAD];
    strcpy(source, "abcdef");
    buflen = strlen(source);

    pthread_create(&thread[0], NULL, (void *)producer, (void *)&thread_id[0]);

    pthread_create(&thread[1], NULL, (void *)consumer, (void *)&thread_id[1]);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    return 0;
}

void *producer(int *id) {
    int currentPos = 0;
    while (pCount < MAX) {
        pthread_mutex_lock(&count_mutex);

        while (i == buflen) {
            pthread_cond_wait(&full, &count_mutex);
        }

        buffer[j] = source[currentPos % buflen];
        printf("%d produced  %c  by Thread  %d\n", pCount, buffer[j], *id);
        j = (j + 1) % buflen;
        i++;
        pCount++;
        currentPos++;

        pthread_cond_signal(&nonEmpty);
        pthread_mutex_unlock(&count_mutex);
        
        usleep(100000);
    }
    pthread_exit(0);
}

void *consumer(int *id) {
    char item;
    while (cCount < MAX) {
        pthread_mutex_lock(&count_mutex);

        while (i == 0) {
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }

        item = buffer[(j - i)];
        printf("%d consumed  %c  by Thread  %d\n", cCount, item, *id);
        i--;
        cCount++;

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&count_mutex);
        
        usleep(200000);
    }
    pthread_exit(0);
}
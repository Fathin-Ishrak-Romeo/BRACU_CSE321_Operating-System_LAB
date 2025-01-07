#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    char *name;
    int result;
} ThreadData;

int calculate_ascii_sum(const char *name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i];
    }
    return sum;
}

void *calculate_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->result = calculate_ascii_sum(data->name);
    return NULL;
}

void *compare_results(void *arg) {
    int *results = (int *)arg;

    if (results[0] == results[1] && results[1] == results[2]) {
        printf("Youreka\n");
    } else if (results[0] == results[1] || results[1] == results[2] || results[0] == results[2]) {
        printf("Miracle\n");
    } else {
        printf("Hasta la vista\n");
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3, compareThread;
    ThreadData data1, data2, data3;
    int results[3];

    data1.name = "Alice";
    data2.name = "Bob";
    data3.name = "Charlie";

    pthread_create(&thread1, NULL, calculate_sum, (void *)&data1);
    pthread_create(&thread2, NULL, calculate_sum, (void *)&data2);
    pthread_create(&thread3, NULL, calculate_sum, (void *)&data3);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    results[0] = data1.result;
    results[1] = data2.result;
    results[2] = data3.result;

    pthread_create(&compareThread, NULL, compare_results, (void *)results);

    pthread_join(compareThread, NULL);

    return 0;
}

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define MaxCrops 5
#define warehouseSize 5

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
char crops[warehouseSize] = {'R', 'W', 'P', 'S', 'M'};
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'};
pthread_mutex_t mutex;

void printWarehouse() {
    for(int i = 0; i < warehouseSize; i++) {
        printf("%c", warehouse[i]);
    }
    printf("\n");
}

void *Farmer(void *far) {
    int *farmer_id = (int *)far;
    
    for(int count = 0; count < MaxCrops; count++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        if (warehouse[in] == 'N') {
            warehouse[in] = crops[in];
            printf("Farmer %d: Insert crops %c at %d\n", *farmer_id, crops[in], in);
            if(count == MaxCrops - 1) {  
                printf("Farmer%d: ", *farmer_id);
                printWarehouse();
            }
            in = (in + 1) % warehouseSize;
        }
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        
        usleep(200000);
    }
    pthread_exit(0);
}

void *ShopOwner(void *sho) {
    int *shop_owner_id = (int *)sho;
    
    for(int count = 0; count < MaxCrops; count++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        if (warehouse[out] != 'N') {
            char crop = warehouse[out];
            printf("Shop owner %d: Remove crops %c from %d\n", *shop_owner_id, crop, out);
            warehouse[out] = 'N';
            
            if(count == MaxCrops - 1) {  
                printf("ShopOwner%d: ", *shop_owner_id);
                printWarehouse();
            }
            out = (out + 1) % warehouseSize;
        }
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        
        usleep(300000);
    }
    pthread_exit(0);
}

int main() {
    pthread_t Far[5], Sho[5];
    int a[5] = {1, 2, 3, 4, 5};
    
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize);
    sem_init(&full, 0, 0);
    
    for(int i = 0; i < 5; i++) {
        pthread_create(&Far[i], NULL, Farmer, (void *)&a[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_create(&Sho[i], NULL, ShopOwner, (void *)&a[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(Far[i], NULL);
        pthread_join(Sho[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}
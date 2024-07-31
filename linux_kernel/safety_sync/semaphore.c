#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_CONNECTIONS 3

sem_t db_semaphore;

void* access_database(void* arg) {
    sem_wait(&db_semaphore); // 请求数据库连接

    printf("Thread %s is accessing the database\n", (char*)arg);
    sleep(2); // 模拟数据库操作

    printf("Thread %s is releasing the database\n", (char*)arg);
    sem_post(&db_semaphore); // 释放数据库连接

    return NULL;
}

int main() {
    pthread_t threads[5];
    sem_init(&db_semaphore, 0, MAX_CONNECTIONS);

    for (int i = 0; i < 5; i++) {
        char* thread_id = malloc(sizeof(char) * 2);
        sprintf(thread_id, "%d", i+1);
        pthread_create(&threads[i], NULL, access_database, thread_id);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&db_semaphore);
    return 0;
}

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
int shared_resource = 0;

void *thread_function(void *arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&lock);
        shared_resource++;
        printf("Thread %s incremented shared resource to %d\n", (char *)arg, shared_resource);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&thread1, NULL, thread_function, "1");
    pthread_create(&thread2, NULL, thread_function, "2");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}

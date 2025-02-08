#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define BUFFER_SIZE     5
#define NUM_THREAD      2 
#define MAX_NUM         100

__uint32_t buffer[BUFFER_SIZE] = {0};
__uint32_t count = 0;
pthread_mutex_t mutex;
pthread_cond_t cond_var;

void *thread_producer(void *arg) {
    while(1) {
        pthread_mutex_lock(&mutex); 

        while (count == BUFFER_SIZE) {
            // Buffer full, producer waits...
            printf("\nBuffer full. Producer is waiting...\n\n");
            pthread_cond_wait(&cond_var, &mutex); 
        }  

        buffer[count] = rand() % MAX_NUM;
        printf("Producer: Write %d to buffer\n", buffer[count]);
        count++;
        pthread_cond_signal(&cond_var);  // Notify the consumer
        pthread_mutex_unlock(&mutex);

        sleep(1);  // Simulating time delay
    }
}

void *thread_consumer(void *arg) {
    while(1) {   
        pthread_mutex_lock(&mutex); 
        
        while (count == 0) {
            // Buffer empty, consumer waits...
            printf("\nBuffer empty. Consumer is waiting...\n\n");
            pthread_cond_wait(&cond_var, &mutex); 
        } 

        printf("Consumer: Read %d from buffer\n", buffer[count - 1]); 
        count--;
        pthread_cond_signal(&cond_var);  // Notify the producer
        pthread_mutex_unlock(&mutex);

        sleep(2);  // Simulating time delay
    }
}

int main() {

    pthread_t thread[NUM_THREAD]; // thread identifiers

    // Initialize mutex and condition variable
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);

    // Create producer thread
    if (pthread_create(&thread[0], NULL, thread_producer, NULL) != 0) {
        perror("Failed to create producer thread");
        exit(1);
    }

    // Create consumer thread
    if (pthread_create(&thread[1], NULL, thread_consumer, NULL) != 0) {
        perror("Failed to create consumer thread");
        exit(1);
    }

    // Join threads (this will block until threads terminate, which in this case won't happen)
    if ((pthread_join(thread[0], NULL) != 0) || (pthread_join(thread[1], NULL) != 0)) {
        perror("Failed to join threads");
        exit(1);
    }

    // Clean up mutex and condition variable
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);

    return 0;
}

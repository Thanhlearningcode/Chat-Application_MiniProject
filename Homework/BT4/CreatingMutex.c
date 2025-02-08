#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function to be executed by each thread
void *thread_function(void *arg) {
    printf("Thread %ld ID: %s\n", pthread_self(), (char *)arg);
    sleep(2);
    printf("Sub thread exited\n");
    pthread_exit(NULL);  
}

int main() {
    pthread_t thread;  // thread identifier

    // Dynamically allocate memory for the thread message
    char *message = "Hello from thread";

    // Create a new thread and run
    if (pthread_create(&thread, NULL, thread_function, (void *)message) != 0) {
        perror("Failed to create thread");
        exit(1);
    }
        
    // Wait for the thread to finish
    if (pthread_join(thread, NULL) != 0) {
        perror("Failed to join thread");
        exit(1);
    }

    printf("Main thread exited\n");

    return 0;
}

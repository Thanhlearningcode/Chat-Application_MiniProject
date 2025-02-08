#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Print the process ID before forking
    printf("Before fork: %d\n", getpid());

    pid_t pid = fork();  // Create a new process

    if (pid == -1) {
        // Handle fork failure
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("This is the child process: %d\n", getpid());
    } else {
        // Parent process
        printf("This is the parent process: %d\n", getpid());
        wait(NULL);  // Wait for the child process to finish
    }

    return EXIT_SUCCESS;
}

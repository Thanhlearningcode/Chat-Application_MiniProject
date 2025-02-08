#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a new process

    printf("Orphaned process simulation\n");

    if (pid == 0) {
        // Child process: Sleep to become orphaned after parent exits
        printf("This is the child process: %d\n", getpid());
        printf("Child process sleeps for some seconds...\n");
        sleep(50);  // Sleep to simulate orphaned state
    } else {
        // Parent process: Exit immediately, leaving the child as orphaned
        printf("This is the parent process: %d\n", getpid());
        printf("Parent process exits immediately...\n");
    }

    return 0;
}

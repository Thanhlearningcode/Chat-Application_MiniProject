#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a new process

    printf("Zombie process simulation\n");

    if (pid == 0) {
        // Child process: Exit immediately and become a zombie
        printf("This is the child process: %d\n", getpid());
        printf("Child process exits immediately...\n");
        _exit(0);  // Exit without calling return() to avoid flushing stdio buffers
    } else {
        // Parent process: Waits indefinitely, leaving the child process as a zombie
        printf("This is the parent process: %d\n", getpid());
        printf("Parent process waits indefinitely, child will become a zombie...\n");
        while (1);  // Simulate a long-running process
    }

    return 0;
}

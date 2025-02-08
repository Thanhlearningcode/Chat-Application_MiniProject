#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function for the child process
void child_signal_handler(int sig) {
    switch (sig) {
        case SIGINT:
            printf("Child caught SIGINT (Ctrl+C)\n");
            break;
        case SIGTERM:
            printf("Child caught SIGTERM (Termination signal). Exiting...\n");
            exit(EXIT_SUCCESS);  // Exit gracefully on termination
            break;
        case SIGUSR1:
            printf("Child caught SIGUSR1 (User-defined signal)\n");
            break;
        default:
            printf("Child caught signal %d\n", sig);
    }
}

int main() {
    pid_t pid;

    // Create a new process (fork)
    pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        if (signal(SIGINT, child_signal_handler) == SIG_ERR) {
            perror("Unable to register SIGINT handler");
            exit(EXIT_FAILURE);
        }

        if (signal(SIGTERM, child_signal_handler) == SIG_ERR) {
            perror("Unable to register SIGTERM handler");
            exit(EXIT_FAILURE);
        }

        if (signal(SIGUSR1, child_signal_handler) == SIG_ERR) {
            perror("Unable to register SIGUSR1 handler");
            exit(EXIT_FAILURE);
        }

        printf("Child process running with PID: %d\n", getpid());
        printf("Child process is waiting for signals...\n");

        while (1) {
            // Keep the child process running indefinitely, waiting for signals
            sleep(1);
        }
    } else {
        // Parent process
        printf("Parent process (PID: %d) will send signals to child (PID: %d)\n", getpid(), pid);
        
        // Give the child some time to start
        sleep(2);

        // Send different signals to the child process
        kill(pid, SIGINT);    // Send SIGINT
        sleep(1);
        kill(pid, SIGUSR1);   // Send SIGUSR1
        sleep(1);
        kill(pid, SIGTERM);   // Send SIGTERM, which will terminate the child

        // Wait for the child to exit
        wait(NULL);
        printf("Parent process exits.\n");
    }

    return EXIT_SUCCESS;
}

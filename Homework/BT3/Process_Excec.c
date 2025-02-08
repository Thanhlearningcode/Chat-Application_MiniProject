#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Ensure correct number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid;

    // Print the current process ID before forking
    printf("Before fork: %d\n", getpid());

    pid = fork();

    if (pid == -1) {
        // Handle fork failure
        perror("Fork failed");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        // Child process
        printf("This is the child process: %d\n", getpid());

        int mode = atoi(argv[1]);

        if (mode == 1) {
            // Display process information
            printf("Child process info:\n");
            char pid_str[20];
            snprintf(pid_str, sizeof(pid_str), "%d", getpid());
            // Replace child process with the 'ps' command
            execlp("ps", "ps", "-p", pid_str, "-f", NULL);
        } else if (mode == 2) {
            // Display the list of files in the current directory
            printf("List of files:\n");
            // Replace child process with the 'ls' command
            execlp("ls", "ls", "-l", NULL);
        } else {
            fprintf(stderr, "Invalid argument. Please provide 1 or 2.\n");
            return EXIT_FAILURE;
        }
    } else {
        // Parent process
        printf("This is the parent process: %d\n", getpid());
        wait(NULL);  // Wait for the child process to finish
    }

    return EXIT_SUCCESS;
}

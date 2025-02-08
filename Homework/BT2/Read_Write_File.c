#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h> 
#include <string.h>   // For strlen()

#define MAX_BUFFER 1024

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <filename> <r/w> <data/num_bytes>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *file_path = argv[1];
    char *mode_type = argv[2];
    char *content = argv[3];
    int access_mode = 0;
    int file_flags = O_CREAT | O_APPEND;
    mode_t permission = S_IRUSR | S_IWUSR;

    if (strlen(mode_type) != 1 || (*mode_type != 'r' && *mode_type != 'w')) {
        fprintf(stderr, "Error: Mode must be 'r' (read) or 'w' (write).\n");
        return EXIT_FAILURE;
    }

    printf("File: %s\nMode: %s\nContent: %s\n\n", file_path, (*mode_type == 'r') ? "Read" : "Write", content);

    access_mode = (*mode_type == 'r') ? O_RDONLY : O_WRONLY;
    int file_descriptor = open(file_path, file_flags | access_mode, permission);
    
    if (file_descriptor < 0) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    if (*mode_type == 'r') {
        int read_size = atoi(content);
        if (read_size <= 0) {
            fprintf(stderr, "Error: Number of bytes to read must be greater than 0.\n");
            close(file_descriptor);
            return EXIT_FAILURE;
        }
        
        char buffer[MAX_BUFFER] = {'\0'};
        ssize_t bytes_read = read(file_descriptor, buffer, read_size);
        if (bytes_read < 0) {
            perror("Error reading file");
            close(file_descriptor);
            return EXIT_FAILURE;
        }
        printf("Read from file: %s\n", buffer);
    } else {
        ssize_t bytes_written = write(file_descriptor, content, strlen(content));
        if (bytes_written < 0) {
            perror("Error writing to file");
            close(file_descriptor);
            return EXIT_FAILURE;
        }
    }

    close(file_descriptor);
    return EXIT_SUCCESS;
}
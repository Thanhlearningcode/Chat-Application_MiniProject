#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  // For open() flags
#include <unistd.h> // For read(), write(), close()
#include <sys/types.h>
#include <sys/stat.h> // For file mode constants
#include <time.h>

int main(int argc, char *argv[]) {

    // Check if the user has provided a filename
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;

    // Get the status of the file
    if (stat(argv[1], &fileStat) == -1) {
        perror("Error getting file status");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("File size: %ld bytes\n", fileStat.st_size);
    printf("Block size: %ld bytes\n", fileStat.st_blksize);
    printf("Number of blocks: %ld\n", fileStat.st_blocks);

    // File permissions
    printf("File permissions: ");
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");  // Directory
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-"); // Owner read
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-"); // Owner write
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-"); // Owner execute
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-"); // Group read
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-"); // Group write
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-"); // Group execute
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-"); // Others read
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-"); // Others write
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-"); // Others execute
    printf("\n");

    // File type
    if (S_ISREG(fileStat.st_mode)) {
        printf("File type: Regular file\n");
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("File type: Directory\n");
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("File type: Symbolic link\n");
    } else {
        printf("File type: Other\n");
    }

    // Time information
    char timeBuf[256];
    struct tm *timeinfo;

    // Last access time
    timeinfo = localtime(&fileStat.st_atime);
    strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last accessed: %s\n", timeBuf);

    // Last modification time
    timeinfo = localtime(&fileStat.st_mtime);
    strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last modified: %s\n", timeBuf);

    // Last status change time
    timeinfo = localtime(&fileStat.st_ctime);
    strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last status change: %s\n", timeBuf);

    return 0;
}
/******************************************************************************
 * Author: Ryan Morgan
 * Date: 11/15/2024
 * Class: CPE2600
 * File: finfo.c
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void print_permissions(mode_t mode) {
    // Print file permissions in a user-readable format
    char perms[10] = "---------"; // 10 chars for permissions
    
    if (S_IRUSR & mode) perms[0] = 'r';
    if (S_IWUSR & mode) perms[1] = 'w';
    if (S_IXUSR & mode) perms[2] = 'x';
    if (S_IRGRP & mode) perms[3] = 'r';
    if (S_IWGRP & mode) perms[4] = 'w';
    if (S_IXGRP & mode) perms[5] = 'x';
    if (S_IROTH & mode) perms[6] = 'r';
    if (S_IWOTH & mode) perms[7] = 'w';
    if (S_IXOTH & mode) perms[8] = 'x';
    
    printf("Permissions: %s\n", perms);
}

void print_file_type(mode_t mode) {
    // Print the type of the file
    if (S_ISREG(mode)) {
        printf("File type: Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("File type: Directory\n");
    } else if (S_ISLNK(mode)) {
        printf("File type: Symbolic link\n");
    } else if (S_ISCHR(mode)) {
        printf("File type: Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("File type: Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("File type: FIFO (named pipe)\n");
    } else if (S_ISSOCK(mode)) {
        printf("File type: Socket\n");
    } else {
        printf("File type: Unknown\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct stat file_info;

    // Use stat to get file info
    if (stat(filename, &file_info) == -1) {
        perror("Error retrieving file information");
        return 1;
    }

    // Print the file type
    print_file_type(file_info.st_mode);

    // Print file permissions
    print_permissions(file_info.st_mode);

    // Print the owner (user ID)
    printf("Owner (UID): %d\n", file_info.st_uid);

    // Print file size in bytes
    printf("Size: %ld bytes\n", file_info.st_size);

    // Print the last modification time
    struct tm *time_info = localtime(&file_info.st_mtime);
    if (time_info == NULL) {
        perror("Error formatting modification time");
        return 1;
    }
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("Last modified: %s\n", time_str);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#define MAX_PATH_LENGTH 1024
#define MAX_STRING_LENGTH 256

// Function to replace strings in a file
void replace_strings(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Lakukan pembacaan file per baris
    while ((read = getline(&line, &len, file)) != -1) {
        // Lakukan penggantian string
        char *ptr;
        while ((ptr = strstr(line, "m4LwAr3")) != NULL) {
            strncpy(ptr, "[MALWARE]", 9);
        }
        while ((ptr = strstr(line, "5pYw4R3")) != NULL) {
            strncpy(ptr, "[SPYWARE]", 9);
        }
        while ((ptr = strstr(line, "R4nS0mWaR3")) != NULL) {
            strncpy(ptr, "[RANSOMWARE]", 12);
        }

        // Tulis kembali baris ke file
        fseek(file, -read, SEEK_CUR);
        fwrite(line, 1, strlen(line), file);
    }

    fclose(file);
    if (line)
        free(line);

    // Catat penghapusan string yang berhasil
    FILE *log_file = fopen("virus.log", "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    fprintf(log_file, "[%02d-%02d-%d][%02d:%02d:%02d] Suspicious string at %s successfully replaced!\n",
            local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
            local->tm_hour, local->tm_min, local->tm_sec,
            file_path);
    fclose(log_file);
}

// Function to monitor a folder recursively
void monitor_folder(const char *folder_path) {
    struct dirent *dp;
    DIR *dir = opendir(folder_path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    // Loop through all files in the folder
    while ((dp = readdir(dir)) != NULL) {
        char path[MAX_PATH_LENGTH];
        snprintf(path, sizeof(path), "%s/%s", folder_path, dp->d_name);

        // Skip "." and ".."
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        struct stat statbuf;
        if (stat(path, &statbuf) == -1) {
            perror("Error getting file status");
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            // If directory, recursively call the function to monitor it
            monitor_folder(path);
        } else {
            // If file, replace strings
            replace_strings(path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    // Ensure folder path argument is provided
    if (argc != 2) {
        printf("Usage: %s folder_path\n", argv[0]);
        return 1;
    }

    char folder_path[MAX_PATH_LENGTH];
    strncpy(folder_path, argv[1], sizeof(folder_path));

    // Ensure the provided folder path is valid
    DIR *dir = opendir(folder_path);
    if (dir == NULL) {
        perror("Invalid folder path");
        return 1;
    }
    closedir(dir);

    // Create a daemon process using fork()
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error forking");
        return 1;
    }

    // If parent process, exit
    if (pid > 0) {
        printf("Daemon process started with PID %d\n", pid);
        return 0;
    }

    // If child process, continue as daemon
    // Change the process image using exec()
    if (setsid() == -1) {
        perror("Error creating new session");
        return 1;
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Execute the monitoring functionality
    while (1) {
        monitor_folder(folder_path);
        sleep(15); // 15-second delay
    }

    return 0;
}

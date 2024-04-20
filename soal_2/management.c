#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>

#define LOG_FILE "../history.log" // Change path to outside library folder
#define BACKUP_DIR "../library/backup" // Change path to outside library folder
#define FILE_URL "https://drive.google.com/uc?export=download&id=1rUIZmp10lXLtCIH3LAZJzRPeRks3Crup"
#define FILE_NAME "../library.zip" // Change path to outside library folder

#define MAX_FILENAME_LEN 256
#define MAX_HISTORY_LEN 512 // Increased buffer size for log entries

// Deklarasi fungsi
void downloadAndUnzipFile();
void decryptFileName(char *filename);
void manageFiles();
void backupFiles();
void restoreFiles();
void signalHandler(int signum);
void logAction(const char *filename, const char *action);
void download_and_extract_file();
void renameDecryptedFiles(char *filename);
void deleteDecryptedFiles(char *filename);

// Variabel global
int mode = 0; // 0: default, 1: backup, 2: restore

char rot19(char c) {
    if (isalpha(c)) {
        char base = islower(c) ? 'a' : 'A';
        return (c - base + 7) % 26 + base;
    }
    return c;
}

void decryptFileName(char *filename) {
    char decryptedFilename[MAX_FILENAME_LEN];
    int i = 0;
    while (filename[i] != '\0') {
        decryptedFilename[i] = rot19(filename[i]);
        i++;
    }
    decryptedFilename[i] = '\0';

    // Rename file using the decrypted filename
    if (rename(filename, decryptedFilename) == 0) {
        logAction(filename, "Decrypted");
    } else {
        perror("Error renaming file");
    }
}

void renameDecryptedFiles(char *filename) {
    if (strstr(filename, "r3N4mE") != NULL) {
        char *extension = strrchr(filename, '.'); // Find file extension
        if (extension == NULL) {
            // No extension, rename to "renamed.file"
            if (rename(filename, "renamed.file") == 0) {
                logAction(filename, "Renamed to renamed.file");
            } else {
                perror("Error renaming file");
            }
        } else {
            // Process based on file extension
            if (strcmp(extension, ".ts") == 0) {
                if (rename(filename, "helper.ts") == 0) {
                    logAction(filename, "Renamed to helper.ts");
                } else {
                    perror("Error renaming file");
                }
            } else if (strcmp(extension, ".py") == 0) {
                if (rename(filename, "calculator.py") == 0) {
                    logAction(filename, "Renamed to calculator.py");
                } else {
                    perror("Error renaming file");
                }
            } else if (strcmp(extension, ".go") == 0) {
                if (rename(filename, "server.go") == 0) {
                    logAction(filename, "Renamed to server.go");
                } else {
                    perror("Error renaming file");
                }
            } else {
                if (rename(filename, "renamed.file") == 0) {
                    logAction(filename, "Renamed to renamed.file");
                } else {
                    perror("Error renaming file");
                }
            }
        }
    }
}

void deleteDecryptedFiles(char *filename) {
    if (strstr(filename, "d3Let3") != NULL) {
        if (remove(filename) == 0) {
            logAction(filename, "Deleted successfully");
        } else {
            perror("Error deleting file");
        }
    }
}

void manageFiles() {
    // Change the working directory to the "library" directory
    if (chdir("library") != 0) {
        perror("Error changing directory to library");
        return;
    }

    // Implement the function to decrypt and process regular files
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    // Iterate through files in the "library" directory
    while ((entry = readdir(dir)) != NULL) {
        char filename[MAX_FILENAME_LEN];
        snprintf(filename, sizeof(filename), "%s", entry->d_name);

        // Skip "." and ".." entries
        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0)
            continue;

        // Skip files with number 1 to 6 as the first character in their filenames
        if (isdigit(filename[0]) && filename[0] >= '1' && filename[0] <= '6')
            continue;

        // Menggunakan lstat() untuk mendapatkan informasi tentang file
        if (lstat(filename, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            // Decrypt filename
            decryptFileName(filename);
            
            logAction(filename, "is being processed");
            // Rename and delete decrypted files if necessary
            renameDecryptedFiles(filename);
            deleteDecryptedFiles(filename);
        }
    }

    closedir(dir);

    // Change back to the main directory after processing files in "library"
    if (chdir("..") != 0) {
        perror("Error changing directory back to main directory");
    }
}

void backupFiles() {
    // Change the working directory to the "library" directory
    if (chdir("library") != 0) {
        perror("Error changing directory to library");
        return;
    }

    // Implement the function to backup files
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char filename[MAX_FILENAME_LEN];
        snprintf(filename, sizeof(filename), "%s", entry->d_name);

        // Menggunakan lstat() untuk mendapatkan informasi tentang file
        if (lstat(filename, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            decryptFileName(filename); // Dekripsi nama file

            if (strstr(filename, "m0V3") != NULL) {
                char backupPath[MAX_FILENAME_LEN + sizeof(BACKUP_DIR) + 2]; // Increased buffer size
                snprintf(backupPath, sizeof(backupPath), "%s/%s", BACKUP_DIR, filename);
                rename(filename, backupPath);
                logAction(filename, "Successfully moved to backup.");
            }
        }
    }

    closedir(dir);

    // Change back to the main directory after processing files in "library"
    if (chdir("..") != 0) {
        perror("Error changing directory back to main directory");
    }
}

void restoreFiles() {
    // Change the working directory to the backup directory
    if (chdir(BACKUP_DIR) != 0) {
        perror("Error changing directory to backup directory");
        return;
    }

    // Implement the function to restore files
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char filename[MAX_FILENAME_LEN];
        snprintf(filename, sizeof(filename), "%s", entry->d_name);

        // Menggunakan lstat() untuk mendapatkan informasi tentang file
        if (lstat(filename, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            decryptFileName(filename); // Dekripsi nama file

            if (strstr(filename, "m0V3") != NULL) {
                char restorePath[MAX_FILENAME_LEN + 3]; // Increased buffer size
                snprintf(restorePath, sizeof(restorePath), "../%s", filename);
                rename(entry->d_name, restorePath);
                logAction(filename, "Successfully restored from backup.");
            }
        }
    }

    closedir(dir);

    // Change back to the main directory after processing files in "backup" directory
    if (chdir("..") != 0) {
        perror("Error changing directory back to main directory");
    }
}

void signalHandler(int signum) {
    if (signum == SIGRTMIN) {
        mode = 0;
    } else if (signum == SIGUSR1) {
        mode = 1;
    } else if (signum == SIGUSR2) {
        mode = 2;
    }
}

void logAction(const char *filename, const char *action) {
    FILE *logFile = fopen(LOG_FILE, "a");
    if (logFile != NULL) {
        time_t rawtime;
        struct tm *timeinfo;
        char timestamp[20];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(timestamp, sizeof(timestamp), "%H:%M:%S", timeinfo);
        char username[64]; // Simpan username sementara sebagai "paul"
        fprintf(logFile, "[paul][%s] - %s - %s\n", timestamp, filename, action);
        fclose(logFile);
    }
}

void download_and_extract_file() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execlp("wget", "wget", FILE_URL, "-O", FILE_NAME, "-q", NULL);
        perror("exec wget");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // Download successful
            pid_t pid_unzip = fork();
            if (pid_unzip == 0) {
                execlp("unzip", "unzip", FILE_NAME, NULL);
                perror("exec unzip");
                exit(EXIT_FAILURE);
            } else if (pid_unzip > 0) {
                int status_unzip;
                waitpid(pid_unzip, &status_unzip, 0);
                if (WIFEXITED(status_unzip) && WEXITSTATUS(status_unzip) == 0) {
                    // Unzip successful
                } else {
                    printf("Unzip failed.\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                perror("fork unzip");
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Download failed.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        perror("fork wget");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    // Membuat daemon
    pid_t pid, sid; // Variabel untuk menyimpan PID

    pid = fork(); // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
     * (nilai variabel pid < 0) */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
     * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("./")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Mengatur signal handler
    signal(SIGRTMIN, signalHandler);
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);

    // Create directories if they don't exist
    mkdir("library", 0777);
    mkdir(BACKUP_DIR, 0777);

    // Mengubah mode jika argumen disediakan
    if (argc == 3 && strcmp(argv[1], "-m") == 0) {
        if (strcmp(argv[2], "backup") == 0) {
            mode = 1;
        } else if (strcmp(argv[2], "restore") == 0) {
            mode = 2;
        }
    }

    switch (mode) {
        case 0:
            download_and_extract_file();
            manageFiles();
            break;
        case 1:
            backupFiles();
            break;
        case 2:
            restoreFiles();
            break;
    }

    sleep(1);

    exit(EXIT_SUCCESS);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 100

void monitor_user_processes(char *user);
void start_daemon_mode(char *user);
void stop_daemon_mode(char *user);
void block_user_processes(char *user);
void unblock_user_processes(char *user);
void log_process(char *user, int pid, char *process_name, int status);
void view_log(char *user);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <option> <user>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *option = argv[1];
    char *user = argv[2];

    if (strcmp(option, "-m") == 0) {
        start_daemon_mode(user);
    } else if (strcmp(option, "-s") == 0) {
        stop_daemon_mode(user);
    } else if (strcmp(option, "-c") == 0) {
        block_user_processes(user);
    } else if (strcmp(option, "-a") == 0) {
        unblock_user_processes(user);
    } else if (strcmp(option, "-l") == 0) {
        view_log(user);
    } else {
        printf("Invalid option!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void monitor_user_processes(char *user) {
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        int fd = open("/dev/null", O_WRONLY); 
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
        execlp("ps", "ps", "-u", user, NULL);
        perror("Error executing ps");
        exit(EXIT_FAILURE);
    } else {
        
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            log_process(user, getpid(), "monitor_user_processes", 1);
        } else {
            log_process(user, getpid(), "monitor_user_processes", 0);
        }
    }
}

void start_daemon_mode(char *user) {
    printf("Daemon mode started for user: %s\n", user);
}

void stop_daemon_mode(char *user) {
    printf("Daemon mode stopped for user: %s\n", user);
}

void block_user_processes(char *user) {
    printf("User processes blocked for user: %s\n", user);
}

void unblock_user_processes(char *user) {
    printf("User processes unblocked for user: %s\n", user);
}

void log_process(char *user, int pid, char *process_name, int status) {
    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);

    char datetime[20];
    strftime(datetime, sizeof(datetime), "%d:%m:%Y-%H:%M:%S", tm_info);

    char *process_status = (status == 0) ? "GAGAL" : "JALAN";

    char filename[50];
    sprintf(filename, "%s.log", user);

    FILE *fp;
    fp = fopen(filename, "a");
    if (fp == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "[%s]-%d-%s-%s\n", datetime, pid, process_name, process_status);

    fclose(fp);
}

void view_log(char *user) {
    char filename[50];
    sprintf(filename, "%s.log", user);

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    printf("Log process for user %s:\n", user);
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);
}

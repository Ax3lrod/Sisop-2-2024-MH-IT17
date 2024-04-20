#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>

#define PID_MAX 20
#define ARG_SIZE 50

pid_t running[PID_MAX];
int pidcount = 0;

void add_global(pid_t pid);
void kill_procs(int argc, char *argv[]);
void open(int argc, char *argv[]);
void open_file(int argc, char *argv[]);

void add_global(pid_t pid) {
    if (pidcount < PID_MAX) {
        running[pidcount] = pid;
        pidcount++;
    }
}

void kill_procs(int argc, char *argv[]) {
    FILE *config = NULL;
    if (argc == 3) {
        config = fopen(argv[2], "r");
        if (!config) {
            printf("Error: Failed to open file");
            exit(1);
        }
    }

    char cmd[ARG_SIZE];
    int num;
    if (config) {
        while (fscanf(config, "%s %d", cmd, &num) != EOF) {
            for (int i = 0; i < num; i++) {
                pid_t pid = fork();
                if (pid < 0) {
                    printf("Error: Fork failed\n");
                    exit(1);
                }
                if (pid == 0) {
                    char *args[] = {"pkill", cmd, NULL};
                    execvp("pkill", args);
                    _exit(1);
                }
                int status;
                waitpid(pid, &status, 0);
            }
        }
        fclose(config);
    } else {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Error: Fork failed\n");
            exit(1);
        }
        if (pid == 0) {
            char *args[] = {"pkill", "firefox", NULL};
            execvp("pkill", args);
            _exit(1);
        }
        waitpid(pid, NULL, 0);
        pid = fork();
        if (pid < 0) {
            printf("Error: Fork failed\n");
            exit(1);
        }
        if (pid == 0) {
            char *args[] = {"pkill", "wireshark", NULL};
            execvp("pkill", args);
            _exit(1);
        }
        waitpid(pid, NULL, 0);
    }
}

void open(int argc, char *argv[]) {
    for (int i = 2; i < argc; i += 2) {
        if (!isdigit(argv[i + 1][0])) {
            printf("Error: Invalid argument(s)");
            exit(1);
        }
    }
    for (int i = 2; i < argc; i += 2) {
        int num = atoi(argv[i + 1]);
        for (int j = 0; j < num; j++) {
            pid_t pid = fork();
            if (pid < 0) {
                printf("Error: Fork failed\n");
                exit(1);
            }
            if (pid == 0) {
                execlp(argv[i], argv[i], NULL);
                _exit(1);
            } else {
                add_global(pid);
            }
        }
    }
}

void open_file(int argc, char *argv[]) {
    FILE *config = fopen(argv[2], "r");
    if (!config) {
        printf("Error: Failed to open file");
        exit(1);
    }

    char cmd[ARG_SIZE];
    int num;
    while (fscanf(config, "%s %d", cmd, &num) != EOF) {
        for (int i = 0; i < num; i++) {
            pid_t pid = fork();
            if (pid < 0) {
                printf("Error: Fork failed\n");
                exit(1);
            }
            if (pid == 0) {
                execlp(cmd, cmd, NULL);
                _exit(1);
            } else {
                add_global(pid);
            }
        }
    }
    fclose(config);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [-o | -f file.conf | -k | -k file.conf]\n", argv[0]);
        return 1;
    }
    switch (argv[1][1]) {
        case 'o':
            open(argc, argv);
            break;
        case 'f':
            open_file(argc, argv);
            break;
        case 'k':
            kill_procs(argc, argv);
            break;
        default:
            printf("Invalid option\n");
            return 1;
    }
    return 0;
}

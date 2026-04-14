#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Helper to tokenize commands [cite: 10]
char **build_args(char *command) {
    char **args = malloc(50 * sizeof(char *));
    int i = 0;
    args[i] = strtok(command, " ");
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " ");
    }
    return args;
}

void run_pipe(char *input_line) {
    char left_cmd[100], right_cmd[100];
    int fd[2], i = 0, j = 0;

    // Split at '|' [cite: 10]
    while (input_line[i] != '|' && input_line[i] != '\0') {
        left_cmd[i] = input_line[i];
        i++;
    }
    left_cmd[i++] = '\0';

    while (input_line[i] != '\0') {
        right_cmd[j++] = input_line[i++];
    }
    right_cmd[j] = '\0';

    // Remove leading space for cleaner execvp
    char *trimmed_right = right_cmd;
    while(*trimmed_right == ' ') trimmed_right++;

    char **left_args = build_args(left_cmd);
    char **right_args = build_args(trimmed_right);

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return;
    }

    // Parent executes left command [cite: 11]
    if (fork() == 0) {
        dup2(fd[1], STDOUT_FILENO); // Redirect stdout [cite: 11]
        close(fd[0]);
        close(fd[1]);
        execvp(left_args[0], left_args);
        perror("Left exec failed");
        exit(1);
    }

    // Child executes right command [cite: 12]
    if (fork() == 0) {
        dup2(fd[0], STDIN_FILENO); // Redirect stdin [cite: 12]
        close(fd[1]);
        close(fd[0]);
        execvp(right_args[0], right_args);
        perror("Right exec failed");
        exit(1);
    }

    // MAIN process cleanup
    close(fd[0]);
    close(fd[1]);
    wait(NULL); // Wait for parent command
    wait(NULL); // Wait for child command
}

int main() {
    char input[256];
    printf("Enter command: ");
    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0;
        // Basic Trap: Prevent hanging on empty 'cat'
        if (strstr(input, "cat") && !strchr(input, '.') && strlen(input) < 10) {
            fprintf(stderr, "Error: 'cat' requires a filename or it will hang.\n");
        } else {
            run_pipe(input);
        }
    }
    return 0;
}


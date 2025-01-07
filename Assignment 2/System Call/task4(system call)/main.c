#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <numbers>\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child: Sorting the array...\n");
        char *args[argc + 1];
        args[0] = "./sort";
        for (int i = 1; i < argc; i++) {
            args[i] = argv[i];
        }
        args[argc] = NULL;
        execvp(args[0], args); 
        perror("execvp failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent: Checking odd/even status...\n");
        char *args[argc + 1];
        args[0] = "./oddeven";
        for (int i = 1; i < argc; i++) {
            args[i] = argv[i];
        }
        args[argc] = NULL; 
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    }

    return 0;
}

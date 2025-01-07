#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, grandchild_pid1, grandchild_pid2, grandchild_pid3;

    printf("Parent process ID: %d\n", getpid());

    child_pid = fork(); 

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        printf("Child process ID: %d\n", getpid());

        grandchild_pid1 = fork();
        if (grandchild_pid1 < 0) {
            perror("Fork failed");
            exit(1);
        }
        if (grandchild_pid1 == 0) {
            printf("Grandchild process ID: %d\n", getpid());
            exit(0);
        }

        wait(NULL); 

        grandchild_pid2 = fork();
        if (grandchild_pid2 < 0) {
            perror("Fork failed");
            exit(1);
        }
        if (grandchild_pid2 == 0) {
            printf("Grandchild process ID: %d\n", getpid());
            exit(0); 
        }

        wait(NULL);

        grandchild_pid3 = fork();
        if (grandchild_pid3 < 0) {
            perror("Fork failed");
            exit(1);
        }
        if (grandchild_pid3 == 0) {
            printf("Grandchild process ID: %d\n", getpid());
            exit(0); 
        }

        wait(NULL); 
        exit(0); 
    }

    wait(NULL);

    return 0;
}

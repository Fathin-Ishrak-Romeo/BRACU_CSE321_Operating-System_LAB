#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid1 == 0) {
        pid2 = fork(); 

        if (pid2 < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid2 == 0) {
            printf("I am grandchild\n");
            exit(0);
        } else {
            wait(NULL);
            printf("I am child\n");
            exit(0);
        }
    } else {
        wait(NULL);
        printf("I am parent\n");
    }

    return 0;
}

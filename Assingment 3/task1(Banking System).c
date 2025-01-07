#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

struct shared {
    char sel[100];
    int b;
};

int main() {
    // Create shared memory
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, sizeof(struct shared), 0666|IPC_CREAT);
    struct shared *shm = (struct shared*)shmat(shmid, NULL, 0);
    
    // Create pipe
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    // Initial balance
    shm->b = 1000;
    
    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");
    
    scanf("%s", shm->sel);
    printf("Your selection: %s\n", shm->sel);
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    
    if (pid == 0) { // Child process (opr)
        close(pipefd[0]); // Close read end
        
        if (strcmp(shm->sel, "a") == 0) {
            int amount;
            printf("Enter amount to be added:\n");
            scanf("%d", &amount);
            
            if (amount > 0) {
                shm->b += amount;
                printf("Balance added successfully\n");
                printf("Updated balance after addition:\n%d\n", shm->b);
            } else {
                printf("Adding failed, Invalid amount\n");
            }
        }
        else if (strcmp(shm->sel, "w") == 0) {
            int amount;
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &amount);
            
            if (amount > 0 && amount <= shm->b) {
                shm->b -= amount;
                printf("Balance withdrawn successfully\n");
                printf("Updated balance after withdrawal:\n%d\n", shm->b);
            } else {
                printf("Withdrawal failed, Invalid amount\n");
            }
        }
        else if (strcmp(shm->sel, "c") == 0) {
            printf("Your current balance is:\n%d\n", shm->b);
        }
        else {
            printf("Invalid selection\n");
        }
        
        // Write to pipe
        char *msg = "Thank you for using";
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);
        
        exit(0);
    }
    else { // Parent process (home)
        close(pipefd[1]); // Close write end
        
        // Wait for child to complete
        wait(NULL);
        
        // Read from pipe
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        close(pipefd[0]);
        
        // Cleanup shared memory
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }
    
    return 0;
}
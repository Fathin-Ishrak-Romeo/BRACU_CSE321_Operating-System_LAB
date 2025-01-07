#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct msg {
    long int type;
    char txt[6];
};

int main() {
    // Create message queue
    key_t key = ftok("msgq", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    
    char workspace[20];
    printf("Please enter the workspace name:\n");
    scanf("%s", workspace);
    
    if (strcmp(workspace, "cse321") != 0) {
        printf("Invalid workspace name\n");
        msgctl(msgid, IPC_RMID, NULL);
        return 0;
    }
    
    // Login process sends workspace name
    struct msg message;
    message.type = 1;
    strcpy(message.txt, workspace);
    msgsnd(msgid, &message, sizeof(message.txt), 0);
    printf("Workspace name sent to otp generator from log in: %s\n", message.txt);
    
    pid_t pid_otp = fork();
    
    if (pid_otp == 0) { // OTP Generator process
        // Read workspace name
        struct msg recv_msg;
        msgrcv(msgid, &recv_msg, sizeof(recv_msg.txt), 1, 0);
        printf("OTP generator received workspace name from log in: %s\n", recv_msg.txt);
        
        // Generate and send OTP to login
        struct msg otp_msg;
        otp_msg.type = 2;
        sprintf(otp_msg.txt, "%d", getpid());
        msgsnd(msgid, &otp_msg, sizeof(otp_msg.txt), 0);
        printf("OTP sent to log in from OTP generator: %s\n", otp_msg.txt);
        
        // Send OTP to mail process
        otp_msg.type = 3;
        msgsnd(msgid, &otp_msg, sizeof(otp_msg.txt), 0);
        printf("OTP sent to mail from OTP generator: %s\n", otp_msg.txt);
        
        pid_t pid_mail = fork();
        
        if (pid_mail == 0) { // Mail process
            // Read OTP from OTP generator
            struct msg mail_msg;
            msgrcv(msgid, &mail_msg, sizeof(mail_msg.txt), 3, 0);
            printf("Mail received OTP from OTP generator: %s\n", mail_msg.txt);
            
            // Send OTP to login
            mail_msg.type = 4;
            msgsnd(msgid, &mail_msg, sizeof(mail_msg.txt), 0);
            printf("OTP sent to log in from mail: %s\n", mail_msg.txt);
            exit(0);
        }
        
        wait(NULL);
        exit(0);
    }
    
    // Login process continues
    wait(NULL);
    
    // Receive OTP from OTP generator
    struct msg otp_from_generator;
    msgrcv(msgid, &otp_from_generator, sizeof(otp_from_generator.txt), 2, 0);
    printf("Log in received OTP from OTP generator: %s\n", otp_from_generator.txt);
    
    // Receive OTP from mail
    struct msg otp_from_mail;
    msgrcv(msgid, &otp_from_mail, sizeof(otp_from_mail.txt), 4, 0);
    printf("Log in received OTP from mail: %s\n", otp_from_mail.txt);
    
    // Compare OTPs
    if (strcmp(otp_from_generator.txt, otp_from_mail.txt) == 0) {
        printf("OTP Verified\n");
    } else {
        printf("OTP Incorrect\n");
    }
    
    // Cleanup message queue
    msgctl(msgid, IPC_RMID, NULL);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int process_count = 1;  

void increment_process_count() {
    process_count++;  
}

int main() {
    pid_t a, b, c;
    
    a = fork();
    if (a == 0) { 
        increment_process_count();
        
        if (getpid() % 2 != 0) {
            pid_t extra_child = fork(); 
            if (extra_child == 0) {  
                increment_process_count();
                exit(0);  
            }
        }
        exit(0);  
    }

    b = fork();
    if (b == 0) {  
        increment_process_count();
        
        if (getpid() % 2 != 0) {
            pid_t extra_child = fork();  
            if (extra_child == 0) {  
                increment_process_count();
                exit(0); 
            }
        }
        exit(0);  
    }

 
    c = fork();
    if (c == 0) {  
        increment_process_count();
        
        if (getpid() % 2 != 0) {
            pid_t extra_child = fork();  
            if (extra_child == 0) {  
                increment_process_count();
                exit(0);  
            }
        }
        exit(0);  
    }

    while (wait(NULL) > 0);  
    
    printf("Total processes created: %d\n", process_count);

    return 0;
}

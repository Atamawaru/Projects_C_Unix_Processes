#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[]) {

    pid_t pid1 = fork();
    pid_t pid2 = fork();
    if (pid1 == 0) {
        if (pid2 == 0) {
            printf("Hello, im child process y\n");
        } 
        else{
            printf("Hello, im child process x\n");
        }
    }
    else {
        if (pid2 == 0) {
            printf("Hello, im child process z\n");
        }
        else {
            printf("Hello, im parent process\n");
        }
    }
    while (wait(NULL) != -1 || errno != ECHILD ) {
        printf("Waited for child to finish\n");
    }
    //printf("PID: %d, PPID: %d\n", getpid(), getppid());
    return 0;
    
}

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[]) {

    pid_t pid = fork();
    if (pid == 0) {
        sleep(1);
    }
    printf("PID: %d, PPID: %d\n", getpid(), getppid());
    int res = wait(NULL);
    if (res == -1) {
        printf("No children left to wait for\n");
    }
    else {
        printf("%d finished execution\n", res);
    }
    return 0;
    
}

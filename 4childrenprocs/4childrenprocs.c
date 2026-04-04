#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[]) {
    //create 4 children processes that have the same parent
    int proc_count = 4; 
    pid_t pids[proc_count]; // array to store process ids
    pids[0] = fork(); //create first fork
    if (pids[0]==0) {
        printf("Process 1 with ID %d, parent ID %d\n", getpid(), getppid());
    }
    if (pids[0]>0) {
        for (int i=1; i<proc_count; i++) {
            pids[i]=fork();
            if (pids[i]==0) {
                printf("Process %d with ID %d, parent ID %d\n", i+1, getpid(), getppid());
                break;
            }
        }
    }
    while (wait(NULL) != -1 || errno != ECHILD) {
       printf("Waited for child to exit\n"); 
    }
    return 0;
    
}

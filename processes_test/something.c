#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[]) {

    pid_t pid = fork();
    int n;
    if (pid == 0) {
        n = 1;
    }
    else {
        n = 6;
    }
    if (pid != 0) {
       wait(NULL); 
    }
    
    for (int i=n; i<n+5; i++) {
        printf("%d ", i);
        fflush(stdout);
    }
    return 0;
    
}

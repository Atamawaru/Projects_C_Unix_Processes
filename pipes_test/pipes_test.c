#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[]) {
    int fd[2];
    if (pipe(fd)== -1){
        printf("Error creating pipe\n;");
        return 1;
    }
    int n = 200;
    int pid = fork();
    if (pid == 0) {
        close(fd[0]);

        char* string = malloc(sizeof(char *) * n);
        
        printf("Input a string: ");
        fgets(string, n, stdin);
        if (write(fd[1], string, strlen(string))==-1){
            printf("Error with writing to pipe\n");
        }

        close(fd[1]);
    }
    else 
    {
        close(fd[1]);
        
        char* y = malloc(sizeof(char *) * n);
        read(fd[0], y, sizeof(char *) * n);
        printf("Got from child process %s\n", y);
        close(fd[0]);
    }
    return 0;
    
}

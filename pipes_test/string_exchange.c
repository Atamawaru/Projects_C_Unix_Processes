#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[]) {
    int fd1[2]; //pipe from child to parent
    int fd2[2]; //pipe from parent to child
    if (pipe(fd1)== -1){
        printf("Error creating pipe\n;");
        return 1;
    }
    if (pipe(fd2)== -1){
        printf("Error creating pipe\n;");
        return 1;
    }
    int n = 200;
    int pid = fork();
    if (pid == 0) {
        
        close(fd1[0]);
        close(fd2[1]);

        char* string = malloc(sizeof(char *) * n);
        
        printf("Input a string: ");
        fgets(string, n, stdin);
        if (write(fd1[1], string, strlen(string))==-1){
            printf("Error with writing to pipe\n");
        }
        if ((read(fd2[0], string, sizeof(char *) * n))==-1){
            printf("Error with reading from pipe\n");
        }
        printf("Got from parent process uppercase string: %s\n", string);
        close(fd1[1]);
        close(fd2[0]);
    }
    else 
    {
        close(fd1[1]);
        close(fd2[0]);
        char* y = malloc(sizeof(char *) * n);
        read(fd1[0],y, sizeof(char *) * n);
        printf("Got from child process string: %s\n", y);
        for (int i=0; i<strlen(y); i++) {
            y[i]=toupper(y[i]);
        }
        write(fd2[1], y, strlen(y)+1);


        close(fd1[0]);
        close(fd2[1]);
    }
    return 0;
    
}

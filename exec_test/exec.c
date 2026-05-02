#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error forking: ");
        return 1;
    }
    
    if (pid == 0) {
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
    }
    else {
        wait(NULL);
        printf("Success!\n");
    }
    return 0;
}

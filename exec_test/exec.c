#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error forking: ");
        return 1;
    }
    
    if (pid == 0) {
        int fd = open("pingResults.txt", O_WRONLY | O_APPEND |O_CREAT, 0777);
        if (fd == -1) {
            perror("Failed to open file: ");
            return 2;
        }
        int fd2 = dup2(fd, STDOUT_FILENO);
        int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        if (err == -1) {
            printf("Error. Could not find command to execute.\n");
            return 3;
        }
        close(fd2);
        close(fd);
    }
    else {
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0) {
            printf("Success! return code: %d\n", WEXITSTATUS(wstatus));
        }
        else {
            printf("Error. Failed to ping. return code: %d\n", WEXITSTATUS(wstatus));
            return 4;
        }
    }
    return 0;
}

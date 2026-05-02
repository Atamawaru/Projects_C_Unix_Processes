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
        //int err = execlp("ls", "ls", "-la", "Projects_C_Unix_Processes", NULL);
        int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        if (err == -1) {
            printf("Error. Could not find command to execute.\n");
            return 0;
        }
    }
    else {
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0) {
            printf("Success! return code: %d\n", WEXITSTATUS(wstatus));
        }
        else {
            printf("Error. Failed to ping. return code: %d\n", WEXITSTATUS(wstatus));
        }
    }
    return 0;
}

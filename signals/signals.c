#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
void signalHandler(int sig){
    char *msg = "Program stopped with interrupt\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    _exit(sig);
}

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid==-1) {
        perror("Error forking: ");
        return 1;
    }

    if (pid==0) {
        while (1) {
            printf("Text goes here\n");
            usleep(50000);
        }
    }
    else {
        sleep(5);
        kill(pid, SIGKILL);
        wait(NULL);
    }
    return 0;
}

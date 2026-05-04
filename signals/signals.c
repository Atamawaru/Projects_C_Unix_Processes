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
            printf("Some text\n");
            usleep(50000);
        }
    }
    else {
        int t=-1;
        kill(pid, SIGSTOP);
        do {
            printf("Time for execution: ");
            scanf("%d", &t);
        } while (t < 0);
        kill(pid, SIGCONT);
        sleep(t);
        kill(pid, SIGKILL);
        wait(NULL);
    }
    return 0;
}

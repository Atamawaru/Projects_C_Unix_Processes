#include <signal.h>
#include <stdio.h>
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
    signal(SIGINT, signalHandler);
    while (1) {
        printf("Hello world!\n");
        sleep(1);
    }
    return 0;
}

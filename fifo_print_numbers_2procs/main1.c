#include <asm-generic/errno-base.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[]) {
    
    if (mkfifo("sum", 0777) == -1 && errno != EEXIST) {
        perror("Error creating fifo: ");
    }

    return 0;
}

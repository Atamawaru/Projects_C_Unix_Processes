#include <asm-generic/errno-base.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    if (mkfifo("myfifo1", 0777) == -1) {
        if (errno != EEXIST) {
            perror("Error creating pipe ");
            return 1;
        }
    }
    int fdin = open("myfifo1", O_WRONLY);
    int x = 97;
    if (write(fdin, &x, sizeof(x))==-1){
        perror("Error writing to file: ");
        return 2;
    }
    close(fdin);
    return 0;
}

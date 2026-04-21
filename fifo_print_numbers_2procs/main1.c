#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
int main(int argc, char* argv[]) {
    char* fifo_name = "sum";
    if (mkfifo(fifo_name, 0777) == -1 && errno != EEXIST) {
        perror("Error creating fifo: ");
        return 1;
    }
    int n = 5;
    int nums[n];
    srand(time(NULL));
    for (int i=0; i<n; i++) {
        nums[i]=rand() % 100 + 1;
        printf("Generated num: %d\n", nums[i]);
    }
    int fdin = open(fifo_name, O_WRONLY);
    if (fdin == -1) {
        perror("Error opening fifo: ");
        return 2;
    }
    close(fdin);
    return 0;
}

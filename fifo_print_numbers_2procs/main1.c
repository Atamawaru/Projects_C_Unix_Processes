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
    }
    int fdin = open(fifo_name, O_WRONLY);
    if (fdin == -1) {
        perror("Error opening fifo: ");
        return 2;
    }
    for (int i=0; i<n; i++) {
        if (write(fdin, &nums[i], sizeof(nums[i]))==-1){
            perror("Error writing to fifo: ");
            return 3;
        }
        printf("Wrote: %d\n", nums[i]);
    }
    close(fdin);
    int sum=0;
    int fdsum = open(fifo_name, O_RDONLY);
    if (fdsum == -1) {
        perror("Error opening writing pipe: ");
        return 4;
    }
    if (read(fdsum, &sum, sizeof(sum)) == -1) {
        perror("Error reading fifo pipe (sum): ");
        return 5;
    }
    printf("Got from other process sum: %d\n", sum);
    close(fdsum);
    return 0;
}

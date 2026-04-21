#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[]) {
    char* fifo_name = "sum";
    int n = 5;
    int arr[n];
    int fd = open(fifo_name, O_RDONLY);
    if (fd == -1) {
        perror("Error opening fifo pipe for reading: ");
        return 1;
    }
    sleep(1);
    for (int i=0; i<n; i++) {
        if (read(fd, &arr[i], sizeof(int)) == -1) {
            perror("Error reading from fifo pipe: ");
            return 2;
        }
        printf("Received: %d\n", arr[i]);
    }
    int sum = 0;
    for (int i=0; i<n; i++) {
        sum+=arr[i];
    }
    close(fd);

    int fdw = open(fifo_name, O_WRONLY);
    if (fdw == -1) {
        perror("Error opening for writing to fifo (sum): ");
        return 3;
    }
    if (write(fdw, &sum, sizeof(sum)) == -1) {
        perror("Error writing to fifo (sum): ");
    }
    close(fdw);
    return 0;
}

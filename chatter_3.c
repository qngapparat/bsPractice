#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "error_handler.h"

int main(int argc, char const *argv[]) {

    srand(time(NULL));
    char path[] = "/home/qngapparat/fifo3";
    char message[] = "im chatter 3 waddup\n";

    watch(mkfifo(path, 0666), "mkfifo");

    int fd;
    watch(fd = open(path, O_WRONLY), "open");

    while(1){

        int intv = rand()%5 + 2;
        sleep(intv);
        watch(write(fd, message, sizeof(message)), "write");
    }

    close(fd);
    unlink(path);

    return EXIT_SUCCESS;
}

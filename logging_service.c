#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "error_handler.h"
#include <sys/select.h>

int max(int a, int b){
    return a > b ? a : b;
}

int main(int argc, char const *argv[]) {

    int fd1, fd2, fd3;
    fd_set my_fd_set;
    char path1[] = "/home/qngapparat/fifo1";
    char path2[] = "/home/qngapparat/fifo2";
    char path3[] = "/home/qngapparat/fifo3";
    char buf[256];

    watch((fd1 = open(path1, O_RDONLY, O_NONBLOCK)), "open");
    watch((fd2 = open(path2, O_RDONLY, O_NONBLOCK)), "open");
    watch((fd3 = open(path3, O_RDONLY, O_NONBLOCK)), "open");

    //needed for select(). Must be the biggest fd + 1
    int max_fd = max(max(fd1, fd2), fd3) + 1;

    while(1){

        FD_ZERO(&my_fd_set);
        FD_SET(fd1, &my_fd_set);
        FD_SET(fd2, &my_fd_set);
        FD_SET(fd3, &my_fd_set);

        select(max_fd, &my_fd_set, NULL, NULL, NULL);

        if(FD_ISSET(fd1, &my_fd_set)){
            if(read(fd1, buf, sizeof(buf)) >= 0){
                printf("[chat1]: %s", buf);
            }
        }

        if(FD_ISSET(fd2, &my_fd_set)){
            if(read(fd2, buf, sizeof(buf)) >= 0){
                printf("[chat2]: %s", buf);
            }
        }

        if(FD_ISSET(fd3, &my_fd_set)){
            if(read(fd3, buf, sizeof(buf)) >= 0){
                printf("[chat3]: %s", buf);
            }
        }

    }

    return EXIT_SUCCESS;
}

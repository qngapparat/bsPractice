#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>

//piping stdout of a child into a pipe, from which the parent reads.


int main(int argc, char const *argv[]) {

    pid_t pid;
    int fd[2];


    watch(pipe(fd), "pipe");

    watch((pid = fork()), "fork");

    if(!pid){ //child (writes)
        close(fd[0]);
        //clear the system write slot and write our file descriptor there

        //NOTE use the following to redirect stdout into the pipe
        /*
        close(1);
        dup(fd[1]);
        close(fd[1]);
        //printf("printf message thru pipe lmaoo\n");
        */

        //dprintf to send a string into a pipe
        dprintf(fd[1], "%d %d and %d and sum message thru pipe\n", 3, 4, 5);
        exit(EXIT_SUCCESS);
    }

    //parent

    close(fd[1]);
    close(0);
    dup(fd[0]);
    close(fd[0]);

    char readbuf[64];

    sleep(1);
    scanf("%[^\n]", readbuf);
    printf("message received: %s\n", readbuf);

    printf("main prog terminating\n");

    return EXIT_SUCCESS;
}

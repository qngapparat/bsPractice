#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>


//creationg two pipes between processes, so they can both read and write.


int main(int argc, char const *argv[]) {

    pid_t pid1, pid2;
    int onetotwo[2], twotoone[2];

    watch(pipe(onetotwo), "pipe");
    watch(pipe(twotoone), "pipe");

    watch((pid1 = fork()), "fork");
    if(!pid1){ //child one

        int readbuf = 0;
        int writebuf = 0;

        close(onetotwo[0]);
        close(twotoone[1]);

        while(1){

            watch(write(onetotwo[1], &writebuf, sizeof(int)), "write");
            watch(read(twotoone[0], &readbuf, sizeof(int)), "read");
            printf("1 received: %d\n", readbuf);
            writebuf = readbuf += 1;

            if(writebuf > 20){
                printf("one terminating\n");
                return EXIT_SUCCESS;
            }

            sleep(1);

        }


    }

    watch((pid2 = fork()), "fork");
    if(!pid2){ //child two

        int readbuf = 0;
        int writebuf = 0;

        close(onetotwo[1]);
        close(twotoone[0]);

        while(1){

            watch(read(onetotwo[0], &readbuf, sizeof(int)), "read");
            printf("2 received: %d\n", readbuf);
            writebuf = readbuf += 1;
            watch(write(twotoone[1], &writebuf, sizeof(int)), "write");

            if(writebuf > 20){
            printf("two terminating\n");
                return EXIT_SUCCESS;
            }

            sleep(1);
        }

    }

    //wait for both child processes
    int status1, status2;
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    //close parent ends of pipes, since only the children should communicate

    close(onetotwo[0]);
    close(onetotwo[1]);
    close(twotoone[0]);
    close(twotoone[1]);

    return EXIT_SUCCESS;
}

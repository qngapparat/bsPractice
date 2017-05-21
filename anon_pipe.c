#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "error_handler.h"

//practising unnamed pipes and execvp. Creating two children, who execute "ls -l", and  "grep <keyword>" , respectively. Stdout from "ls -l" is piped to "grep <keyword>" using a unnamed pipe.

int main(int argc, char const *argv[]) {

    pid_t pid;
    int fd[2];

    watch(pipe(fd), "pipe");

    watch((pid = fork()), "fork");

    if(!pid){ //child


    }



    return EXIT_SUCCESS;
}

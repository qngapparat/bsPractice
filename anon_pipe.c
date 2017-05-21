#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//practising unnamed pipes and execvp. Creating two children, who execute "ls -l", and  "grep <keyword>" , respectively. Stdout from "ls -l" is piped to "grep <keyword>" using a unnamed pipe.

int main(int argc, char const *argv[]) {

    pid_t pid1, pid2;
    int fd[2];
    char keyword[20];
    printf("choose keyword for grep:\n");
    scanf("%s", keyword);

    char* lsv[] = {"ls", "-l", NULL};
    char* grepv[] = {"grep", keyword, NULL};

    watch(pipe(fd), "pipe");

    watch((pid1 = fork()), "fork");
    if(!pid1){ //ls child
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        execvp(lsv[0], lsv);
        perror("execvp");
        exit(EXIT_FAILURE);

    }

    watch((pid2 = fork()), "fork");
    if(!pid2){ //grep child
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);

        execvp(grepv[0], grepv);
        perror("execvp");
        exit(EXIT_FAILURE);

    }


    for(int i = 0; i < 2; i++){
        wait(NULL);
    }

    printf("all children terminated. bye\n");

    return EXIT_SUCCESS;
}

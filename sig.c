#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "error_handler.h"
#include <time.h>
#include <stdbool.h>

//sending and handling signals between/in processes using kill() and sigaction().
//To cancel the program without creating a zombie child, SIGINT (from Strg-C) is caught and handled, so that the child exits safely.

bool usr1_set = false;
bool usr2_set = false;
bool strg_c_set = false;

void strg_c_handler_funct(int signum){
    strg_c_set = true;
}

void usr1_handler_funct (int signum){
    usr1_set = true;
}

void usr2_handler_funct (int signum){
    usr2_set = true;
}

int main(int argc, char const *argv[]) {

    srand(time(NULL));

    struct sigaction usr1_handler, usr2_handler, strg_c_handler;

    usr1_handler.sa_handler = usr1_handler_funct;
    usr1_handler.sa_flags = 0;
    usr2_handler.sa_handler = usr2_handler_funct;
    usr2_handler.sa_flags = 0;
    strg_c_handler.sa_handler = strg_c_handler_funct;
    strg_c_handler.sa_flags = 0;

    sigaction(SIGUSR1, &usr1_handler, NULL);
    sigaction(SIGUSR2, &usr2_handler, NULL);
    sigaction(SIGINT, &strg_c_handler, NULL);

    pid_t pid;

    watch((pid = fork()), "fork");
    if(!pid){ //child

        while(1){
            sleep(rand()%5);
            kill(getppid(), SIGUSR1);
            sleep(rand()%5);
            kill(getppid(), SIGUSR2);
        }

    }

    //parent

    while(1){

        sleep(0.1);

        if(usr1_set){
            printf("usr1 received.\n");
            usr1_set = false;
        }

        if(usr2_set){
            printf("usr2 received.\n");
            usr2_set = false;
        }

        if(strg_c_set){
            kill(pid, SIGINT);
            printf("child exited safely");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

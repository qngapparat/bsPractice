#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "error_handler.h"

//open existing shm, reading char-by-char from shm, setting "flag" to signal sender to terminate


int main(int argc, char const *argv[]) {

    key_t key;
    int shmid;
    char *s, *shm;

    const int MAX_SIZE = 27;
    int mask = 0666;
    key = ftok(".", 'a');

    if((shmid = shmget(key, MAX_SIZE, mask)) == -1){
        die("shmget");
    }

    if((shm = shmat(shmid, NULL, 0)) == (char*) -1){
        die("shmat");
    }

    s = shm;
    for(int i = 0; i < MAX_SIZE; i++){
        putchar(*s);
        s++;
    }

    putchar('\n');

    //set complete "flag"
    *shm = '*';

    if(shmdt(shm) == -1){
        die("shmdt");
    }

    printf("detached. terminating\n");

    return EXIT_SUCCESS;
}

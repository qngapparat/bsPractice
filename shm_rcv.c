#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(int argc, char const *argv[]) {

    key_t key;
    int shmid;
    char *s, *shm;

    const int MAX_SIZE = 128;
    int mask = IPC_CREAT | 0666;
    key = ftok(".", 'a');

    if((shmid = shmget(key, MAX_SIZE, mask)) == -1){
        perror("shmget")
        return EXIT_FAILURE;
    }

    if((shm = shmat(shmid, NULL, 0)) == (char*) -1){
        perror("shmat");
        return EXIT_SUCCESS;
    }


    for(s = shm; *s != NULL; s++){
        putchar(*s);
    }

    putchar('\n');

    //set complete "flag"
    *shm = '*';

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(int argc, char const *argv[]) {

    key_t key;
    int shmid;
    char c, *shm, *s;

    int mask = 0666;
    const int MAX_SIZE = 128;
    key = ftok(".", 'a');

    if((shmid = shmget(key, MAX_SIZE, mask)) == -1){
        perror("shmget");
        return EXIT_FAILURE;
    }

    if((shm = shmat(shmid, NULL, 0)) == (char*)-1 ){
        perror("shmat");
        return EXIT_FAILURE;
    }

    //write to memory
    //dont change orginal pointer to not loose value
    s = shm;
    for(c = 'a', c < 'z', c++){
        s* = c;
        s++;
    }

    //sleep until first char is set to *. //TODO exit immediately without shmdt. does sender still work?
    
    while((*shm) != '*'){
        sleep(1);
    }

    //detach segment
    if((shmdt(shm)) == -1){
        perror("shmdt");
        return EXIT_FAILURE;
    }

    printf("detached. terminating\n");

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "error_handler.h"

//create shm, write string to it, wait for "flag" to be set in shm before termination

int main(int argc, char const *argv[]) {

    key_t key;
    int shmid;
    char c, *shm, *s;

    int mask = IPC_CREAT | 0666;
    const int MAX_SIZE = 27;
    key = ftok(".", 'a');

    if((shmid = shmget(key, MAX_SIZE, mask)) == -1){
        die("shmget");

    }

    //shm is the pointer to first char element or MAX_SIZE char elements in memory
    //every shmat process/thread has access to these chars.
    if((shm = shmat(shmid, NULL, 0)) == (char*)-1 ){
        die("shmat");
    }

    //write to memory
    //dont change orginal pointer to not loose value
    s = shm;
    for(c = 'a'; c < 'z'; c++){
        *s = c;
        s++;
    }

    //sleep until first char is set to *. //TODO exit immediately without shmdt. does sender still work?
    while((*shm) != '*'){
        sleep(1);
    }

    //detach segment
    if((shmdt(shm)) == -1){
        die("shmdt");
    }

    char decision;
    printf("do you want to delete the memory? y/n");
    scanf("%c", &decision);

    //sets the IPC_RMID flag for the segment, which deletes it after the last proccess detaches
    if(decision == 'y'){
        shmctl(shmid, IPC_RMID, 0);
    }

    printf("detached. terminating\n");

    return EXIT_SUCCESS;
}

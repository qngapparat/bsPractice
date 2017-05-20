#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include "error_handler.h"


int main(int argc, char const *argv[]) {

    int mask = 0666;
    key_t key = ftok(".", 'x');
    int semid;

    //get semid
    watch((semid = semget(key, 1, mask)), "semget");

    //create lock and unlock structs
    struct sembuf lock;
    lock.sem_num = 0; //semaphore #
    lock.sem_op = -1; //decrement semaphore to lock
    lock.sem_flg = 0; //waits in case semaphore is 0

    struct sembuf unlock; //TODO to array
    unlock.sem_num = 0;
    unlock.sem_op = +1;
    unlock.sem_flg = 0; //TODO might change this


    printf("waiting for critical region\n");

    watch((semop(semid, &lock, 1)), "semop");
    printf("im in the critical region man\n");
    watch((semop(semid, &unlock, 1)), "semop");

    printf("done. terminating\n");
    return EXIT_SUCCESS;
}

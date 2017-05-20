#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include "error_handler.h"

int main(int argc, char const *argv[]) {

    int mask = IPC_CREAT | 0666;
    key_t key = ftok(".", 'x');
    int semid;

    //create
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


    //this way, semop can replace the initial semctl (at least with one semaphore).
    lock.sem_op = 1;
    watch((semop(semid, &lock, 1)), "initial semop (semctl replacement)");

    //reset our operation
    lock.sem_op = +1;

    watch((semop(semid, &lock, 1)), "semop");
    printf("im in critical region... sleeping here for 10 sec\n");

    int i = 0;
    while(i++ < 10){
        sleep(1);
    }

    watch((semop(semid, &unlock, 1)), "semop");

    printf("unlinking + terminating\n");
    watch((semctl(semid, 0, IPC_RMID)), "semctl");


    return EXIT_SUCCESS;
}

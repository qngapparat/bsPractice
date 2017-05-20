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
    if((semid = semget(key, 1, mask)) == -1){
        die("semget");
    }

    //create lock and unlock structs
    struct sembuf lock;
    lock.sem_num = 0; //semaphore #
    lock.sem_op = -1; //decrement semaphore to lock
    lock.sem_flg = 0; //waits in case semaphore is 0

    struct sembuf unlock; //TODO to array
    unlock.sem_num = 0;
    unlock.sem_op = +1;
    unlock.sem_flg = IPC_NOWAIT; //TODO might change this


    //this way, semop can replace the initial semctl (at least with one semaphore).
    lock.sem_op = 1;
    if((semop(semid, &lock, 1)) == -1){
        die("semop lock (initial)");
    }

    //reset our operation
    lock.sem_op = +1;

    if((semop(semid, &lock, 1)) == -1){
        die("semop lock");
    }

    printf("im in critical region\n");

    if((semop(semid, &unlock, 1)) == -1){
        die("semop unlock");
    }

    printf("unlinking + terminating\n");

    if((semctl(semid, 0, IPC_RMID)) == -1){
        die("semctl ipc_rmid");
    }


    return EXIT_SUCCESS;
}

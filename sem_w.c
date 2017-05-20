#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include "error_handler.h"

union semun {
    int val;/* value of SETVAL */
    struct semid_ds *buf;/* buffer for IPC_STAT,IPC_SET */
    ushort *array;/* array for GETALL, SETALL */
};

int main(int argc, char const *argv[]) {

    int mask = IPC_CREAT | 0666;
    key_t key = ftok(".", 'x');
    int semid;

    //create
    watch((semid = semget(key, 1, mask)), "semget");

    //create lock and unlock structs
    struct sembuf lock[1];
    lock[0].sem_num = 0; //semaphore #
    lock[0].sem_op = -1; //decrement semaphore to lock
    lock[0].sem_flg = SEM_UNDO; //waits in case semaphore is 0

    struct sembuf unlock[1];
    unlock[0].sem_num = 0;
    unlock[0].sem_op = +1;
    unlock[0].sem_flg = SEM_UNDO; //TODO might change this

    //use the following for multiple semapores, in combination with SETALL instead of SETVAL
/*
    union semun arg;
    unsigned short values[1];
    values[0] = 1;
    arg.array = values;
*/
    union semun arg;
    arg.val = 1;

    //init semaphore (set to 1)
    watch((semctl(semid, 0, SETVAL, arg)), "semctl");

    //critical
    watch((semop(semid, lock, 1)), "semop");
    printf("im in critical region... \n");
    //critical operations here
    watch((semop(semid, unlock, 1)), "semop");
    //end critical

    printf("waiting 5 sec for reader to finish before terminating\n");
    sleep(5);

    //delete semaphore
    printf("unlinking + terminating\n");
    watch((semctl(semid, 0, IPC_RMID)), "semctl");


    return EXIT_SUCCESS;
}

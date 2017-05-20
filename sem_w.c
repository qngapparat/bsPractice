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

    struct sembuf unlock[1]; //TODO to array
    unlock[0].sem_num = 0;
    unlock[0].sem_op = +1;
    unlock[0].sem_flg = SEM_UNDO; //TODO might change this


    //this way, semop can replace the initial semctl (at least with one semaphore).
    /*lock.sem_op = 1;
    watch((semop(semid, lock, 1)), "initial semop (semctl replacement)");

    //reset our operation
    lock.sem_op = +1;*/

    union semun arg;
    unsigned short values[1];
    values[0] = 1;
    arg.array = values;

    watch((semctl(semid, 0, SETALL, arg)), "init setctl");


    watch((semop(semid, lock, 1)), "semop");
    printf("im in critical region... sleeping here for 10 sec\n");
    int i = 0;
    while(i++ < 10){
        sleep(1);
    }
    watch((semop(semid, unlock, 1)), "semop");

    printf("waiting 5 sec for reader to finish before terminating\n");
    //Waiting 5 seconds. using i=10 from above.
    while(i-- > 5){
        sleep(1);
    }

    printf("unlinking + terminating\n");
    watch((semctl(semid, 0, IPC_RMID)), "semctl");


    return EXIT_SUCCESS;
}

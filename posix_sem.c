#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#include <sys/mman.h>	/* for PROT_WRITE/PROT_READ, MAP_SHARED, munmap/mmap, shm_open/shm_unlink */
#include <sys/stat.h>	/* For mode constants */
#include <sys/wait.h>


#include <unistd.h>	/* read, close, ftruncate */
#include <fcntl.h>

int main(int argc, char const *argv[]) {

    sem_t* my_sem;
    char name[] = "posix_sem";
    char flag = O_CREAT;

    //sem_open(name, flag, permissions, initial semaphore value)
    //NOTE if flag is set to one, in case no sem exists yet, one is created with "name", "permissions" and "initial semaphore value". Otherwise, this is ignored.
    if((my_sem = sem_open(name, flag, 0666, 1)) == SEM_FAILED){
        perror("sem_open");
        return EXIT_FAILURE;
    }

    watch(sem_wait(my_sem), "sem_wait");

    //critical region here

    watch(sem_post(my_sem), "sem_post");

    //...

    //close semaphore
    watch(sem_close(my_sem), "sem_close");



    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

int main(int argc, char const *argv[]) {

    sem_t my_sem = NULL;
    char name[] = "posix_sem";
    char flag = O_CREAT;

    //sem_open(name, flag, permissions, initial semaphore value)
    //NOTE if flag is set to one, in case no sem exists yet, one is created with "name", "permissions" and "initial semaphore value". Otherwise, this is ignored.
    watch(my_sem = sem_open(name, flag, 0666, 1));

    watch(sem_wait(my_sem));

    //critical region here

    watch(sem_post(my_sem));

    //...

    //close semaphore
    watch(sem_close(my_sem));



    return EXIT_SUCCESS;
}

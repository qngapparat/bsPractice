#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "error_handler.h"


int main(int argc, char const *argv[]) {

    int fd;
    const char name[] = "/shm_object";
    int mask = O_CREAT | O_RDWR;
    int* my_shm;


    watch((fd = shm_open(name, mask, 0666)), "shm_open");

    watch((ftruncate(fd, sizeof(int))), "ftruncate");

    //mmap(specific adress, size of segment, permissions, mapping notificaitons, fd, offset)
    my_shm = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(my_shm == ((void *) -1)){
        perror("mmap");
        return EXIT_FAILURE;
    }

    *my_shm = 0;

    //... code

    pid_t pid;
    watch((pid = fork()), "fork");
    if(!pid){ //child
        *my_shm =  14;
        printf("child: changed integer to 14. terminating\n");
        exit(EXIT_SUCCESS);
    }

    //wait for child to terminate
    wait(NULL);
    printf("parent: integer: %d", *my_shm);


    //unmap shm (check if it was unmapped before)
    if(my_shm > 0){
        munmap(my_shm, sizeof(int));
    }
    close(fd);
    //delete shm after last one closes it
    shm_unlink(name);



    return EXIT_SUCCESS;
}

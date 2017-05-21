#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>



int main(int argc, char const *argv[]) {

    int fd;
    const char name[] = "shm_obj";
    int mask = O_CREAT | O_RDWR;

    watch((fd = shm_open(name, mask, 0666)), "shm_open");

    return EXIT_SUCCCESS;
}

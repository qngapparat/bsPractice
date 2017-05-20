#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(int argc, char const *argv[]) {

    key_t key;
    int shmid;

    const int MAX_SIZE = 128;
    int mask = IPC_CREAT | 0666;
    key = ftok(".", 'a');






    return EXIT_SUCCESS;
}

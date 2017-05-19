#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>


int main(int argc, char const *argv[]) {

    int msg,mask,msgid;

    mask = 0666;
    key = ftok(".", "A");
    msgid = msgget(key, mask); //returns error if doesnt exist

    if(msgid == -1){ //in case msg doesn't exist, create one
        printf("msgqueue doesn't exist. Creating one...\n");

        //initialize
        if((msgid = msgget(key, mask | IPC_CREAT)) == -1){
            perror("msgget");
            return EXIT_FAILURE;
        }

        int msg[2];
        msg[1] = 1234;
        msg[2] = 6789;

        //send
        if((int ret = msgsnd(msgid, msg, sizeof(int), IPC_NOWAIT)) == -1{
            perror("msgsnd");
            return EXIT_FAILURE;
        }

    }

    else{
        printf("msgqueue exists already. cancelling\n");
        return EXIT_FAILURE;
    }

    printf("completed. terminating\n");
    return EXIT_SUCCESS;
}

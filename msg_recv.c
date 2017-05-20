#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 128

struct msgbuf {
    long mtype;
    char mtext[MAX_BUF];
};

int main(int argc, char const *argv[]) {

    key_t key;
    int msgid;
    //structs containing the message and another identifier (long mtype), here set to 1

    struct msgbuf rcvbuf;

    key = 1234;

    if((msgid = msgget(key, 0666)) == -1){
        perror("msgget");
        return EXIT_SUCCESS;
    }

    while(1){
        //receive message  of identifier 1 (long mtype)
        if(msgrcv(msgid, &rcvbuf, MAX_BUF, 1, 0) == -1){
            perror("msgrcv");
            return EXIT_FAILURE;
        }

        //print message
        else{
            printf("message received:\n");
            printf("%s\n", rcvbuf.mtext);
        }
    }


    //destroy message queue
    msgctl(msgid, IPC_RMID, NULL);


    return EXIT_SUCCESS;
}

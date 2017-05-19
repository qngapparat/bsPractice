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
    struct msgbuf rcvbuf;

    key = 1234;

    if((msgid = msgget(key, 0666)) == -1){
        perror("msgget");
        return EXIT_SUCCESS;
    }

    //receive message  of type 1 (defined in struct msgbuf mtype in msg_send.c)
    if(msgrcv(msgid, &rcvbuf, MAX_BUF, 1, 0) == -1){
        perror("msgrcv");
        return EXIT_FAILURE;
    }

    else{
        printf("message received:\n");
        printf("%s\n", rcvbuf.mtext);
    }


    return EXIT_SUCCESS;
}

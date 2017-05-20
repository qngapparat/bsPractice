#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_BUF 128

struct msgbuf {
    long mtype;
    char mtext[MAX_BUF];
};


int main(int argc, char const *argv[]) {

    int msgid;
    key_t key;

    struct msgbuf sndbuf;
    sndbuf.mtype = 1;

    size_t buflen;
    //create msg queue if it doesnt already exist
    int mask = 0666 | IPC_CREAT;

    key = 1234;

    if((msgid = msgget(key, mask))== -1){ //in case msg doesn't exist, create one
        perror("msgget");
        return EXIT_FAILURE;
    }

    while(1){
        printf("enter a text:\n");
        //scan until a newline is inserted (\n)
        scanf("%[^\n]",sndbuf.mtext);
        getchar(); //NOTE for whatever reason

        buflen = strlen(sndbuf.mtext) + 1;

        //send message
        if((msgsnd(msgid, &sndbuf, buflen, IPC_NOWAIT)) == -1){
            perror("msgsnd");
            return EXIT_FAILURE;
        }

        else{
            printf("message sent\n");
        }
    }

    printf("completed. terminating\n");
    return EXIT_SUCCESS;
}

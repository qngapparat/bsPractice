#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//FILE* popen(char* commandString, char* mode) executes a shell command, which reads from FILE OR writes to FILE.

#define READ_SIZE 1024

int main(int argc, char const *argv[]) {

    char* cmdString = "ls -l";
    FILE* cmdDump;
    char ch;

    if((cmdDump = popen(cmdString, "r")) == NULL){
        perror("popen");
        return EXIT_FAILURE;
    }

    while((ch = fgetc(cmdDump)) != EOF){
        printf("%c", ch);
    }

    printf("\n\ndone printing\n\n");
    pclose(cmdDump);



    return EXIT_SUCCESS;
}

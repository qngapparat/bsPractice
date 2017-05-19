#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//NOTE stdout of a shell cmd remains as usual if it's popened with "r" (and vice versa)

//FILE* popen(char* commandString, char* mode) executes a shell command, which reads from FILE OR writes to FILE.

//practicing reading from FILE (eg what is printed to shell otherwise)

#define READ_SIZE 1024

int main(int argc, char const *argv[]) {

    char* cmdString = "ls -l";
    FILE* cmdDump;
    char ch;

    //reading from file
    if((cmdDump = popen(cmdString, "r")) == NULL){
        perror("popen r");
        return EXIT_FAILURE;
    }

    while((ch = fgetc(cmdDump)) != EOF){
        printf("%c", ch);
    }

    printf("\n\ndone printing\n\n");
    pclose(cmdDump);

    return EXIT_SUCCESS;

}

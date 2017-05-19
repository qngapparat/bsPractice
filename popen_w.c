#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//NOTE stdout of a shell cmd remains as usual if it's popened with "r" (and vice versa)

//FILE* popen(char* commandString, char* mode) executes a shell command, which reads from FILE OR writes to FILE.

//executing grep, and writing data into FILE which gets filtered, and the results printed

int main(int argc, char const *argv[]) {

    FILE* cmdFile;
    char cmdString[] = "grep en";

    if((cmdFile = popen(cmdString, "w")) == NULL){
        perror("popen");
        return EXIT_SUCCESS;
    }

    //feed into grep
    fprintf(cmdFile, "%s", "hep\nhen\nherk\nhenner\nnelk\nenel\n");
    pclose(cmdFile);

    printf("main program terminating\n");


    return EXIT_SUCCESS;

}

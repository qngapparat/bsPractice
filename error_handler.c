#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"

void die(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

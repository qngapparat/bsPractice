#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"
#include <stdbool.h>
#include <time.h>

#define LENGTH 16

int queue[LENGTH];

int put_ptr, take_ptr = 0;
bool empty = true;


bool enqueue(int value){
    //means that queue is fill. Empty is switched to false by the first ever enqueue, to distinguish between the initial ptr position and both pointers randomly meeting at zero.

    if(put_ptr == take_ptr && !empty){
        return false;
    }

    else{ //insert into circular array
        queue[put_ptr] = value;
        put_ptr = (put_ptr + 1) % LENGTH;
        empty = false;
    }
}

int top(){
    if(!empty){
        return queue[take_ptr];
    }
}


int dequeue(){

    if(take_ptr == put_ptr){
        printf("queue empty. couldnt dequeue\n");
        return EXIT_FAILURE; //not the most elegant solution
    }
    else{
        int temp = queue[take_ptr];
        take_ptr = (take_ptr + 1) % LENGTH;
        return temp;
    }

}

int main(int argc, char const *argv[]) {

    srand(time(NULL));

    //enqueue until queue is full (eg enqueue equals to false)
    printf("filling queue...\n");
    while(enqueue(rand()%20)){ }

    printf("top: %d\n", top());
    printf("dequeue: %d\n", dequeue());
    printf("top: %d\n", top());
    printf("dequeue: %d\n", dequeue());
    printf("top: %d\n", top());

    printf("done\n");


    return EXIT_SUCCESS;
}

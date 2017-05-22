#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"
#include <stdbool.h>
#include <time.h>

#define LENGTH 8

int queue[LENGTH];

int put_ptr, take_ptr = 0;
bool empty = true;
bool full = false;

bool enqueue(int value){
    //means that queue is fill. Empty is switched to false by the first ever enqueue, to distinguish between the initial ptr position and both pointers randomly meeting at zero.
    if(full){
        printf("enqueue: queue full\n");
        return false;
    }

    if(((put_ptr + 1) % LENGTH) == take_ptr){
        //next insert will render queue full
        full = true;
    }

     //insert into circular array
    queue[put_ptr] = value;
    put_ptr = (put_ptr + 1) % LENGTH;
    empty = false;
    printf("enqueued: %d\n", value);
    return true;
}

int top(){
    if(!empty){
        return queue[take_ptr];
    }

    else{
        printf("top: queue empty. terminating\n");
        exit(EXIT_FAILURE);
    }
}


bool dequeue(){

    if(empty){
        printf("dequeue: queue empty\n");
        return false;
    }

    if(((take_ptr + 1) % LENGTH) == put_ptr){
        //this dequeue will render the queue empty
        empty = true;
    }

    int temp = queue[take_ptr];
    take_ptr = (take_ptr + 1) % LENGTH;
    full = false;
    return true;
}

int main(int argc, char const *argv[]) {

    srand(time(NULL));

    //enqueue until queue is full (eg enqueue equals to false)
    printf("filling queue...\n");
    while(enqueue(rand()%20)){ }

    //dequeue one and enqueue one
    printf("%d\n", top());
    dequeue();
    enqueue(183);

    //print and dequeue until empty
    while(1){
        printf("%d\n", top());
        dequeue();
    }

    printf("\ndone\n");


    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool initialized = false;

void clear_element(int my_heap, int index){
    my_heap[index] = -1;
    return;
}

int find_last_element(int my_heap){
    if(!initialized){
        printf("removeMin: Heap not initialized.");
        exit(EXIT_FAILURE);
    }

    //get how many elements are stored
    int length = my_heap[0];
    //length = 3 means the last element is at position [3]
    return my_heap[length];
}

bool bubble_down(int my_heap){

}

int removeMin(int my_heap){

    if(!initialized){
        printf("removeMin: Heap not initialized.");
        exit(EXIT_FAILURE);
    }

    int root  = my_heap[1];
    my_heap[1] = find_last_element(my_heap);
    clear_element(my_heap, my_heap[0]);
    bubble_down(my_heap);


}

bool bubble_up(int my_heap){


}

bool insert(int my_heap, int value){


}

int initialize(int size){

    int my_heap[size];
    for(int i = 0; i < size; i++){
        my_heap[i] = -1;
    }

    return my_heap;
}


int main(int argc, char const *argv[]) {

    printf("size of initial heap:\n");
    int MAX_SIZE;
    scanf("%d", &MAX_SIZE);
    //since field[0] is left blank, or filled with size information
    MAX_SIZE += 1;

    int my_heap[] = initialize(MAX_SIZE);


    return EXIT_SUCCESS;
}

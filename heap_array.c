#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//NOTE flooring integers is towards 0 is needed in bubble_up(). C99 and up automatically floors towards zero, so this requires no additional functions.

//using this to avoid Indexoutofbounds exceptions, eg accessing array with invalid index.
bool can_have_left_child(int my_heap, int index){

    if((2*index) <= my_heap[0] && index != 0){
        return true;
    }

    return false;
}

bool can_have_right_child(int my_heap, int index){

    if((2*index+1) <= my_heap[0] && index != 0){
        return true;
    }

    return false;
}

int clear_element(int my_heap, int index){

    my_heap[index] = -1;
    return my_heap;
}

int find_last_element(int my_heap){


    //get how many elements are stored
    int length = my_heap[0];
    //length = 3 means the last element is at position [3]
    return my_heap[length];
}

bool bubble_down(int my_heap, int index){

/*When parent is located at index n , the left child is located at index 2n, and the right child at 2n + 1. (Assuming the root is located at index 1 of the array, not 0)*/

    if(can_have_left_child(my_heap, index) && (my_heap[index] > my_heap[2*index]) ){ //if parent is bigger than left child.
        int temp = my_heap[index];
        my_heap[index] = my_heap[2*index];
        my_heap[2*index] = temp;

        bubble_down(my_heap, 2*index); //bubble down left subtree
    }

    if(can_have_right_child(my_heap, index) && (my_heap[index] > my_heap[(2*index) + 1])){ //if parent is bigger than right child.
        int temp = my_heap[index];
        my_heap[index] = my_heap[(2*index) + 1];
        my_heap[(2*index) + 1] = temp;

        bubble_down(my_heap, (2*index+1)); //bubble down right subtree
    }

    //TODO can you ensure it was successful at this pt?
    return true;
}

int removeMin(int my_heap){

    int root  = my_heap[1];
    my_heap[1] = find_last_element(my_heap);
    my_heap = clear_element(my_heap, my_heap[0]);
    bubble_down(my_heap);


}

bool bubble_up(int my_heap, int index){

    if(index == 1){
        return true;
    }

    //check if parent is bigger
    if(my_heap[index/2] > my_heap[index]){

        //swap
        int temp = my_heap[index];
        my_heap[index] = my_heap[index/2];
        my_heap[index/2] = temp;

        //bubble up from parent position
        return bubble_up(my_heap, (index/2))
    }

    else{
        return true;
    }

}

bool insert(int my_heap, int value){

    int free_index = my_heap[0] + 1;
    my_heap[free_index] = value;

    return bubble_up(my_heap, free_index);

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

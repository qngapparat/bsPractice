#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//NOTE flooring integers is towards 0 is needed in bubble_up(). C99 and up automatically floors towards zero, so this requires no additional functions.

//using this to avoid Indexoutofbounds exceptions, eg accessing array with invalid index.

void print_heap(int my_heap[]){

    int length = my_heap[0];
    for(int i = 1; i <= length; i++){
        printf(" %d \n", my_heap[i]);
    }

    printf("printed heap\n");
    return;
}

bool can_have_left_child(int my_heap[], int index){

    if((2*index) <= my_heap[0] && index != 0){
        return true;
    }

    return false;
}

bool can_have_right_child(int my_heap[], int index){

    if((2*index+1) <= my_heap[0] && index != 0){
        return true;
    }

    return false;
}

void clear_element(int my_heap[], int index){

    my_heap[index] = -1;
    //decrease size variable
    my_heap[0] -= 1;
    return;
}

int find_last_element(int my_heap[]){


    //get how many elements are stored
    int length = my_heap[0];
    //length = 3 means the last element is at position [3]
    return my_heap[length];
}

bool bubble_down(int my_heap[], int index){

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

int removeMin(int my_heap[]){

    int root  = my_heap[1];
    //replace root with last one and delete last one
    my_heap[1] = find_last_element(my_heap);
    //decrease size variable, essentially (also sets last one in array to -1, which can be useful in more complex algorithms)
    clear_element(my_heap, my_heap[0]);

    printf("removed min: %d\n", root);

    //sort it
    bubble_down(my_heap, 1);

    return root;
}

bool bubble_up(int my_heap[], int index){

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
        return bubble_up(my_heap, (index/2));
    }

    else{
        return true;
    }

}

bool insert(int my_heap[], int value, int MAX_SIZE){

    int free_index = my_heap[0] + 1;
    if(free_index > MAX_SIZE){
        return false;
    }

    my_heap[free_index] = value;
    my_heap[0] += 1;
    printf("inserted %d\n", value);
    return bubble_up(my_heap, free_index);

}


int main(int argc, char const *argv[]) {

    //ask for size of heap
    printf("size of initial heap:\n");
    int MAX_SIZE;
    scanf("%d", &MAX_SIZE);
    //since field[0] is left blank, or filled with size information
    //MAX_SIZE += 1;

    //create array
    int my_heap[MAX_SIZE];
    for(int i = 0; i <= MAX_SIZE; i++){
        my_heap[i] = -1;
    }
        //set size varialbe to 0
    my_heap[0] = 0;
    printf("initialized\n");

    print_heap(my_heap);

    //while(insert(my_heap, rand()%20 + 3 , MAX_SIZE)){   }
    insert(my_heap, rand()%20 + 3 , MAX_SIZE);
    insert(my_heap, rand()%20 -30  , MAX_SIZE);
    insert(my_heap, rand()%20 + 3 , MAX_SIZE);
    insert(my_heap, rand()%20 + 3 , MAX_SIZE);
    insert(my_heap, 1, MAX_SIZE);

    print_heap(my_heap);


    removeMin(my_heap);
    print_heap(my_heap);
    printf("my_heap[0]: %d\n", my_heap[0]);

    printf("termianting\n");

    return EXIT_SUCCESS;
}

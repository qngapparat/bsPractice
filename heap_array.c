#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"
#include <stdbool.h>

//serving as basis for our tree. Points to root
//TODO update node_count upon insert returning true

struct earth {
    struct node* root;
    int node_count;
};

struct node{
    struct node* left;
    struct node* right;
    int value;
}

typedef struct earth Earth;
typedef struct node Node;


Earth create_earth(){

    Earth temp = malloc(sizeof(temp));
    temp.node_count = 0;
    temp.root = NULL;

    return temp;
}

bool insert_node(Earth* my_earth, int value){



}

static void destroy(Node* my_node){

    //postorder traversal to destroy all nodes
    if(my_node->left != NULL){
        destroy(my_node->left);
    }
    if(my_node->right != NULL){
        destroy(my_node->left);
    }

    free(my_node);

}

int minimum_child_value(Node* my_node){

}

int maximum_child_value(Node* my_node){

}

bool contains_node(Node* my_node, int value){

    if(value == my_node->value){
        return true;
    }

    if(my_node->left != NULL){
        contains_node(my_node->left, value);
    }

    if(my_node->right != NULL){
        contains_node(my_node->right, value);
    }

}



int main(int argc, char const *argv[]) {



    return EXIT_SUCCESS;
}

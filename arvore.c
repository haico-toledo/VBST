#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"

struct node *create_node(struct node *dad, int key){
    struct node *n = malloc(sizeof(struct node));
    if (n == NULL){
        return NULL;
    }
    
    n->key = key;
    n->l_son = NULL;
    n->r_son = NULL;
    n->dad = dad;
    
    return n;
}

struct node *find_or_insert_node(struct node *sbroot, int key){
    if (sbroot->key > key && sbroot->l_son == NULL){
        sbroot->l_son = create_node(sbroot, key);
        return sbroot->l_son; 
    }
    if (sbroot->key < key && sbroot->r_son == NULL){
        sbroot->r_son = create_node(sbroot, key);
        return sbroot->r_son;
    }
    
    if (sbroot->key > key) {
        find_or_insert_node(sbroot->l_son, key);
        
    }
    if (sbroot->key < key) {
            find_or_insert_node(sbroot->r_son, key);
    }
    return sbroot;
}

void print_tree(struct node *root) {
    if (root == NULL) {
        return;
    }
    
    printf("(");
    printf("%d ", root->key);
    print_tree(root->l_son);
    print_tree(root->r_son);
    printf(")");
    
    return;
}

void free_tree(struct node *root) {
    if(root == NULL){
        return;
    }
    free_tree(root->l_son);
    free_tree(root->r_son);
    free(root);
    return;
}




//to do:
//exclude node
    //se eh folha entao exclui
    //se eh interno:
        //rotacao: como?


//insert root node

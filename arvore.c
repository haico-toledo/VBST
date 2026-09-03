#include "arvore.h"

#include <stdlib.h>
#include <stdio.h>

#include "auxiliary.h"

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
        return find_or_insert_node(sbroot->l_son, key);
    }
    if (sbroot->key < key) {
        return find_or_insert_node(sbroot->r_son, key); 
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

struct node *minimum(struct node *sbroot) {
    if (sbroot->l_son == NULL){
        return sbroot;
    }
    
    return minimum(sbroot->l_son);
}

void delete_node(struct node **root, struct node *rem) {
    if (rem->r_son == NULL && rem->l_son ==  NULL) {
        transplant(root, rem, NULL);
        free(rem);
        return;
    }
    
    if (rem->l_son == NULL) { 
        transplant(root, rem, rem->r_son);
        free(rem);
        return;
    }

    if (rem->r_son == NULL){ 
        transplant(root, rem, rem->l_son);
        free(rem);
        return;
    }
    
    struct node *sus = minimum(rem->r_son);
    if (rem->r_son != sus) {
        transplant(root, sus, sus->r_son);
        sus->r_son = rem->r_son;
        sus->r_son->dad = sus;
    }
    transplant(root, rem, sus);
    sus->l_son = rem->l_son;
    if (sus->l_son != NULL) {
        sus->l_son->dad = sus;
    }
    
    free(rem);
    return;
}


//to do:
//colocar flag no find_or_insert para escolher entre insert ou retornar NULL se o nodo ainda nao existe
//insert root node

#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

int main (){

    struct node *root = create_node(NULL, 10);

    for (int i = 0; i < 7; i++) {
        find_or_insert_node(root, i);
    }
    
    find_or_insert_node(root, 100);
    find_or_insert_node(root, 103);
    find_or_insert_node(root, 101);
    find_or_insert_node(root, 102);
    find_or_insert_node(root, 99);
    
    print_tree(root);
    printf("\n");
    free_tree(root);
    return 0;
}

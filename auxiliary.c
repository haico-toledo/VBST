#include "auxiliary.h"

#include <stdio.h>

void transplant(struct node **root, struct node *old, struct node *new) {
    if (old == NULL) {
        fprintf(stderr, "CRITICAL ERROR IN TRANSPLANT FUNCTION, NULL parameter found");
        return;
    }
    
    if (old->dad == NULL) {
        *root = new; 
    }
    else {
        if (old->dad->l_son == old) {
            old->dad->l_son = new;
        }
        else {
            old->dad->r_son = new;
        }
    }
    if (new != NULL) {
        new->dad = old->dad;
    }
}

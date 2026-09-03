#ifndef ARVORE
#define ARVORE

struct node {
    int key;
    struct node *l_son;
    struct node *r_son;
    struct node *dad;
};

//creates node and returns it
struct node *create_node(struct node *dad, int key);

//finds node or calls create_node if it doesnt exist (uses Binary Search)
struct node *find_or_insert_node(struct node *root, int key);

//prints a given tree
void print_tree(struct node *root);

//free a given tree
void free_tree(struct node *root);

//find minimum node from a given subtree
struct node *minimum(struct node *sbroot);

//exclude an existing node and returns it or returns NULL
void delete_node(struct node **root, struct node *rem);

#endif

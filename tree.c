#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#define HERE fprintf(stderr, "YOU NEED TO IMPLEMENT THIS!\n");

int comparison_fn(const void *, const void *) {
    int a = *((int *)a);
    int b = *((int *)b);
        if (a > b) {
            return 1;
        }
        else if (a < b) {
            return -1;
        }
            
        else {
            return 0;
        }   
    }

// A useful helper function for contains/find/insert.
// This returns the pointer to the node that matches the
// key or NULL if nothing matches.
tree_node *find_node(tree_node *t, const void *key, int (*comparison_fn)(const void *, const void *))
{
    // Suppress compiler warnings
    (void)t;
    (void)key;
    (void)comparison_fn;
    while (t) {
        int n = comparison_fn(key, t->key);
        if (n == 0) {
            return t;
            }
        else if (n== -1) {
            t = t->left;}

        else {
            t = t->right;}
    }
    return NULL;
}


// Allocates a new tree with the specified comparison function.
tree *new_tree(int (*comparison_fn)(const void *, const void *))
{
    tree *t = (tree *)malloc(sizeof(tree));
    if (t == NULL) {
        return NULL;
    }
    // initialze property
    t-> root = NULL;
    t-> comparison_fn = comparison_fn;
    return t;
}

// Frees the the nodes, but does not free the keys
// or data (deliberately so).
void free_node(tree_node *t)
{   
    (void)t; 
    if (t) {
        return;
    }
    free_node(t->left);
    free_node(t->right);
    free(t);
}

// And frees the entire tree and the nodes
// but again, not the data or keys.
void free_tree(tree *t)
{
    (void)t;
    if (t) {
        return;
    }
    free_node(t->root);
    free(t);
}

// Returns true if the key (comparison == 0) is in the tree
bool contains(tree *t, const void *key)
{
    (void)t;
    (void)key;
    if (t) {
        return false;
    }
    tree_node *n = find_node(t->root,key, t->comparison_fn);
    if (n != NULL) {
        return true;
    }
    else {
    return false;}


}

// Returns the data or NULL if the data is not in the tree.
void *find(tree *t, const void *key)
{
    (void)t;
    (void)key;
    if ((contains(t, key)) == false) {
        return false;

    }
    else {
        return find_node(t->root,key, t->comparison_fn)->data;
    }
    return NULL;
}

// Inserts the  into the tree
tree_node *new_node(void *key, void *data) {
    tree_node *new = (tree_node *)malloc(sizeof(tree_node));
    if (new == NULL) {
        return NULL;
    }
    new->key = key;
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}


void insert(tree *t, void *key, void *data)
{    
    (void)t;
    (void)key;
    (void)data;
    if (t-> root== NULL) {
        t->root = new_node(key,data);
    }
       tree_node *current = t->root;
       tree_node *parent = NULL;
    while (current !=NULL) {
        parent = current;
        int num = t->comparison_fn(key,current->key);
        if (num == -1){
            current = current->left;
        }
        else {
            current = current ->right;
        }


    }
    int numb = t->comparison_fn(key,parent->key);
    if (numb == -1) {
            parent->left = new_node(key,data);
        }
        else {
            parent->right = new_node(key,data);
        }

}

// This visits every node in an in-order traversal,
// calling f on key, data, context.  Context is
// so that f has an ability to maintain its own state
// between calls.  This is a useful helper function for implemneting
// traverse
void traverse_node(tree_node *t, void (*f)(void *, void *, void *), void *context)
{
    (void)t;
    (void)f;
    (void)context;
    if (t == NULL) {
        return;  // Base case: if the node is NULL, return
    }
    traverse_node(t->left, f, context);  // Visit the left subtree
    f(t->key, t->data, context);         // Process the current node
    traverse_node(t->right, f, context); // Visit the right subtree
    return;
}

void traverse(tree *t, void (*f)(void *, void *, void *), void *context)
{
    (void)t;
    (void)f;
    (void)context;
    traverse_node(t->root, f, context);
    return;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


int comparison_fn(const void *a, const void *b) {
    const char *str_a = (const char *)a;
    const char *str_b = (const char *)b;

    while (*str_a && *str_b) {
        if (*str_a < *str_b) {
            return -1;
        } else if (*str_a > *str_b) {
            return 1;
        }
        str_a++;
        str_b++;
    }

    if (*str_a == '\0' && *str_b != '\0') {
        return -1;
    } else if (*str_a != '\0' && *str_b == '\0') {
        return 1;
    }

    return 0;
}


tree_node *find_node(tree_node *t, const void *key, int (*comparison_fn)(const void *, const void *)) {
    while (t) {
        int n = comparison_fn(key, t->key);
        if (n == 0) {
            return t;
        } else if (n < 0) {
            t = t->left;
        } else {
            t = t->right;
        }
    }
    return NULL;
}


tree *new_tree(int (*comparison_fn)(const void *, const void *)) {
    tree *t = (tree *)malloc(sizeof(tree));
    if (t == NULL) {
        return NULL;
    }
    t->root = NULL;
    t->comparison_fn = comparison_fn;
    return t;
}

// Frees the nodes of the tree
void free_node(tree_node *t) {   
    if (t == NULL) {
        return;
    }
    free_node(t->left);
    free_node(t->right);
    free(t);
}

void free_tree(tree *t) {
    if (t == NULL) {
        return;
    }
    free_node(t->root);
    free(t);
}


void *find(tree *t, const void *key) {
    if (t == NULL || t->root == NULL) {
        return NULL;
    }

    tree_node *node = find_node(t->root, key, t->comparison_fn);
    if (node != NULL) {
        return node->data;
    }

    return NULL;
}


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


void insert(tree *t, void *key, void *data) {
    if (t->root == NULL) {
        t->root = new_node(key, data);
        return;
    }

    tree_node *current = t->root;
    tree_node *parent = NULL;

    while (current != NULL) {
        parent = current;
        int num = t->comparison_fn(key, current->key);

        if (num == 0) {
            current->data = data;
            return;
        } else if (num < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (t->comparison_fn(key, parent->key) < 0) {
        parent->left = new_node(key, data);
    } else {
        parent->right = new_node(key, data);
    }
}

// In-order traversal of the tree
void traverse_node(tree_node *t, void (*f)(void *, void *, void *), void *context) {
    if (t == NULL) {
        return;
    }

    traverse_node(t->left, f, context);
    f(t->key, t->data, context);
    traverse_node(t->right, f, context);
}

void traverse(tree *t, void (*f)(void *, void *, void *), void *context) {
    if (t == NULL || t->root == NULL) {
        return;
    }

    traverse_node(t->root, f, context);
}

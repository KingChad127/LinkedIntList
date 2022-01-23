#ifndef LINKEDINTLIST_NODE_H
#define LINKEDINTLIST_NODE_H

struct node {
    struct node *prev;
    struct node *next;
    int value;
};

static size_t node_size = 2 * sizeof(struct node *) + sizeof(int);

struct node *node_create(struct node *prev, struct node *next);

void node_set_next(struct node *curr, struct node *next);

void node_set_prev(struct node *curr, struct node *prev);

#endif //LINKEDINTLIST_NODE_H

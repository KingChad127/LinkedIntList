#ifndef LINKEDINTLIST_NODE_H
#define LINKEDINTLIST_NODE_H

struct node {
    struct node *prev;
    struct node *next;
    int value;
};

/**
 * Set the next node
 * @param curr pointer to the node to modify
 * @param next pointer to the node to set as next
 */
void node_set_next(struct node *curr, struct node *next);

/**
 * Set the previous node
 * @param curr pointer to the node to modify
 * @param prev pointer to the node to set as prev
 */
void node_set_prev(struct node *curr, struct node *prev);

#endif //LINKEDINTLIST_NODE_H

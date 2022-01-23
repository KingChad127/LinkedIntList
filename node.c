#include <stdlib.h>
#include "node.h"

/**
 * Create a new node on the heap and assign prev and next nodes
 * @param prev the previous node
 * @param next the next node
 * @return a pointer to this node
 */
struct node *node_create(struct node *prev, struct node *next) {
    struct node *n = malloc(node_size);
    n->prev = prev;
    n->next = next;
    return n;
}

/**
 * Set the next node
 * @param curr pointer to the node to modify
 * @param next pointer to the node to linked_int_list_set as next
 */
void node_set_next(struct node *curr, struct node *next) {
    curr->next = next;
}

/**
 * Set the previous node
 * @param curr pointer to the node to modify
 * @param prev pointer to the node to linked_int_list_set as prev
 */
void node_set_prev(struct node *curr, struct node *prev) {
    curr->prev = prev;
}
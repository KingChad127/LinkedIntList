//
// Created by Abhinav  Chadaga on 1/23/22.
//

#ifndef LINKEDINTLIST_LINKED_INT_LIST_H
#define LINKEDINTLIST_LINKED_INT_LIST_H

#include <stdbool.h>
#include "node.h"


struct linked_int_list {
    struct node *header;
    int size;
};
/* create a new linked list on the stack */
struct linked_int_list linked_int_list_create();

void linked_int_list_add(struct linked_int_list *list, int value);

struct node *linked_int_list_get_node_at_pos(struct linked_int_list *list, int position);

void linked_int_list_insert(struct linked_int_list *list, int pos, int value);

int linked_int_list_set(struct linked_int_list *list, int pos, int value);

int linked_int_list_get(struct linked_int_list *list, int pos);

int linked_int_list_remove_node(struct linked_int_list *list, struct node *node_to_remove);

int linked_int_list_remove_by_pos(struct linked_int_list *list, int pos);

bool linked_int_list_remove_by_value(struct linked_int_list *list, int value);

int linked_int_list_index_pos(struct linked_int_list *list, int pos, int value);

int linked_int_list_index_of(struct linked_int_list *list, int value);

struct linked_int_list linked_int_list_get_sub_list(struct linked_int_list *list, int start, int stop);

void linked_int_list_remove_range(struct linked_int_list *list, int start, int stop);

void linked_int_list_make_empty(struct linked_int_list *list);

void print_list(struct linked_int_list *list);

#endif //LINKEDINTLIST_LINKED_INT_LIST_H

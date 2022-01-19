#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Note: C is pass by value. If I pass the actual struct into the below methods, the C compiler
// will make a copy of that struct and proceed to modify it. I want to modify the original, thus,
// I pass the pointer to that object so that the C compiler copies the pointer and not the struct.


/**
 * list node struct
 */
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
void set_next(struct node *curr, struct node *next) {
    curr->next = next;
}

/**
 * Set the previous node
 * @param curr pointer to the node to modify
 * @param prev pointer to the node to set as prev
 */
void set_prev(struct node *curr, struct node *prev) {
    curr->prev = prev;
}

/**
 * linked_int_list struct
 */
struct linked_int_list {
    struct node *header; // pointer to header node
    int size; // size of the list excluding the header node
};

static int node_size = sizeof(struct linked_int_list *) + sizeof(int);

/**
 * Get the node at a certain position
 * O(N) runtime
 * @param position the position of the node pointer to return
 * @param list the list to traverse through
 * @return a pointer to the node that was requested
 */
struct node *get_node_at_pos(int position, struct linked_int_list *list) {
    struct node *tmp = list->header;
    for (int i = -1; i < position; ++i) {
        tmp = tmp->next;
    }
    return tmp;
}

/**
 * Add an element to the list
 * @param value the value to add
 * @param list pointer to the list to add to
 */
void add(int value, struct linked_int_list *list) {
    list->size++;
    struct node *n = malloc(node_size);
    n->value = value;
    n->prev = list->header->prev;
    n->next = list->header;
    list->header->prev->next = n;
    list->header->prev = n;
}

/**
 * Insert a new value at a specific index
 * @param value to insert
 * @param pos position to insert at
 * @param list list to insert into
 */
void insert(int value, int pos, struct linked_int_list *list) {
    list->size++;
    struct node *prev = get_node_at_pos(pos - 1, list);
    struct node *next = prev->next;
    struct node *insert_node = malloc(node_size);
    set_prev(insert_node, prev);
    set_next(insert_node, next);
    insert_node->value = value;
    set_next(prev, insert_node);
    set_prev(next, insert_node);
}

/**
 * Change the value at a certain position without changing the size of the list
 * @param pos of the node to modify
 * @param value new value to replace the old value with
 * @param list list to modify
 * @return the value that was replaced
 */
int set(int pos, int value, struct linked_int_list *list) {
    struct node *node_to_change = get_node_at_pos(pos, list);
    int old_value = node_to_change->value;
    node_to_change->value = value;
    return old_value;
}

/**
 * Return the value at the given index
 * @param pos return the value at this index
 * @param list list to look through
 * @return the value at pos index
 */
int get(int pos, struct linked_int_list *list) {
    struct node *n = get_node_at_pos(pos, list);
    return n->value;
}

/**
 * Remove the node passed in from the list
 * @param node_to_remove tgt
 * @param list to remove from
 * @return the value contained in the node removed
 */
int remove_node(struct node *node_to_remove, struct linked_int_list *list) {
    int ret_val = node_to_remove->value;
    struct node *prev = node_to_remove->prev;
    struct node *next = node_to_remove->next;
    set_next(prev, next);
    set_prev(next, prev);
    free(node_to_remove);
    return ret_val;
}

/**
 * Remove an element from the list based on position
 * @param pos position to remove from
 * @param list to remove from
 * @return the value removed
 */
int remove_at_pos(int pos, struct linked_int_list *list) {
    struct node *node_to_remove = get_node_at_pos(pos, list);
    int ret_val = remove_node(node_to_remove, list);
    list->size--;
    return ret_val;
}

/**
 * Remove the leftmost occurence of value from the list
 * @param value to remove
 * @param list to remove from
 * @return true if the list was changed as a result of this function
 */
bool remove_by_value(int value, struct linked_int_list *list) {
    bool removed = false;
    struct node *tmp = list->header;
    while (tmp != NULL && !removed) {
        if (tmp->value == value) {
            removed = true;
            remove_node(tmp, list);
        } else {
            tmp = tmp->next;
        }
    }
}


/**
 * Print a linked list given the first node of the list
 * @param first node of the linked list
 */
void print_list(struct linked_int_list *list) {
    printf("[ ");
    int i = 0;
    int len = list->size;
    struct node *tmp = list->header->next;
    while (tmp != NULL && i < len) {
        int value = tmp->value;
        printf("%d ", value);
        i++;
        tmp = tmp->next;
    }
    printf("]\n");
}

int main() {
    /**
     * Make the header
     */
    struct node header = {
            &header,
            &header,
    };

    /*
     * Make the LinkedList Struct
     */
    struct linked_int_list list = {
            &header,
            0,
    };

    /*
     * Populate the linked list
     */
    for (int i = 0; i < 4; ++i) {
        add(i, &list);
    }
    // print the list after adding
    print_list(&list);

    insert(6, 2, &list);
    print_list(&list);
}

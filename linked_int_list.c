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

/**
 * The size of a single node = the size of the pointer to the
 */
static int node_size = 2 * sizeof(struct node *) + sizeof(int);

/**
 * Create a new empty linked_int_list on the heap
 * @return a pointer to this newly created empty linked_int_list
 */
struct linked_int_list *create_new_list() {
    // create header dynamically
    struct node *header = malloc(node_size);
    header->prev = header;
    header->next = header;
    // create list dynamically
    struct linked_int_list *result = malloc(sizeof(int) + sizeof(struct node *));
    result->header = header;
    result->size = 0;
    // return the memory address of this new empty list
    return result;
}

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
    list->size--;
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
    return ret_val;
}

/**
 * Remove the leftmost occurrence of value from the list
 * @param value to remove
 * @param list to remove from
 * @return true if the list was changed as a result of this function
 */
bool remove_by_value(int value, struct linked_int_list *list) {
    bool removed = false;
    struct node *tmp = list->header->next;
    while (tmp != list->header && !removed) {
        if (tmp->value == value) {
            removed = true;
            remove_node(tmp, list);
        } else {
            tmp = tmp->next;
        }
    }
}
/**
 * Return the index of the left most occurrence of a value from the list after a certain position
 * @param value to remove
 * @param pos position to start looking from
 * @param list to look through
 * @return the index of the value that was found, or -1 if value is not in the list
 */
int index_pos(int value, int pos, struct linked_int_list *list) {
    int not_found = -1;
    int index = pos;
    struct node *tmp = list->header->next;
    while (tmp != list->header) {
        if (tmp->value == value) {
            return index;
        }
        tmp = tmp->next;
        index++;
    }
    // element wasn't found after iterating through the list
    return not_found;
}

/**
 * Look for a value and find its index
 * @param value to look for
 * @param list to remove from
 * @return the index of the value if found, else return -1
 */
int index_of(int value, struct linked_int_list *list) {
    return index_pos(value, 0, list);
}

/**
 * Return a sublist of elements in this list from start inclusive to stop exclusive. This list is
 * not changed as a result of this call.
 * @param start index of the first element of the sublist
 * @param stop index of the last element of the sublist
 * @param list the list from which to create the sublist
 * @return a list with stop - start elements. The elements are from positions start inclusive to
 * stop exclusive in this list. If stop == start, the returned list is empty
 */
struct linked_int_list *get_sub_list(int start, int stop, struct linked_int_list *list) {
    struct linked_int_list *result = create_new_list();
    struct node *tmp = get_node_at_pos(start, list);
    for (int i = start; i < stop; ++i) {
        add(tmp->value, result);
        tmp = tmp->next;
    }

    return result;
}

/**
 * Remove a range from the list start to stop, inclusive, exclusive
 * @param start the first index to remove from
 * @param stop the last index to remove (exclusive)
 * @param list to remove from
 */
void remove_range(int start, int stop, struct linked_int_list *list) {
    struct node *remove = get_node_at_pos(start, list);
    struct node *next = remove->next;
    int size = stop - start;
    for (int i = 0; i < size; ++i) {
        remove_node(remove, list);
        remove = next;
        next = next->next;
    }
}

/**
 * Remove every node from the list and free the memory of these unused nodes
 * @param list to remove from
 */
void make_empty(struct linked_int_list *list) {
    remove_range(0, list->size, list);
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

    int x = 6;
    printf("size of an int x: %lu\n", sizeof(x));

    struct linked_int_list *list = create_new_list();

    for (int i = 0; i < 100; ++i) {
        add(i, list);
    }

    printf("list: ");
    print_list(list);

    struct node *tmp = list->header->next;
    int nodes = 1;
    while (tmp != list->header) {
        tmp = tmp->next;
        nodes++;
    }
    unsigned long mem_size = nodes * node_size + sizeof(int);
    printf("Number of nodes: %d\n", nodes);
    printf("Memory used up by the list = %lu\n", mem_size);


    printf("remove range 20-50: ");
    remove_range(20, 50, list);
    print_list(list);

    printf("make empty: ");
    make_empty(list);
    print_list(list);

    tmp = list->header->next;
    nodes = 1;
    while (tmp != list->header) {
        tmp = tmp->next;
        nodes++;
    }
    mem_size = nodes * node_size + sizeof(int);
    printf("Number of nodes: %d\n", nodes);
    printf("Memory used up by the list = %lu\n", mem_size);

    /*
     * stress test
     */
//    for (int i = 0; i < 700000; ++i) {
//        struct linked_int_list *l = create_new_list();
//        for (int j = 0; j < 1000; ++j) {
//            add(i, l);
//        }
//        printf("finished list: ");
//        print_list(l);
//        make_empty(l);
//        printf("empty list: ");
//        print_list(l);
//    }

    return EXIT_SUCCESS;
}

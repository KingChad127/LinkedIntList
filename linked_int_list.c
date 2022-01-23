#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"
#include "linked_int_list.h"

// Note: C is pass by value. If I pass the actual struct into the below methods, the C compiler
// will make a copy of that struct and proceed to modify it. I want to modify the original, thus,
// I pass the pointer to that object so that the C compiler copies the pointer and not the struct.

///**
// * Create a new empty linked_int_list on the heap
// * @return a pointer to this newly created empty linked_int_list
// */
//struct linked_int_list *linked_int_list_create() {
//    struct node *header = node_create(NULL, NULL);
//    header->prev = header;
//    header->next = header;
//    struct linked_int_list *result = (struct linked_int_list *) malloc(sizeof(struct node *) + sizeof(int));
//    result->header = header;
//    result->size = 0;
//    return result;
//}

/**
 * Create a new empty linked_int_list on the stack
 * @return this newly created empty linked_int_list
 */
struct linked_int_list linked_int_list_create() {
    struct node *header = node_create(NULL, NULL);
    header->prev = header;
    header->next = header;
    return (struct linked_int_list) {
        .header = header,
        .size = 0,
    };
}

/**
 * Add an element to the list
 * @param list pointer to the list to linked_int_list_add to
 * @param value the value to linked_int_list_add
 */
void linked_int_list_add(struct linked_int_list *list, int value) {
    list->size++;
    struct node *n = (struct node *) malloc(node_size);
    n->value = value;
    n->prev = list->header->prev;
    n->next = list->header;
    list->header->prev->next = n;
    list->header->prev = n;
}

/**
 * Get the node at a certain position
 * O(N) runtime
 * @param list the list to traverse through
 * @param position the position of the node pointer to return
 * @return a pointer to the node that was requested
 */
struct node *linked_int_list_get_node_at_pos(struct linked_int_list *list, int position) {
    struct node *tmp = list->header;
    for (int i = -1; i < position; ++i) {
        tmp = tmp->next;
    }
    return tmp;
}

/**
 * Insert a new value at a specific index
 * @param list list to linked_int_list_insert into
 * @param value to linked_int_list_insert
 * @param pos position to linked_int_list_insert at
 */
void linked_int_list_insert(struct linked_int_list *list, int pos, int value) {
    list->size++;
    struct node *prev = linked_int_list_get_node_at_pos(list, pos - 1);
    struct node *next = prev->next;
    struct node *insert_node = (struct node *) malloc(node_size);
    node_set_prev(insert_node, prev);
    node_set_next(insert_node, next);
    insert_node->value = value;
    node_set_next(prev, insert_node);
    node_set_prev(next, insert_node);
}

/**
 * Change the value at a certain position without changing the size of the list
 * @param list list to modify
 * @param pos of the node to modify
 * @param value new value to replace the old value with
 * @return the value that was replaced
 */
int linked_int_list_set(struct linked_int_list *list, int pos, int value) {
    struct node *node_to_change = linked_int_list_get_node_at_pos(list, pos);
    int old_value = node_to_change->value;
    node_to_change->value = value;
    return old_value;
}

/**
 * Return the value at the given index
 * @param list list to look through
 * @param pos return the value at this index
 * @return the value at pos index
 */
int linked_int_list_get(struct linked_int_list *list, int pos) {
    struct node *n = linked_int_list_get_node_at_pos(list, pos);
    return n->value;
}

/**
 * Remove the node passed in from the list
 * @param list to remove from
 * @param node_to_remove tgt
 * @return the value contained in the node removed
 */
int linked_int_list_remove_node(struct linked_int_list *list, struct node *node_to_remove) {
    list->size--;
    int ret_val = node_to_remove->value;
    struct node *prev = node_to_remove->prev;
    struct node *next = node_to_remove->next;
    node_set_next(prev, next);
    node_set_prev(next, prev);
    free(node_to_remove);
    return ret_val;
}

/**
 * Remove an element from the list based on position
 * @param list to remove from
 * @param pos position to remove from
 * @return the value removed
 */
int linked_int_list_remove_by_pos(struct linked_int_list *list, int pos) {
    struct node *node_to_remove = linked_int_list_get_node_at_pos(list, pos);
    int ret_val = linked_int_list_remove_node(list, node_to_remove);
    return ret_val;
}

/**
 * Remove the leftmost occurrence of value from the list
 * @param list to remove from
 * @param value to remove
 * @return true if the list was changed as a result of this function
 */
bool linked_int_list_remove_by_value(struct linked_int_list *list, int value) {
    bool removed = false;
    struct node *tmp = list->header->next;
    while (tmp != list->header && !removed) {
        if (tmp->value == value) {
            removed = true;
            linked_int_list_remove_node(list, tmp);
        } else {
            tmp = tmp->next;
        }
    }
    return removed;
}

/**
 * Return the index of the left most occurrence of a value from the list after a certain position
 * @param list to look through
 * @param pos position to start looking from
 * @param value to find
 * @return the index of the value that was found, or -1 if value is not in the list
 */
int linked_int_list_index_pos(struct linked_int_list *list, int pos, int value) {
    int not_found = -1;
    int index = pos;
    struct node *tmp = linked_int_list_get_node_at_pos(list, pos);
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
int linked_int_list_index_of(struct linked_int_list *list, int value) {
    return linked_int_list_index_pos(list, 0, value);
}

/**
 * Return a sublist of elements in this list from start inclusive to stop exclusive. This list is
 * not changed as a result of this call.
 * @param list the list from which to create the sublist
 * @param start index of the first element of the sublist
 * @param stop index of the last element of the sublist
 * @return a list with stop - start elements. The elements are from positions start inclusive to
 * stop exclusive in this list. If stop == start, the returned list is empty
 */
struct linked_int_list linked_int_list_get_sub_list(struct linked_int_list *list, int start, int stop) {
    struct linked_int_list result = linked_int_list_create();
    struct node *tmp = linked_int_list_get_node_at_pos(list, start);
    for (int i = start; i < stop; ++i) {
        linked_int_list_add(&result, tmp->value);
        tmp = tmp->next;
    }

    return result;
}

/**
 * Remove a range from the list start to stop, inclusive, exclusive
 * @param list to remove from
 * @param start the first index to remove from
 * @param stop the last index to remove (exclusive)
 */
void linked_int_list_remove_range(struct linked_int_list *list, int start, int stop) {
    struct node *remove = linked_int_list_get_node_at_pos(list, start);
    struct node *next = remove->next;
    int size = stop - start;
    for (int i = 0; i < size; ++i) {
        linked_int_list_remove_node(list, remove);
        remove = next;
        next = next->next;
    }
}

/**
 * Remove every node from the list and free the memory of these unused nodes
 * @param list to remove from
 */
void linked_int_list_make_empty(struct linked_int_list *list) {
    linked_int_list_remove_range(list, 0, list->size);
}

/**
 * Print a linked list given a pointer to the list
 * @param list the list to print
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
    // some basic test for this linked_int_list

    // test 1: create new list
    struct linked_int_list list = linked_int_list_create();
    printf("test 1: create new list\n");
    print_list(&list); // expected: [ ]

    // test 2: linked_int_list_add
    for (int i = 0; i < 6; ++i) {
        linked_int_list_add(&list, i);
    }

    for (int i = 7; i < 10; ++i) {
        linked_int_list_add(&list, i);
    }

    printf("test 2: add\n");
    print_list(&list); // expected: [ 0 1 2 3 4 5 7 8 9 ]

    // test 3: linked_int_list_insert
    linked_int_list_insert(&list, 6, 6);
    printf("test 3: insert\n");
    print_list(&list); // expected: [ 0 1 2 3 4 5 6 7 8 9 ]

    // test 4: linked_int_list_set
    linked_int_list_set(&list, 0, 10);
    printf("test 4: set\n");
    print_list(&list); // expected: [ 10 1 2 3 4 5 6 7 8 9 ]

    // test 5: linked_int_list_get
    int actual = linked_int_list_get(&list, 6);
    printf("test 5: get\n");
    printf("expected: 6, ");
    printf("actual: %d\n", actual);

    // test 6: remove at pos
    actual = linked_int_list_remove_by_pos(&list, 5);
    printf("test 6: remove at pos\n");
    printf("expected: 5, ");
    printf("actual: %d, list: ", actual);
    print_list(&list); // expected: [ 10 1 2 3 4 6 7 8 9 ]

    // test 7: remove by value
    bool actual_bool = linked_int_list_remove_by_value(&list, 8);
    printf("test 7: remove by value\n");
    printf("expected: 1, ");
    printf("actual: %d, list: ", actual_bool);
    print_list(&list); // expected: [ 10 1 2 3 4 6 7 9 ]

    // test 8: index_pos
    actual = linked_int_list_index_pos(&list, 4, 10);
    printf("test 8: index from position\n");
    printf("expected: -1, ");
    printf("actual: %d\n", actual);

    // test 9: index_of
    actual = linked_int_list_index_of(&list, 10);
    printf("test 9: index of\n");
    printf("expected: 0, ");
    printf("actual: %d\n", actual);

    // test 10: get sub list
    struct linked_int_list sub_list = linked_int_list_get_sub_list(&list, 1, 4);
    printf("test 10: get sub list\n");
    printf("expected: [ 1 2 3 ], ");
    printf("actual: ");
    print_list(&sub_list);

    // test 11: remove range
    linked_int_list_remove_range(&list, 4, 8);
    printf("test 11: remove range\n");
    printf("expected: [ 10 1 2 3 ], ");
    printf("actual: ");
    print_list(&list);

    // test 12: make empty
    linked_int_list_make_empty(&list);
    printf("test 12: make empty\n");
    printf("expected: 0, [ ]; ");
    printf("actual: %d, ", list.size);
    print_list(&list);
    printf("\n");

    // stress test: create and destroy linked list 100,000 times to ensure that there are no memory leaks
    // after a list is destroyed, the memory used by the nodes should be freed
    struct linked_int_list l = linked_int_list_create();
    printf("Stress Test\n");
    for (int i = 0; i < 100000; ++i) {
        // printf("%d\n", i);
        for (int j = 0; j < 10000; ++j) {
            linked_int_list_add(&l, i);
        }
        linked_int_list_make_empty(&l);
    }

    return EXIT_SUCCESS;
}

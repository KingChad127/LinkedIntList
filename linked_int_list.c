#include <stdio.h>
#include <stdlib.h>

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
 * Get the node at a certain position
 * O(N) runtime
 * @param position the position of the node pointer to return  
 * @param list the list to traverse through
 * @return a pointer to the node that was requested
 */
struct node *get_node_at_pos(int position, struct linked_int_list *list) {
    // precondition checking
    if (position < 0 || position >= list->size) {
        printf("Invalid list position");
        return NULL;
    }
    struct node *tmp = list->header;
    for (int i = 0; i <= position; ++i) {
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
    struct node *n = malloc(sizeof(list->header) + sizeof(list->size));
    n->value = value;
    n->prev = list->header->prev;
    n->next = list->header;
    list->header->prev->next = n;
    list->header->prev = n;
}

void insert(int value, int position, struct linked_int_list *list) {

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
    printf("]");
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
    for (int i = 0; i < 10; ++i) {
        add(i, &list);
    }
    // print the list after adding
    print_list(&list);
    // access every item in the list
    for (int i = 0; i < list.size; ++i) {
        printf("List Item %d: %d\n", i, get_node_at_pos(i, &list)->value);
    }
}

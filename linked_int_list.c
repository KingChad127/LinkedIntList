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
 * linked_int_list struct
 */
struct linked_int_list {
    struct node *header; // pointer to header node
    int size; // size of the list excluding the header node
};

void add(int value, struct linked_int_list *list) {
    list->size++;
    struct node *n = malloc(sizeof(list->header) + sizeof(list->size));
    n->value = value;
    n->prev = list->header->prev;
    n->next = list->header;
    list->header->prev->next = n;
    list->header->prev = n;
}

/**
 * Print a linked list given the first node of the list
 * @param first node of the linked list
 */
void print_list(struct linked_int_list *list) {
    // print nothing if the size is 0 to avoid infinite loop
    int i = 0;
    int len = list->size;
    struct node *tmp = list->header->next;
    while (tmp != NULL && i < len) {
        int value = tmp->value;
        printf("index: %d, value: %d\n", i, value);
        i++;
        tmp = tmp->next;
    }
}

int main() {
    struct node header = {
            &header,
            &header,
    };

    struct linked_int_list list = {
            &header,
            0,
    };

    for (int i = 0; i < 10; ++i) {
        add(i, &list);
    }
    print_list(&list);
}

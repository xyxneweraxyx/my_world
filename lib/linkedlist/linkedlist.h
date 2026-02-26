/*
** EPITECH PROJECT, 2026
** linkedlist
** File description:
** A simple linked list library.
*/

#ifndef LINKEDLIST
    #define LINKEDLIST

    #include <stddef.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #define LINKED_SUCC 0
    #define LINKED_FAIL -1

// Typedefs

typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} node_t;


typedef struct linkedlist {
    node_t *head;
    size_t node_count;
} linkedlist_t;

// Functions

/*
Create a new linkedlist object.
Returns NULL on fail.
*/
linkedlist_t *linkedlist_ini(void);

/*
Destroys a linkedlist object.
Set "delete_data" to true to free the data in nodes.
*/
size_t linkedlist_destroy(linkedlist_t *linkedlist, bool delete_data);

/*
Creates a new node object and initializes it.
Returns NULL on fail.
*/
node_t *linkedlist_newnode(void *data);

/*
Inserts a node object as the new head of the list.
*/
size_t linkedlist_inserthead(linkedlist_t *linkedlist, node_t *node);

/*
Inserts a node object in the list after the first successful comparison.
Returns LINKED_FAIL if no object was found.
*/
size_t linkedlist_insert(linkedlist_t *linkedlist, node_t *node,
    bool (*comp)(node_t *toinsert, node_t *comp));

/*
Removes the first node object in the list that matches the comparison function.
*/
size_t linkedlist_remove(linkedlist_t *linkedlist,
    bool (*comp)(node_t *node), bool delete_data);

/*
Removes all node objects in the list that match the comparison function.
Returns the total amount of removed objects, or LINKED_FAIL on error.
*/
size_t linkedlist_massremove(linkedlist_t *linkedlist,
    bool (*comp)(node_t *node), bool delete_data);

#endif

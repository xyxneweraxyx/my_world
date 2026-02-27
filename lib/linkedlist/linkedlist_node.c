/*
** EPITECH PROJECT, 2026
** linkedlist
** File description:
** A simple linked list library.
*/

#include "./linkedlist.h"

size_t linkedlist_inserthead(linkedlist_t *linkedlist, node_t *node)
{
    if (!linkedlist || !node)
        return (size_t)LINKED_FAIL;
    node->next = NULL;
    node->prev = NULL;
    if (linkedlist->head)
        linkedlist->head->prev = node;
    node->next = linkedlist->head;
    linkedlist->head = node;
    linkedlist->node_count += 1;
    return (size_t)LINKED_SUCC;
}

size_t linkedlist_insert(linkedlist_t *linkedlist, node_t *node,
    bool (*comp)(node_t *toinsert, node_t *comp))
{
    node_t *node_comp = linkedlist->head;

    if (!linkedlist || !node || !comp)
        return (size_t)LINKED_FAIL;
    node->next = NULL;
    node->prev = NULL;
    if (!node_comp)
        return linkedlist_inserthead(linkedlist, node);
    while (node_comp && !comp(node, node_comp))
        node_comp = node_comp->next;
    if (!node_comp)
        return (size_t)LINKED_FAIL;
    if (node_comp->next)
        node_comp->next->prev = node;
    node->next = node_comp->next;
    node->prev = node_comp;
    node_comp->next = node;
    linkedlist->node_count += 1;
    return (size_t)LINKED_SUCC;
}

static void rm_node(linkedlist_t *linkedlist, node_t *node, bool delete_data)
{
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    if (linkedlist->head == node)
        linkedlist->head = node->next;
    if (delete_data)
        free(node->data);
    free(node);
    linkedlist->node_count -= 1;
}

size_t linkedlist_remove(linkedlist_t *linkedlist,
    bool (*comp)(node_t *node), bool delete_data)
{
    node_t *node = NULL;

    if (!linkedlist || !comp)
        return (size_t)LINKED_FAIL;
    node = linkedlist->head;
    while (node && !comp(node))
        node = node->next;
    if (!node)
        return (size_t)LINKED_FAIL;
    rm_node(linkedlist, node, delete_data);
    return (size_t)LINKED_SUCC;
}

size_t linkedlist_massremove(linkedlist_t *linkedlist,
    bool (*comp)(node_t *node), bool delete_data)
{
    node_t *node = NULL;
    node_t *temp = NULL;
    size_t total = 0;

    if (!linkedlist || !comp)
        return (size_t)LINKED_FAIL;
    node = linkedlist->head;
    while (node) {
        temp = node;
        node = node->next;
        if (comp(temp)) {
            rm_node(linkedlist, temp, delete_data);
            total += 1;
        }
    }
    return total;
}

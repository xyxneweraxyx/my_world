/*
** EPITECH PROJECT, 2025
** setfml
** File description:
** Tired of initializing csfml? Up your workflow with this simple wrapper.
*/

#include "./setfml.h"

static bool insert_func(node_t *toinsert, node_t *comp)
{
    function_t *n_before = NULL;
    function_t *n_insert = NULL;

    if (!toinsert || !comp)
        return true;
    n_insert = (function_t *)toinsert->data;
    n_before = (function_t *)comp->data;
    if (n_insert->function == n_before->function)
        return true;
    return false;
}

size_t setfml_add_event(setfml_t *setfml, size_t (*f_before)(setfml_t *setfml),
    char name[BUFF_FUNC_NAME], size_t (*callback)(setfml_t *setfml))
{
    node_t *node = c_alloc(sizeof(node_t), 1, setfml->alloc);
    function_t *function = c_alloc(sizeof(function_t), 1, setfml->alloc);

    if (!node || !function)
        return (size_t)SETFML_FAIL;
    function->paused = false;
    function->function = f_before;
    str_cpy(name, function->name);
    node->data = (void *)function;
    if (!f_before) {
        if (linkedlist_inserthead(setfml->functions[LOOP_EVENT], node)
            == (size_t)SETFML_FAIL)
            return (size_t)SETFML_FAIL;
    } else {
        if (linkedlist_insert(setfml->functions[LOOP_EVENT], node, &insert_func)
            == (size_t)SETFML_FAIL)
        return (size_t)SETFML_FAIL;
    }
    function->function = (void*)callback;
    return (size_t)SETFML_SUCC;
}

size_t setfml_add_data(setfml_t *setfml, size_t (*f_before)(setfml_t *setfml),
    char name[BUFF_FUNC_NAME], size_t (*callback)(setfml_t *setfml))
{
    node_t *node = c_alloc(sizeof(node_t), 1, setfml->alloc);
    function_t *function = c_alloc(sizeof(function_t), 1, setfml->alloc);

    if (!node || !function)
        return (size_t)SETFML_FAIL;
    function->paused = false;
    function->function = f_before;
    str_cpy(name, function->name);
    node->data = (void *)function;
    if (!f_before) {
        if (linkedlist_inserthead(setfml->functions[LOOP_DATA], node)
            == (size_t)SETFML_FAIL)
            return (size_t)SETFML_FAIL;
    } else {
        if (linkedlist_insert(setfml->functions[LOOP_DATA], node, &insert_func)
            == (size_t)SETFML_FAIL)
        return (size_t)SETFML_FAIL;
    }
    function->function = (void*)callback;
    return (size_t)SETFML_SUCC;
}

size_t setfml_add_render(setfml_t *setfml, size_t (*f_before)(setfml_t *setfml),
    char name[BUFF_FUNC_NAME], size_t (*callback)(setfml_t *setfml))
{
    node_t *node = c_alloc(sizeof(node_t), 1, setfml->alloc);
    function_t *function = c_alloc(sizeof(function_t), 1, setfml->alloc);

    if (!node || !function)
        return (size_t)SETFML_FAIL;
    function->paused = false;
    function->function = f_before;
    str_cpy(name, function->name);
    node->data = (void *)function;
    if (!f_before) {
        if (linkedlist_inserthead(setfml->functions[LOOP_RENDER], node)
            == (size_t)SETFML_FAIL)
            return (size_t)SETFML_FAIL;
    } else {
        if (linkedlist_insert(setfml->functions[LOOP_RENDER], node, &insert_func)
            == (size_t)SETFML_FAIL)
        return (size_t)SETFML_FAIL;
    }
    function->function = (void*)callback;
    return (size_t)SETFML_SUCC;
}

size_t setfml_add_draw(setfml_t *setfml, size_t (*f_before)(setfml_t *setfml),
    char name[BUFF_FUNC_NAME], size_t (*callback)(setfml_t *setfml))
{
    node_t *node = c_alloc(sizeof(node_t), 1, setfml->alloc);
    function_t *function = c_alloc(sizeof(function_t), 1, setfml->alloc);

    if (!node || !function)
        return (size_t)SETFML_FAIL;
    function->paused = false;
    function->function = f_before;
    str_cpy(name, function->name);
    node->data = (void *)function;
    if (!f_before) {
        if (linkedlist_inserthead(setfml->functions[LOOP_DRAW], node)
            == (size_t)SETFML_FAIL)
            return (size_t)SETFML_FAIL;
    } else {
        if (linkedlist_insert(setfml->functions[LOOP_DRAW], node, &insert_func)
            == (size_t)SETFML_FAIL)
        return (size_t)SETFML_FAIL;
    }
    function->function = (void*)callback;
    return (size_t)SETFML_SUCC;
}
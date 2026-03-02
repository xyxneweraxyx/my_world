/*
** EPITECH PROJECT, 2025
** setfml
** File description:
** Tired of initializing csfml? Up your workflow with this simple wrapper.
*/

#include "./setfml.h"

static node_t *func_single_loop(setfml_t *setfml,
    char name[BUFF_FUNC_NAME], loop_t event)
{
    function_t *func = NULL;

    for (node_t *n = setfml->functions[event]->head; n; n = n->next) {
        func = (function_t *)n->data;
        if (!str_cmp(func->name, name))
            return n;
    }
    return NULL;
}

static loop_t func_from_name(setfml_t *setfml, char name[BUFF_FUNC_NAME])
{
    node_t *node = NULL;

    for (loop_t event = 0; event < 4; event++) {
        node = func_single_loop(setfml, name, event);
        if (node)
            return event;
    }
    return (loop_t)SETFML_FAIL;
}

size_t setfml_del(setfml_t *setfml, char name[BUFF_FUNC_NAME])
{
    loop_t event = func_from_name(setfml, name);
    node_t *node = NULL;
    
    if (event == (loop_t)SETFML_FAIL)
        return (size_t)SETFML_FAIL;
    node = func_single_loop(setfml, name, event);
    if (!node)
        return (size_t)SETFML_FAIL;
    linkedlist_remove(setfml->functions[event], node, true);
    return (size_t)SETFML_SUCC;
}

size_t setfml_pause(setfml_t *setfml, char name[BUFF_FUNC_NAME])
{
    loop_t event = func_from_name(setfml, name);
    node_t *node = NULL;
    function_t *function = NULL;
    
    if (event == (loop_t)SETFML_FAIL)
        return (size_t)SETFML_FAIL;
    node = func_single_loop(setfml, name, event);
    if (!node)
        return (size_t)SETFML_FAIL;
    function = (function_t *)node->data;
    if (!function)
        return (size_t)SETFML_FAIL;
    function->paused = true;
    return (size_t)SETFML_SUCC;
}

size_t setfml_resume(setfml_t *setfml, char name[BUFF_FUNC_NAME])
{
    loop_t event = func_from_name(setfml, name);
    node_t *node = NULL;
    function_t *function = NULL;
    
    if (event == (loop_t)SETFML_FAIL)
        return (size_t)SETFML_FAIL;
    node = func_single_loop(setfml, name, event);
    if (!node)
        return (size_t)SETFML_FAIL;
    function = (function_t *)node->data;
    if (!function)
        return (size_t)SETFML_FAIL;
    function->paused = false;
    return (size_t)SETFML_SUCC;
}

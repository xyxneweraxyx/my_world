/*
** EPITECH PROJECT, 2025
** setfml
** File description:
** Tired of initializing csfml? Up your workflow with this simple wrapper.
*/

#include "./setfml.h"

size_t setfml_windowCreate(setfml_t *setfml)
{
    params_t params = setfml->params;
    sfVideoMode mode = {
        setfml->params.max_scr_res[0],
        setfml->params.max_scr_res[1],
        8};
    sfRenderWindow *window = sfRenderWindow_create(
        mode,
        params.title,
        params.style,
        params.settings);

    if (!window)
        return (size_t)SETFML_FAIL;
    setfml->window = window;
    sfRenderWindow_setFramerateLimit(window, (unsigned int)params.fps);
    return (size_t)SETFML_SUCC;
}

size_t setfml_windowStart(setfml_t *setfml)
{
    if (!setfml | !setfml->window)
        return (size_t)SETFML_FAIL;
    sfRenderWindow_display(setfml->window);
    while (sfRenderWindow_isOpen(setfml->window))
        sfRenderWindow_display(setfml->window);
    return (size_t)SETFML_SUCC;
}

size_t setfml_windowClose(setfml_t *setfml)
{
    if (!setfml | !setfml->window)
        return (size_t)SETFML_FAIL;
    sfRenderWindow_close(setfml->window);
    return (size_t)SETFML_SUCC;
}

size_t setfml_windowDelete(setfml_t *setfml)
{
    if (!setfml | !setfml->window)
        return (size_t)SETFML_FAIL;
    sfRenderWindow_destroy(setfml->window);
    setfml->window = NULL;
    return (size_t)SETFML_SUCC;
}
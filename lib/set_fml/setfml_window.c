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
        setfml->params.window.max_scr_res[0],
        setfml->params.window.max_scr_res[1],
        8};
    sfRenderWindow *window = sfRenderWindow_create(
        mode,
        params.window.title,
        params.window.style,
        params.window.settings);

    if (!window)
        return (size_t)SETFML_FAIL;
    setfml->window = window;
    sfRenderWindow_setFramerateLimit(window, (unsigned int)params.window.fps);
    return (size_t)SETFML_SUCC;
}

static void setfml_setTime(setfml_t *setfml)
{
    clock_gettime(CLOCK_MONOTONIC, &(setfml->state.time_elapsed.data));
    clock_gettime(CLOCK_MONOTONIC, &(setfml->state.time_elapsed.draw));
    clock_gettime(CLOCK_MONOTONIC, &(setfml->state.time_elapsed.event));
    clock_gettime(CLOCK_MONOTONIC, &(setfml->state.time_elapsed.render));

    setfml->state.to_exec.data = false;
    setfml->state.to_exec.draw = false;
    setfml->state.to_exec.event = false;
    setfml->state.to_exec.render = false;
}

static void setfml_updateLoop(setfml_t *setfml)
{
    if (setfml->state.to_exec.data)
        clock_gettime(CLOCK_MONOTONIC, &(setfml->state.last_exec.data));
    if (setfml->state.to_exec.draw)
        clock_gettime(CLOCK_MONOTONIC, &(setfml->state.last_exec.draw));
    if (setfml->state.to_exec.render)
        clock_gettime(CLOCK_MONOTONIC, &(setfml->state.last_exec.render));
    if (setfml->state.to_exec.event)
        clock_gettime(CLOCK_MONOTONIC, &(setfml->state.last_exec.event));
}

static void setfml_updateTime(setfml_t *setfml)
{
    time_elapsed_t t_el = setfml->state.time_elapsed;
    time_elapsed_t l_ex = setfml->state.last_exec;
    long time_elapsed_data = (t_el.data.tv_sec - l_ex.data.tv_sec) *
        NANO_TO_SEC + (t_el.data.tv_nsec - l_ex.data.tv_nsec);
    long time_elapsed_draw = (t_el.draw.tv_sec - l_ex.draw.tv_sec) *
        NANO_TO_SEC + (t_el.draw.tv_nsec - l_ex.draw.tv_nsec);
    long time_elapsed_event = (t_el.event.tv_sec - l_ex.event.tv_sec) *
        NANO_TO_SEC + (t_el.event.tv_nsec - l_ex.event.tv_nsec);
    long time_elapsed_render = (t_el.render.tv_sec - l_ex.render.tv_sec) *
        NANO_TO_SEC + (t_el.render.tv_nsec - l_ex.render.tv_nsec);

    if ((size_t)time_elapsed_data > setfml->params.time.data)
        setfml->state.to_exec.data = true;
    if ((size_t)time_elapsed_draw > setfml->params.time.draw)
        setfml->state.to_exec.draw = true;
    if ((size_t)time_elapsed_render > setfml->params.time.render)
        setfml->state.to_exec.render = true;
    if ((size_t)time_elapsed_event > setfml->params.time.event)
        setfml->state.to_exec.event = true;
}

static void setfml_iteration(setfml_t *setfml)
{
    setfml_settime(setfml);
    setfml_updatetime(setfml);
    setfml_updateLoop(setfml);
    sfRenderWindow_display(setfml->window);
}

size_t setfml_windowStart(setfml_t *setfml)
{
    if (!setfml | !setfml->window)
        return (size_t)SETFML_FAIL;
    sfRenderWindow_display(setfml->window);
    setfml_settime(setfml);
    setfml_updatetime(setfml);
    setfml_updateLoop(setfml);
    while (sfRenderWindow_isOpen(setfml->window))
        setfml_iteration(setfml);
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
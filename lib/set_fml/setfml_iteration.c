/*
** EPITECH PROJECT, 2025
** setfml
** File description:
** Tired of initializing csfml? Up your workflow with this simple wrapper.
*/

#include "./setfml.h"

static void setfml_settime(setfml_t *setfml)
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

static void setfml_updateloop(setfml_t *setfml)
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

static void setfml_updatetime(setfml_t *setfml)
{
    time_elapsed_t t_el = setfml->state.time_elapsed;
    time_elapsed_t l_ex = setfml->state.last_exec;
    long time_elapsed_data = (t_el.data.tv_sec - l_ex.data.tv_sec) *
        SEC_TO_NANO + (t_el.data.tv_nsec - l_ex.data.tv_nsec);
    long time_elapsed_draw = (t_el.draw.tv_sec - l_ex.draw.tv_sec) *
        SEC_TO_NANO + (t_el.draw.tv_nsec - l_ex.draw.tv_nsec);
    long time_elapsed_event = (t_el.event.tv_sec - l_ex.event.tv_sec) *
        SEC_TO_NANO + (t_el.event.tv_nsec - l_ex.event.tv_nsec);
    long time_elapsed_render = (t_el.render.tv_sec - l_ex.render.tv_sec) *
        SEC_TO_NANO + (t_el.render.tv_nsec - l_ex.render.tv_nsec);

    if ((size_t)time_elapsed_data > setfml->params.time.data)
        setfml->state.to_exec.data = true;
    if ((size_t)time_elapsed_draw > setfml->params.time.draw)
        setfml->state.to_exec.draw = true;
    if ((size_t)time_elapsed_render > setfml->params.time.render)
        setfml->state.to_exec.render = true;
    if ((size_t)time_elapsed_event > setfml->params.time.event)
        setfml->state.to_exec.event = true;
}

// For some reason the pause value shuffles around like a
// garbage value? I'm confused why but it goes from 0 to whatever it wants
// This makes the callback fail
static void setfml_execcallback(setfml_t *setfml, loop_t LOOP)
{
    node_t *node = NULL;
    function_t *func = NULL;
    function_t *function = (function_t *)setfml->functions[LOOP_EVENT]->head->data;
    printf("1 %d\n", (int)function->paused);
    if (!setfml || !setfml->functions[LOOP]->head)
        return;
    printf("2 %d\n", (int)function->paused);
    for (node = setfml->functions[LOOP]->head; node; node = node->next) {
        printf("3 %d\n", (int)function->paused);
        func = (function_t *)node->data;
        printf("func name is %s\n", func->name);
        printf("pause value is %d\n", (int)func->paused);
        if (func->paused)
            continue;
        func->return_code = func->function(setfml);
    }
    printf("4 %d\n", (int)function->paused);
}

static void setfml_handlecallbacks(setfml_t *setfml)
{
    function_t *function = (function_t *)setfml->functions[LOOP_EVENT]->head->data;
    printf("BEFORE CALLBACK %d\n", (int)function->paused);
    if (setfml->state.to_exec.event) {
        setfml->state.to_exec.event = false;
        setfml_execcallback(setfml, LOOP_EVENT);
    }
    printf("AFTER EVENTS %d\n", (int)function->paused);
    if (setfml->state.to_exec.data) {
        setfml->state.to_exec.data = false;
        setfml_execcallback(setfml, LOOP_DATA);
    }
    if (setfml->state.to_exec.render) {
        setfml->state.to_exec.render = false;
        setfml_execcallback(setfml, LOOP_RENDER);
    }
    if (setfml->state.to_exec.draw) {
        setfml->state.to_exec.draw = false;
        sfRenderWindow_clear(setfml->window, sfBlack);
        setfml_execcallback(setfml, LOOP_DRAW);
    }
    printf("AFTER ALL %d\n", (int)function->paused);
}

void setfml_iteration(setfml_t *setfml)
{
    function_t *function = (function_t *)setfml->functions[LOOP_EVENT]->head->data;
    printf("BEFORE %d\n", (int)function->paused);
    setfml_settime(setfml);
    setfml_updatetime(setfml);
    setfml_updateloop(setfml);
    printf("AFTER 1 %d\n", (int)function->paused);
    setfml_handlecallbacks(setfml);
    printf("AFTER %d\n", (int)function->paused);
    sfRenderWindow_display(setfml->window);
}

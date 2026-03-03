/*
** EPITECH PROJECT, 2025
** buttonfml
** File description:
** Wrapper on the setfml library to create simple buttons easily.
*/

#include "./buttonfml.h"

static size_t is_mouse_on_button(button_t *button, size_t x, size_t y)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(button->button->sprite);

    if (x < (size_t)rect.left || x > (size_t)(rect.left + rect.width))
        return (size_t)BUTTONFML_FAIL;
    if (y < (size_t)rect.top || y > (size_t)(rect.top + rect.height))
        return (size_t)BUTTONFML_FAIL;
    return (size_t)BUTTONFML_SUCC;
}

static size_t buttonfml_reset(setfml_t *setfml, void *userdata)
{
    buttonfml_t *buttonfml = (buttonfml_t *)userdata;
    button_t *button = NULL;
    char text_name[BUFF_TEXT_NAME] = {0};

    for (node_t *node = buttonfml->buttons->head; node; node = node->next) {
        if (!button->is_visible || button->state == BUTTON_IDLE)
            continue;
        button = (button_t *)node->data;
        button->state = BUTTON_IDLE;
        str_cat(text_name, 2, button->name, "_idle");
        setfml_spritechangetexture(setfml,
            button->button, text_name);
    }
    return (size_t)BUTTONFML_SUCC;
}

static size_t buttonfml_mousemove(setfml_t *setfml, void *userdata)
{
    buttonfml_t *buttonfml = (buttonfml_t *)userdata;
    button_t *button = NULL;
    char text_name[BUFF_TEXT_NAME] = {0};

    for (node_t *node = buttonfml->buttons->head; node; node = node->next) {
        if (!button->is_visible)
            continue;
        button = (button_t *)node->data;
        if (is_mouse_on_button(button, (size_t)setfml->event.mouseMove.x,
            (size_t)setfml->event.mouseMove.y) == (size_t)BUTTONFML_FAIL)
            continue;
        if (button->state == BUTTON_IDLE)
            button->state = BUTTON_HOVERED;
        printf("button is hovered!\n");
        if (button->textures->hover[0]) {
            str_cat(text_name, 2, button->name, "_hover");
            setfml_spritechangetexture(setfml,
                button->button, text_name);
        }
        if (button->callbacks->frame)
            button->callbacks->hover(setfml, userdata);
    }
    return (size_t)BUTTONFML_SUCC;
}

static size_t buttonfml_mouseclick(setfml_t *setfml, void *userdata)
{
    buttonfml_t *buttonfml = (buttonfml_t *)userdata;
    button_t *button = NULL;
    char text_name[BUFF_TEXT_NAME] = {0};

    for (node_t *node = buttonfml->buttons->head; node; node = node->next) {
        if (!button->is_visible || !button->is_clickable)
            continue;
        button = (button_t *)node->data;
        if (is_mouse_on_button(button, setfml->event.mouseMove.x,
            setfml->event.mouseMove.y) == (size_t)BUTTONFML_FAIL)
            continue;
        button->state = BUTTON_CLICKED;
        printf("button is clicked!\n");
        if (button->textures->click[0]) {
            str_cat(text_name, 2, button->name, "_click");
            setfml_spritechangetexture(setfml,
                button->button, text_name);
        }
        if (button->callbacks->frame)
            button->callbacks->click(setfml, userdata);
    }
    return (size_t)BUTTONFML_SUCC;
}

static size_t buttonfml_frame(setfml_t *setfml, void *userdata)
{
    buttonfml_t *buttonfml = (buttonfml_t *)userdata;
    button_t *button = NULL;

    for (node_t *node = buttonfml->buttons->head; node; node = node->next) {
        if (!button->is_visible)
            continue;
        button = (button_t *)node->data;
        if (is_mouse_on_button(button, setfml->event.mouseMove.x,
            setfml->event.mouseMove.y) == (size_t)BUTTONFML_FAIL)
            continue;
        button->state = BUTTON_CLICKED;
        if (button->callbacks->frame)
            button->callbacks->frame(setfml, userdata);
    }
    return (size_t)BUTTONFML_SUCC;
}

static size_t buttonfml_draw(setfml_t *setfml, void *userdata)
{
    buttonfml_t *buttonfml = (buttonfml_t *)userdata;
    button_t *button = NULL;

    for (node_t *node = buttonfml->buttons->head; node; node = node->next) {
        if (!button->is_visible)
            continue;
        button = (button_t *)node->data;
        sfRenderWindow_drawSprite(setfml->window,
            button->button->sprite, NULL);
    }
    return (size_t)BUTTONFML_SUCC;
}

size_t buttonfml_connectcallbacks(buttonfml_t *buttonfml)
{
    node_t *node = NULL;
    function_t *function = NULL;

    setfml_add(buttonfml->setfml, &(setfml_func_comp_t){NULL,
        &buttonfml_draw}, "buttonfml_draw", LOOP_DRAW);
    node = setfml_nodefromfunc(buttonfml->setfml, "buttonfml_draw",
        LOOP_DRAW);
    if (!node)
        return (size_t)BUTTONFML_FAIL;
    function = (function_t *)node->data;
    function->userdata = (void *)buttonfml;

    setfml_add(buttonfml->setfml, &(setfml_func_comp_t){NULL,
        &buttonfml_mousemove}, "buttonfml_mousemove", sfEvtMouseMoved);
    node = setfml_nodefromfunc(buttonfml->setfml, "buttonfml_mousemove",
        sfEvtMouseMoved);
    if (!node)
        return (size_t)BUTTONFML_FAIL;
    function = (function_t *)node->data;
    function->userdata = (void *)buttonfml;

    setfml_add(buttonfml->setfml, &(setfml_func_comp_t){NULL,
        &buttonfml_mouseclick}, "buttonfml_mouseclick", sfEvtMouseButtonPressed);
    node = setfml_nodefromfunc(buttonfml->setfml, "buttonfml_mouseclick",
        sfEvtMouseButtonPressed);
    if (!node)
        return (size_t)BUTTONFML_FAIL;
    function = (function_t *)node->data;
    function->userdata = (void *)buttonfml;

    setfml_add(buttonfml->setfml, &(setfml_func_comp_t){NULL,
        &buttonfml_frame}, "buttonfml_frame", LOOP_RENDER);
    node = setfml_nodefromfunc(buttonfml->setfml, "buttonfml_frame",
        LOOP_RENDER);
    if (!node)
        return (size_t)BUTTONFML_FAIL;
    function = (function_t *)node->data;
    function->userdata = (void *)buttonfml;

    setfml_add(buttonfml->setfml, &(setfml_func_comp_t){NULL,
        &buttonfml_reset}, "buttonfml_reset", sfEvtMouseMoved);
    node = setfml_nodefromfunc(buttonfml->setfml, "buttonfml_reset",
        sfEvtMouseMoved);
    if (!node)
        return (size_t)BUTTONFML_FAIL;
    function = (function_t *)node->data;
    function->userdata = (void *)buttonfml;

    return (size_t)BUTTONFML_SUCC;
}

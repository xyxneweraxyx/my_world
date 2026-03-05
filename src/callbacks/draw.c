/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Camera movement callbacks.
*/

#include "./../../include/myworld.h"

static size_t draw_backgrounds(setfml_t *setfml, void *userdata)
{
    sprite_t *sprite = NULL;
    main_t *main = (main_t *)setfml->userdata;

    if (main->state == MYWORLD_MENU)
        sprite = setfml_spritefromname(setfml, "background", false);
    if (main->state == MYWORLD_EDITOR)
        sprite = setfml_spritefromname(setfml, "editorbackground", false);
    if (!sprite)
        return (size_t)SETFML_FAIL;
    sfRenderWindow_drawSprite(setfml->window, sprite->sprite, NULL);
    return (size_t)SETFML_SUCC;
}

size_t ini_draw_callbacks(setfml_t *setfml, void *userdata)
{
    setfml_add(setfml, &(setfml_func_comp_t){NULL, &draw_backgrounds}, "draw_backgrounds", LOOP_DRAW);
    setfml_add(setfml, &(setfml_func_comp_t){&draw_backgrounds, &draw}, "draw", LOOP_DRAW);
    return (size_t)SETFML_SUCC;
}
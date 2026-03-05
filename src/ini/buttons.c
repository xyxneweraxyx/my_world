/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Initializing buttons.
*/

#include "./../../include/myworld.h"

static void ini_button_data(main_t *main)
{
    button_t *cm = buttonfml_buttonfromname(main->buttonfml, "create_map");
    button_t *ex = buttonfml_buttonfromname(main->buttonfml, "exit");
    button_t *se = buttonfml_buttonfromname(main->buttonfml, "setting");

    sfSprite_setScale(ex->button->sprite, (sfVector2f){.5f, .5f});
    sfSprite_setScale(se->button->sprite, (sfVector2f){.5f, .5f});
    sfSprite_setScale(cm->button->sprite, (sfVector2f){1.1f, 1.1f});
    sfSprite_setPosition(cm->button->sprite, (sfVector2f){650, 250});
    sfSprite_setPosition(ex->button->sprite, (sfVector2f){600, 400});
    sfSprite_setPosition(se->button->sprite, (sfVector2f){600, 600});
}

size_t ini_buttons(main_t *main)
{
    button_t *create_map = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_CREATEMAP, "", ""},
        &(btn_clbck_t){NULL, NULL, NULL, NULL}, "create_map");
    button_t *exit = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_EXIT, "", ""},
        &(btn_clbck_t){NULL, NULL, NULL, NULL}, "exit");
    button_t *setting = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_SETTING, "", ""},
        &(btn_clbck_t){NULL, NULL, NULL, NULL}, "setting");

    if (!create_map || !exit || !setting)
        return (size_t)EXIT_FAIL;
    ini_button_data(main);
    return (size_t)EXIT_SUCC;
}
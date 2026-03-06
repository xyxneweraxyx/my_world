/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Initializing buttons.
*/

#include "./../../include/myworld.h"
#include "./../callbacks/callbacks.h"

static void set_origins(main_t *main)
{
    sprite_t *sprite = NULL;
    sfFloatRect size = {0, 0};

    for (node_t *n = main->setfml->sprites->head; n; n = n->next) {
        sprite = (sprite_t *)n->data;
        if (!sprite || !sprite->sprite)
            continue;
        size = sfSprite_getGlobalBounds(sprite->sprite);
        sfSprite_setOrigin(sprite->sprite,
            (sfVector2f){(float)size.width / 2, (float)size.height / 2});
    }
}

static void ini_button_data(main_t *main)
{
    button_t *cm = buttonfml_buttonfromname(main->buttonfml, "create_map");
    button_t *ex = buttonfml_buttonfromname(main->buttonfml, "exit");
    button_t *se = buttonfml_buttonfromname(main->buttonfml, "setting");
    button_t *ra = buttonfml_buttonfromname(main->buttonfml, "raise");
    button_t *lo = buttonfml_buttonfromname(main->buttonfml, "lower");
    button_t *re = buttonfml_buttonfromname(main->buttonfml, "reset");

    sfSprite_setPosition(cm->button->sprite, (sfVector2f){700, 250});
    sfSprite_setPosition(ex->button->sprite, (sfVector2f){700, 450});
    sfSprite_setPosition(se->button->sprite, (sfVector2f){700, 650});
    sfSprite_setPosition(ra->button->sprite, (sfVector2f){0, 800});
    sfSprite_setPosition(lo->button->sprite, (sfVector2f){200, 800});
    sfSprite_setPosition(re->button->sprite, (sfVector2f){400, 800});
    sfSprite_setScale(ra->button->sprite, (sfVector2f){0.25f, 0.25f});
    sfSprite_setScale(lo->button->sprite, (sfVector2f){0.25f, 0.25f});
    sfSprite_setScale(re->button->sprite, (sfVector2f){0.25f, 0.25f});
    set_origins(main);
}

static size_t ini_buttons_2(main_t *main)
{
    button_t *raise = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_RAISE, "", ""},
        &(btn_clbck_t){&editor_frame, NULL, &click_raise, NULL}, "raise");
    button_t *lower = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_LOWER, "", ""},
        &(btn_clbck_t){&editor_frame, NULL, &click_lower, NULL}, "lower");
    button_t *reset = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_RESET, "", ""},
        &(btn_clbck_t){&editor_frame, NULL, &click_reset, NULL}, "reset");

    if (!raise || !lower || !reset)
        return (size_t)EXIT_FAIL;
    return (size_t)EXIT_SUCC;
}

size_t ini_buttons(main_t *main)
{
    button_t *create_map = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_CREATEMAP, "", ""},
        &(btn_clbck_t){&menu_frame, NULL, &click_create_map, NULL},
        "create_map");
    button_t *exit = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_EXIT, "", ""},
        &(btn_clbck_t){&menu_frame, NULL, &click_exit, NULL},
        "exit");
    button_t *setting = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_SETTING, "", ""},
        &(btn_clbck_t){&menu_frame, NULL, &click_setting, NULL},
        "setting");

    if (!create_map || !exit || !setting ||
        ini_buttons_2(main) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    ini_button_data(main);
    return (size_t)EXIT_SUCC;
}

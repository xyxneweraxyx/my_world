/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Initializing buttons.
*/

#include "./../../include/myworld.h"

size_t ini_buttons(main_t *main)
{
    button_t *create_map = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_CREATEMAP, "", ""},
        &(btn_clbck_t){NULL, NULL, NULL, NULL},
        "create_map");
    button_t *exit = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_EXIT, "", ""},
        &(btn_clbck_t){NULL, NULL, NULL, NULL},
        "exit");
    button_t *setting = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_SETTING, "", ""},
        &(btn_clbck_t){NULL, NULL, NULL, NULL},
        "setting");
    button_t *back_home = buttonfml_buttoncreate(main->buttonfml,
        &(btn_text_t){AST_BACKHOME, "", ""},
        &(btn_clbck_t){NULL, NULL, NULL, NULL},
        "back_home");
    if (!create_map || !exit || !setting || ! back_home)
        return (size_t)EXIT_FAIL;
    printf("%p\n", back_home->callbacks->frame);
    printf("%p\n", setting->callbacks->frame);
    return (size_t)EXIT_SUCC;
}
/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Menu button callbacks.
*/

#include "./../../include/myworld.h"
#include "./callbacks.h"

size_t click_create_map(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    main->state = MYWORLD_EDITOR;
    return (size_t)EXIT_SUCC;
}

size_t click_exit(setfml_t *setfml, void *userdata)
{
    setfml_windowclose(setfml);
    return (size_t)SETFML_WINDOWCLOSING;
}

size_t click_setting(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    main->state = MYWORLD_SETTING;
    return (size_t)EXIT_SUCC;
}

size_t menu_frame(setfml_t *setfml, void *userdata)
{
    buttonfml_t *buttonfml = (buttonfml_t *)userdata;
    main_t *main = (main_t *)buttonfml->setfml->userdata;

    if (main->state == MYWORLD_MENU) {
        buttonfml_buttonshow(buttonfml, "create_map");
        buttonfml_buttonshow(buttonfml, "exit");
        buttonfml_buttonshow(buttonfml, "setting");
    } else {
        buttonfml_buttonhide(buttonfml, "create_map");
        buttonfml_buttonhide(buttonfml, "exit");
        buttonfml_buttonhide(buttonfml, "setting");
    }
    return (size_t)EXIT_SUCC;
}

/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Implementing program callbacks.
*/

#include "./../../include/myworld.h"
#include "./callbacks.h"

static size_t ini_tools_callbacks(setfml_t *setfml, void *userdata)
{
    setfml_add(setfml, &(setfml_func_comp_t){NULL, &update_brush},
        "update_brush", LOOP_DATA);
    return (size_t)EXIT_SUCC;
}

size_t ini_callbacks(main_t *main)
{
    if (ini_draw_callbacks(main->setfml, NULL) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    if (ini_camera_callbacks(main->setfml, NULL) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    if (ini_tools_callbacks(main->setfml, NULL) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    setfml_add(main->setfml,
        &(setfml_func_comp_t){NULL, &edit_click},
        "edit_click", sfEvtMouseButtonPressed);
    return (size_t)EXIT_SUCC;
}
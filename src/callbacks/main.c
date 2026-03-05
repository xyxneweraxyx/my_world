/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Implementing program callbacks.
*/

#include "./../../include/myworld.h"

size_t ini_callbacks(main_t *main)
{
    if (ini_draw_callbacks(main->setfml, NULL) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    if (ini_camera_callbacks(main->setfml, NULL) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    return (size_t)EXIT_SUCC;
}
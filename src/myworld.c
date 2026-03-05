/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Main entry file.
*/

#include "./../include/myworld.h"

static main_t *ini_vars(void)
{
    c_alloc_t *alloc = c_ini((uint16_t)1000);
    main_t *main = NULL;
    setfml_t *setfml = NULL;
    buttonfml_t *buttonfml = NULL;

    if (!alloc)
        return NULL;
    main = c_alloc(sizeof(main_t), 1, alloc);
    if (!main)
        return NULL;
    main->alloc = alloc;
    setfml = setfml_ini((void *)main);
    if (!setfml)
        return NULL;
    main->setfml = setfml;
    buttonfml = buttonfml_ini(setfml);
    if (!buttonfml)
        return NULL;
    main->buttonfml = buttonfml;
    return main;
}

static void destroy(main_t *main)
{
    buttonfml_destroy(main->buttonfml);
    setfml_destroy(main->setfml);
    c_delete(main->alloc, true);
}

int main(void)
{
    main_t *main = ini_vars();

    if (!main)
        return (size_t)EXIT_FAIL;
    main->setfml->params.time.draw = 500 * MILLI_TO_NANO;
    if (ini_csfml(main) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    if (ini_callbacks(main) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    if (setfml_windowstart(main->setfml) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    destroy(main);
    return (size_t)EXIT_SUCC;
}
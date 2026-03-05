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
    if (ini_csfml(main) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    if (ini_callbacks(main) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    if (setfml_windowstart(main->setfml) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    destroy(main);
    return (size_t)EXIT_SUCC;
}

/*static void draw(sfRenderWindow *window)
{
    sfVertexArray *array = sfVertexArray_create();

    sfVertexArray_resize(array, (size_t)50);
    sfVertexArray_setPrimitiveType(array, sfPoints);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            sfVertex vertex = {};
            vertex.color = (sfColor){150, i * 30, j * 30, 255};
            vertex.position = (sfVector2f){i * 50 + 10, j * 50 + 10};
            vertex.texCoords = (sfVector2f){0, 0};
            sfVertexArray_append(array, vertex);
        }
    }
    sfRenderWindow_drawVertexArray(window, array, NULL);
    sfVertexArray_destroy(array);
}*/

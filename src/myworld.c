/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Main entry file.
*/

#include "./../include/myworld.h"

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

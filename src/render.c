/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Main entry file.
*/

#include "./../include/myworld.h"

static sfVector2f get_vertex_pos(main_t *main, size_t x, size_t y)
{
    sfVector2f vector = {0, 0};

    vector.x = x * main->render.zoom * 100;
    vector.y = y * main->render.zoom * 100;
    vector.x = vector.x + main->render.origin.x;
    vector.y = vector.y + main->render.origin.y;
    printf("xy is %zu %zu coords are %f %f\n", x, y, vector.x, vector.y);
    return vector;
}

static texture_t *get_texture_from_height(main_t *main, float height)
{
    if (height < 0)
        return setfml_texturefromname(main->setfml, "grasstexture", false);
    if (height < 20)
        return setfml_texturefromname(main->setfml, "rocktexture", false);
    return setfml_texturefromname(main->setfml, "exit", false);
}

static void new_square(main_t *main, size_t x, size_t y)
{
    sfConvexShape *convexshape = sfConvexShape_create();
    float height = main->render.height[y][x];
    texture_t *texture = get_texture_from_height(main, height);

    if (!texture)
        return;
    printf("creating square\n");
    sfConvexShape_setPointCount(convexshape, 4);
    sfConvexShape_setPoint(convexshape, 0, get_vertex_pos(main, x, y));
    sfConvexShape_setPoint(convexshape, 1, get_vertex_pos(main, x + 1, y));
    sfConvexShape_setPoint(convexshape, 2, get_vertex_pos(main, x, y + 1));
    sfConvexShape_setPoint(convexshape, 3, get_vertex_pos(main, x + 1, y + 1));
    sfConvexShape_setOutlineColor(convexshape, (sfColor){0, 0, 0, 0});
    sfConvexShape_setOutlineThickness(convexshape, 1);
    sfConvexShape_setFillColor(convexshape, (sfColor){0, 255, 0, 1});
    sfConvexShape_setPosition(convexshape, get_vertex_pos(main, x, y));
    sfRenderWindow_drawConvexShape(main->setfml->window, convexshape, NULL);
    sfConvexShape_destroy(convexshape);
}

size_t draw(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    for (size_t y = 0; y < 1; y++) {
        for (size_t x = 0; x < 1; x++)
            new_square(main, x, y);
    }
    return (size_t)EXIT_SUCC;
}
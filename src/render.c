/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** 3D perspective rendering of the height map
*/

#include "./../include/myworld.h"

static vec3_t translate(main_t *main, vec3_t *point)
{
    render_t *r = &main->render;
    vec3_t translate_vec = {0, 0, 0};

    translate_vec.x = point->x - r->cam_x;
    translate_vec.y = point->y - r->cam_y;
    translate_vec.z = point->z - r->cam_z;
    return translate_vec;
}

static vec3_t rotate_yaw(vec3_t *point, float yaw)
{
    vec3_t yaw_vec = {0, 0, 0};

    yaw_vec.x = point->x * cosf(yaw) - point->z * sinf(yaw);
    yaw_vec.y = point->y;
    yaw_vec.z = point->x * sinf(yaw) + point->z * cosf(yaw);
    return yaw_vec;
}

static vec3_t rotate_pitch(vec3_t *point, float pitch)
{
    vec3_t rotate_vec = {0, 0, 0};

    rotate_vec.x = point->x;
    rotate_vec.y = point->y * cosf(pitch) - point->z * sinf(pitch);
    rotate_vec.z = point->y * sinf(pitch) + point->z * cosf(pitch);
    return rotate_vec;
}

static sfVector2f project(main_t *main, vec3_t *world)
{
    sfVector2u win = sfRenderWindow_getSize(main->setfml->window);
    vec3_t point = translate(main, world);

    point = rotate_yaw(&point, main->render.yaw);
    point = rotate_pitch(&point, -1 * main->render.pitch);
    if (point.z <= 0.1f)
        return (sfVector2f){-99999, -99999};
    return (sfVector2f){
        win.x / 2.0f + (point.x / point.z) * main->render.fov,
        win.y / 2.0f - (point.y / point.z) * main->render.fov
    };
}

static texture_t *get_texture(main_t *main, float height)
{
    if (height < 0)
        return setfml_texturefromname(main->setfml, "rocktexture", false);
    if (height < 100)
        return setfml_texturefromname(main->setfml, "dirttexture", false);
    return setfml_texturefromname(main->setfml, "grasstexture", false);
}

static bool create_points(main_t *main, size_t x, size_t y,
    sfVector2f points[4])
{
    render_t *r = &main->render;
    float t = r->zoom;
    float heights[4] = {
        r->height[y][x],
        r->height[y][x + 1],
        r->height[y + 1][x + 1],
        r->height[y + 1][x]
    };

    points[0] = project(main, &(vec3_t){x * t, heights[0], y * t});
    points[1] = project(main, &(vec3_t){(x+1) * t, heights[1], y * t});
    points[2] = project(main, &(vec3_t){(x+1) * t, heights[2], (y+1) * t});
    points[3] = project(main, &(vec3_t){x * t, heights[3], (y+1) * t});
    for (size_t i = 0; i < 4; i++)
        if (points[i].x < -9000 || points[i].y < -9000)
            return false;
    return true;
}

static void draw_square(main_t *main, size_t x, size_t y)
{
    sfVector2f points[4] = {0};
    sfConvexShape *shape = sfConvexShape_create();
    float avg = (main->render.height[y][x] + main->render.height[y][x + 1] +
        main->render.height[y + 1][x + 1] + main->render.height[y + 1][x]) / 4;
    int cl = 255 - avg;

    if (!shape || !create_points(main, x, y, points))
        return;
    sfConvexShape_setPointCount(shape, 4);
    sfConvexShape_setTexture(shape,
        get_texture(main, main->render.height[y][x])->texture, sfFalse);
    for (size_t i = 0; i < 4; i++)
        sfConvexShape_setPoint(shape, i, points[i]);
    sfConvexShape_setOutlineColor(shape, (sfColor){0, 0, 0, 255});
    sfConvexShape_setOutlineThickness(shape, 1);
    sfConvexShape_setFillColor(shape, (sfColor){cl, cl, cl, 255});
    sfRenderWindow_drawConvexShape(main->setfml->window, shape, NULL);
    sfConvexShape_destroy(shape);
}

size_t draw(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;
    render_t *r = &main->render;

    if (main->state != MYWORLD_EDITOR)
        return (size_t)EXIT_SUCC;
    for (size_t y = r->square_amount_y - 2; y < r->square_amount_y; y--)
        for (size_t x = 0; x < r->square_amount_x - 1; x++)
            draw_square(main, x, y);
    return (size_t)EXIT_SUCC;
}
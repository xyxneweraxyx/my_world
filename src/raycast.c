/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Raycast and modification of related data
*/

#include "./../include/myworld.h"

static sfVector2f unproject(main_t *main)
{
    render_t render = main->render;
    sfVector2u win = sfRenderWindow_getSize(main->setfml->window);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(main->setfml->window);
    float p = -1 * render.pitch;
    float rx = (float)(mouse.x - (int)win.x / 2) / render.fov;
    float ry_cam = -(float)(mouse.y - (int)win.y / 2) / render.fov;
    float rz_cam = 1.0f;
    float ry = ry_cam * cosf(p) + rz_cam * sinf(p);
    float rz = -ry_cam * sinf(p) + rz_cam * cosf(p);
    float dx = rx * cosf(render.yaw) + rz * sinf(render.yaw);
    float dz = -rx * sinf(render.yaw) + rz * cosf(render.yaw);
    float t = 0.0f;

    if (fabsf(ry) < 0.0001f)
        return (sfVector2f){-1, -1};
    t = -1 * render.cam_y / ry;
    if (t < 0)
        return (sfVector2f){-1, -1};
    return (sfVector2f){render.cam_x + t * dx, render.cam_z + t * dz};
}

static void update_in_radius(main_t *main)
{
    render_t *r = &main->render;
    float tile_cx = 0.0f;
    float tile_cz = 0.0f;
    float dist = 0.0f;

    for (size_t y = 0; y < r->square_amount_y; y++) {
        for (size_t x = 0; x < r->square_amount_x; x++) {
            tile_cx = (x + 0.5f) * r->zoom;
            tile_cz = (y + 0.5f) * r->zoom;
            dist = sqrtf(
                (tile_cx - r->brush.x) * (tile_cx - r->brush.x) +
                (tile_cz - r->brush.y) * (tile_cz - r->brush.y));
            r->in_radius[y][x] = dist <= (float)(r->radius * r->zoom);
        }
    }
}

size_t update_brush(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    if (main->state != MYWORLD_EDITOR)
        return (size_t)EXIT_SUCC;
    main->render.brush = unproject(main);
    if (main->render.brush.x < 0)
        return (size_t)EXIT_SUCC;
    update_in_radius(main);
    return (size_t)EXIT_SUCC;
}
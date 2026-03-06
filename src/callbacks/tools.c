/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Implementing program callbacks.
*/

#include "./../../include/myworld.h"

/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Terrain editing callbacks.
*/

#include "./../../include/myworld.h"
#include "./callbacks.h"

#define RAISE_AMOUNT 5.0f

static void handletile(main_t *main, size_t x, size_t y)
{
    if (main->edit_state == EDIT_RESET)
        main->render.height[y][x] = 0.0f;
    if (!main->render.in_radius[y][x])
        return;
    if (main->edit_state == EDIT_RAISE)
        main->render.height[y][x] += RAISE_AMOUNT;
    if (main->edit_state == EDIT_LOWER)
        main->render.height[y][x] -= RAISE_AMOUNT;
}

static void apply_effects(main_t *main)
{
    for (size_t y = 0; y < main->render.square_amount_y; y++)
        for (size_t x = 0; x < main->render.square_amount_x; x++)
            handletile(main, x, y);
}

size_t edit_click(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    if (main->state != MYWORLD_EDITOR)
        return (size_t)EXIT_SUCC;
    apply_effects(main);
    return (size_t)EXIT_SUCC;
}

size_t click_raise(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    main->edit_state = EDIT_RAISE;
    return (size_t)EXIT_SUCC;
}

size_t click_lower(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    main->edit_state = EDIT_LOWER;
    return (size_t)EXIT_SUCC;
}

size_t click_reset(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    main->edit_state = EDIT_RESET;
    return (size_t)EXIT_SUCC;
}

size_t editor_frame(setfml_t *setfml, void *userdata)
{
    buttonfml_t *buttonfml = (buttonfml_t *)userdata;
    main_t *main = (main_t *)buttonfml->setfml->userdata;

    if (main->state == MYWORLD_EDITOR) {
        buttonfml_buttonshow(buttonfml, "raise");
        buttonfml_buttonshow(buttonfml, "lower");
        buttonfml_buttonshow(buttonfml, "reset");
    } else {
        buttonfml_buttonhide(buttonfml, "raise");
        buttonfml_buttonhide(buttonfml, "lower");
        buttonfml_buttonhide(buttonfml, "reset");
    }
    return (size_t)EXIT_SUCC;
}